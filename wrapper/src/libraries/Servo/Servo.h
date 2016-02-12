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



#ifndef Servo_h
#define Servo_h

#include "vmsys.h"
#define timer16_Sequence_t VMINT

#define Servo_VERSION           2     // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds 

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer 
#define _Nbr_16timers   4
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

typedef struct  {
  VMUINT8 nbr        :6 ;             // a pin number from 0 to 63
  VMUINT8 isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false 
} ServoPin_t   ;  

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;

//DESCRIPTION
// Servo Library allows RC servo control on LinkIt circuit board. 
// Servo integrates gears and axes, which is capable of accurate control.
//
// A standard servo system positions an axis in different angles, normally between 0 and 180 degree.
// Rotating servo continuously will set the rotation of axis to different speeds.
//
//Note:
// Only pin (D3, D9) with PWM functionality can be used by servo.
//
//EXAMPLE
//<code>
//#include <Servo.h>
//Servo myservo;
// 
//int potpin = 0;
//int val;
// 
//void setup()
//{
//  myservo.attach(9);                // servo connect to pin 9
//}
// 
//void loop()
//{
//  val = analogRead(potpin);         // read from Pot pin
//  val = map(val, 0, 1023, 0, 180);  // map from 0~1023 to 0~180
//  myservo.write(val);               // control servo
//  delay(200);
//}
//<code>
class Servo
{
public:
  Servo();

  // DESCRIPTION
  //  Attaches servo motor to a digital pin. Only digital pins supporting PWM (D3, D9) can use this function.
  // RETURNS
  //  channel number or 0 if failure
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  VMUINT8 attach(
	  int pin	//pin which needs servo attachment
	  );

  // DESCRIPTION
  //  Attaches servo motor to a digital pin. Only digital pins supporting PWM (D3, D9) can use this function.
  // RETURNS
  //  channel number or 0 if failure
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  VMUINT8 attach(
	  int pin, //pin which needs servo attachment
	  int min, //(optional)lower bound of PW, ms; PWM when servo motor is at 0 degree (default: 544)
	  int max  //(optional)upper bound of PW, ms, PWM when servo motor is at 180 degree (default: 2400)
	  );

  //Servo motor and pin detached. If all servo motors are bound, you can use PWM output and analogWrite to output.
  void detach();	

  // DESCRIPTION
  //  Writes a value to servo to control corresponding lever.
  //  Sets up the lever angle for a standard servo motor to move the lever to the corresponding angle. For a continuously rotating servo motor, sets up its rotation speed (0: rotate towards one direction in full speed; 180: rotate towards another direction in full speed; 90: stay intact)
  // RETURNS
  //  void
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  //   myservo.write(90);  // set servo to mid-point
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  void write(
	  int value	//angle written to servo, 0 ~ 180
	  );


  // DESCRIPTION
  //  Writes an us value to servo to control corresponding lever. 
  //  Sets up the rotation angle of a standard servo motor. In terms of parameters for a standard servo, 1000 means rotating counterclockwise in full speed, 2000 clockwise in full speed and 1500 in the middle.
  // 
  //  The following is extracted from the official website of Arduino:
  //  Some customers do not operate following the standard method, for example setting the response value of servo between 700 and 2300. You can try enlarge the limits to adjust the range of rotation. However, such operation may shorten the life of servo and should be avoided.
  // RETURNS
  //  void
  // EXAMPLE
  // <code>
  // #include <Servo.h>
  //  
  // Servo myservo;
  //  
  // void setup()
  // {
  //   myservo.attach(9);
  //   myservo.writeMicroseconds(1500);  // set servo to mid-point
  // }
  //  
  // void loop() 
  // {
  //   
  // }
  // </code> 
  void writeMicroseconds(
	  int value	//value of microseconds
	  ); 

  // DESCRIPTION
  //  Reads the current rotation angle of servo motor.
  // RETURNS
  //  Rotation angle of servo, 0 ~ 180 degree
  int read();

  // DESCRIPTION
  //  Detects if servo has been attached with a pin.
  // RETURNS
  //  True if pin is attached; otherwise false
  bool attached();        

private:
   VMUINT8 servoIndex;               // index into the channel data for this servo
   VMINT8 min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
   VMINT8 max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH   
};

#endif
