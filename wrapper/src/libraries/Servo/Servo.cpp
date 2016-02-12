/* 
  A servo is activated by creating an instance of the Servo class passing 
  the desired pin to the attach() method.
  The servos are pulsed in the background using the value most recently 
  written using the write() method.

  Note that analogWrite of PWM on pins associated with the timer are 
  disabled when the first servo is attached.
  Timers are seized as needed in groups of 12 servos - 24 servos use two 
  timers, 48 servos will use four.
  The sequence used to sieze timers is defined in timers.h

  The methods are:

    Servo - Class for manipulating servo motors connected to Arduino pins.

    attach(pin )  - Attaches a servo motor to an i/o pin.
    attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
    default min is 544, max is 2400  
 
    write()     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
    writeMicroseconds() - Sets the servo pulse width in microseconds 
    read()      - Gets the last written servo pulse width as an angle between 0 and 180. 
    readMicroseconds()   - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
    attached()  - Returns true if there is a servo attached. 
    detach()    - Stops an attached servos from pulsing its i/o pin. 

  Modified 20 Aug 2014 by MediaTek Inc.
 */

#include <Arduino.h>
#include <Servo.h>
#include "vmsys.h"
#include "vmtimer.h"
#include "vmlog.h"

/* 32K or 13M hz */
#define MTK_SERVO_CLOCK 32000

#if defined(MTK_SERVO_CLOCK) && (MTK_SERVO_CLOCK == 32000)
#define MTK_SERVO_CLOCK_VALUE 1
#elif defined(MTK_SERVO_CLOCK) && (MTK_SERVO_CLOCK == 13000000)
#define MTK_SERVO_CLOCK_VALUE 0
#else
#error "specified mtk clock value error"
#endif
                            /* CLOCK */                /* HZ */
#define MTK_SERVO_CYCLE (MTK_SERVO_CLOCK / (1000/(REFRESH_INTERVAL/1000)))





#define usToTicks(_us)    ((_us) / 4615)     // converts microseconds to tick
#define ticksToUs(_ticks) ((unsigned)_ticks * 4615) // converts from ticks back to microseconds

#define TRIM_DURATION       0                               // compensation ticks to trim adjust for digitalWrite delays

static servo_t servos[MAX_SERVOS];                          // static array of servo structures

uint8_t ServoCount = 0;                                     // the total number of attached servos

static volatile int8_t Channel[_Nbr_16timers ];             // counter for the servo being pulsed for each timer (or -1 if refresh interval)

// convenience macros
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER)) // returns the timer controlling this servo
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)       // returns the index of the servo on this timer
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)     // macro to access servo index by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])            // macro to access servo class by timer and channel

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // maximum value in uS for this servo

/************ static functions common to all instances ***********************/

typedef struct
{
    volatile unsigned int TC_RA;
    volatile unsigned int TC_CV;
}TC_CHANNEL_T;

static TC_CHANNEL_T TC_CHANNEL[MAX_SERVOS] = {{0, REFRESH_INTERVAL}};

static void Servo_Handler(timer16_Sequence_t timer, uint8_t channel)
{
    // clear interrupt
    timer = 0;
    channel = 0;

    delayMicroseconds(TC_CHANNEL[channel].TC_RA);
    if (Channel[timer] < 0) {
        //tc->TC_CHANNEL[channel].TC_CCR |= TC_CCR_SWTRG; // channel set to -1 indicated that refresh interval completed so reset the timer
    } else {
        if (SERVO_INDEX(timer,Channel[timer]) < ServoCount && SERVO(timer,Channel[timer]).Pin.isActive == true) {
            digitalWrite(SERVO(timer,Channel[timer]).Pin.nbr, LOW); // pulse this channel low if activated
        }
    }

    Channel[timer]++;    // increment to the next channel
    if( SERVO_INDEX(timer,Channel[timer]) < ServoCount && Channel[timer] < SERVOS_PER_TIMER) {
        TC_CHANNEL[channel].TC_RA = TC_CHANNEL[channel].TC_CV + SERVO(timer,Channel[timer]).ticks;
        if(SERVO(timer,Channel[timer]).Pin.isActive == true) {    // check if activated
            digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,HIGH); // its an active channel so pulse it high
        }
    }
    else {
        // finished all channels so wait for the refresh period to expire before starting over
        if( (TC_CHANNEL[channel].TC_CV) + 4 < REFRESH_INTERVAL ) { // allow a few ticks to ensure the next OCR1A not missed
            TC_CHANNEL[channel].TC_RA = (unsigned int)REFRESH_INTERVAL;
        }
        else {
            TC_CHANNEL[channel].TC_RA = TC_CHANNEL[channel].TC_CV + 4;  // at least REFRESH_INTERVAL has elapsed
        }
        Channel[timer] = -1; // this will get incremented at the end of the refresh period to start again at the first channel
    }
}

void initISR(timer16_Sequence_t timer)
{
    
}


void finISR(timer16_Sequence_t timer)
{
    
}


static boolean isTimerActive(timer16_Sequence_t timer)
{
  // returns true if any servo is active on this timer
  for(uint8_t channel=0; channel < SERVOS_PER_TIMER; channel++) {
    if(SERVO(timer,channel).Pin.isActive == true)
      return true;
  }
  return false;
}



/****************** end of static functions ******************************/

Servo::Servo()
{
  if (ServoCount < MAX_SERVOS) {
    this->servoIndex = ServoCount++;                    // assign a servo index to this instance
    //servos[this->servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values
    servos[this->servoIndex].ticks = DEFAULT_PULSE_WIDTH;   // store default values
  } else {
    this->servoIndex = INVALID_SERVO;  // too many servos
  }
}

uint8_t Servo::attach(int pin)
{
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(int pin, int min, int max)
{
  timer16_Sequence_t timer;

  if (this->servoIndex < MAX_SERVOS) {
    pinMode(pin, OUTPUT);                                   // set servo pin to output
    servos[this->servoIndex].Pin.nbr = pin;
    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
    //this->min  = (int)(((float)MIN_PULSE_WIDTH/REFRESH_INTERVAL) * MTK_SERVO_CYCLE);
    this->min  = (MIN_PULSE_WIDTH - min)/4; // 
    this->max  = (MAX_PULSE_WIDTH - max)/4; // 
    // initialize the timer if it has not already been initialized
    timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if (isTimerActive(timer) == false) {
      initISR(timer);
    }
    servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
  }
  return this->servoIndex;
}

void Servo::detach()
{
  timer16_Sequence_t timer;

  servos[this->servoIndex].Pin.isActive = false;
  timer = SERVO_INDEX_TO_TIMER(servoIndex);
  if(isTimerActive(timer) == false) {
    finISR(timer);
  }
}

void Servo::write(int value)
{
  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
  if (value < MIN_PULSE_WIDTH)
  {
    if (value < 0)
      value = 0;
    else if (value > 180)
      value = 180;
    vm_log_info("Servo::write 1 value[%d]", value);
    value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
    vm_log_info("Servo::write 2 value[%d]", value);
  }
  writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
  // calculate and store the values for the given channel
  byte channel = this->servoIndex;
  if( (channel < MAX_SERVOS) )   // ensure channel is valid
  {
    if (value < SERVO_MIN())          // ensure pulse width is valid
      value = SERVO_MIN();
    else if (value > SERVO_MAX())
      value = SERVO_MAX();

    value = value - TRIM_DURATION;
    //value = usToTicks(value);  // convert to ticks after compensating for interrupt overhead
    servos[channel].ticks = value; // 

    int curr_min = (int)(((float)MIN_PULSE_WIDTH/REFRESH_INTERVAL) * MTK_SERVO_CYCLE);
    int curr_max = (int)(((float)MAX_PULSE_WIDTH/REFRESH_INTERVAL) * MTK_SERVO_CYCLE);

    int duty = map(value, SERVO_MIN(), SERVO_MAX(), curr_min, curr_max);
    analogWriteAdvance(servos[this->servoIndex].Pin.nbr, 
                        MTK_SERVO_CLOCK_VALUE, 
                        0, 
                        MTK_SERVO_CYCLE, 
                        duty);
    vm_log_info("Servo::writeMicroseconds [%d:%d][%d,%d,%d,%d]", curr_min, curr_max,
        servos[this->servoIndex].Pin.nbr, MTK_SERVO_CLOCK_VALUE, MTK_SERVO_CYCLE, duty);
  }
}

int Servo::read() // return the value as degrees
{
  //return map(readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);
  return map(servos[this->servoIndex].ticks, SERVO_MIN(), SERVO_MAX(), 0, 180);
}
/*
int Servo::readMicroseconds()
{
  unsigned int pulsewidth;
  if (this->servoIndex != INVALID_SERVO)
    pulsewidth = ticksToUs(servos[this->servoIndex].ticks)  + TRIM_DURATION;
  else
    pulsewidth  = 0;

  return pulsewidth;
}
*/

bool Servo::attached()
{
  return servos[this->servoIndex].Pin.isActive;
}
