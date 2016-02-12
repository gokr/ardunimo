/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

#ifndef _LGPS_H
#define _LGPS_H

#include "LTask.h"

#define GPS_MAX_GPGGA_SENTENCE_LENGTH 100
#define GPS_MAX_GPGSA_SENTENCE_LENGTH 80
#define GPS_MAX_GPRMC_SENTENCE_LENGTH 100
#define GPS_MAX_GPVTG_SENTENCE_LENGTH 80
#define GPS_MAX_GPGSV_SENTENCE_LENGTH 400
#define GPS_MAX_GLGSV_SENTENCE_LENGTH 400
#define GPS_MAX_BDGSV_SENTENCE_LENGTH 400
#define GPS_MAX_BDGSA_SENTENCE_LENGTH 80
#define GPS_MAX_GLGSA_SENTENCE_LENGTH 80

// gps sentence (NMEA) infomation
typedef struct
{
    unsigned char  GPGGA[GPS_MAX_GPGGA_SENTENCE_LENGTH+1];   // Sample like $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
    unsigned char  GPGSA[GPS_MAX_GPGSA_SENTENCE_LENGTH+1];    // Sample like $GPGSA,A,3,01,20,19,13,,,,,,,,,40.4,24.4,32.2*0A
    unsigned char  GPRMC[GPS_MAX_GPRMC_SENTENCE_LENGTH+1];   //  Sample like $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
    unsigned char  GPVTG[GPS_MAX_GPVTG_SENTENCE_LENGTH+1];   //  Sample like $GPVTG,89.68,T,,M,0.00,N,0.0,K*5F
    unsigned char  GPGSV[GPS_MAX_GPGSV_SENTENCE_LENGTH+1];   //  Sample like $GPGSV,3,1,10,20,78,331,45,01,59,235,47,22,41,069,,13,32,252,45*70
    unsigned char  GLGSV[GPS_MAX_GLGSV_SENTENCE_LENGTH+1];   //  GLONASS data of GSV
    unsigned char  GLGSA[GPS_MAX_GLGSA_SENTENCE_LENGTH+1];   //  GLONASS data of GSA
    unsigned char  BDGSV[GPS_MAX_BDGSV_SENTENCE_LENGTH+1];   // BEIDOU data of GSV
    unsigned char  BDGSA[GPS_MAX_BDGSA_SENTENCE_LENGTH+1];   // BEIDOU data of GSA
} gpsSentenceInfoStruct;

// gps mode
typedef enum
{
    GPS_START_MODE_NULL,
    GPS_HOT_START,               // GPS selects this mode when it remembers its last calculated position and the last recorded satellites is still in view. If you are at same location when the GPS was turned off, the GPS is capable of positioning in the shortest time.
    GPS_WARM_START,           // GPS selects this mode when it remembers its last calculated position but the last recorded satellites is not in view. The GPS then needs more time to locate the satellites and position.
    GPS_COLD_START,             // GPS selects this mode when it only has the current time. It takes longer time to locate the GPS information.
    GPS_FULL_START,              // GPS selects this mode when it has no information. There will be a full restart and it will take the longest time.
    GPS_START_TYPE_END
}gpsModeEnum;

/*gps type */
typedef enum
{
    GPS_ONLY,		/* GPS ONLY */
    GPS_GLONASS,	/* GPS+GLONASS */
    GPS_BEIDOU,		/* GPS+BEIDOU */
    GPS_TYPE_END
} gpsTypeEnum;

// LGPS class interface, With this library, you can use the object LGPS to get GPS data. Basic flow of controlling GPS:
class LGPSClass  : public _LTaskClass {

// Constructor / Destructor
public:
	LGPSClass() { };

// Method
public:
	 // DESCRIPTION
	 //     Turns on GPS device.
	 // EXAMPLE
	 //  <code>
	 //  #include <LGPS.h>
	 //  gpsSentenceInfoStruct info;
        //  void setup()
	 //  {
	 //     LGPS.powerOn();
	 //     delay(500);
	 //  }
	 //  void loop()
	//  {
	//     LGPS.getData(&info);
	//     delay(2000);
	//  }
	//  </code>
	void powerOn(
			gpsTypeEnum type = GPS_GLONASS    // [IN] please refer the enum gpsTypeEnum, default is GPS + GLONASS
		);

	 // DESCRIPTION
	 //     Turns off GPS.
	 //     Note: Turning off GPS when GPS data are not required can save power.
	void powerOff(void);

	 // DESCRIPTION
	 //    Sets up GPS start mode, this interface used for testing, no need it when in normal usage.
	void setMode(
			gpsModeEnum mode    // [IN] please refer the enum gpsModeEnum
		);

	 // DESCRIPTION
	 //    get GPS data
	void getData(
			gpsSentenceInfoStruct* info    // [IN] please refer the struct gpsSentenceInfoStruct
			);
	
public:
	void setData(gpsSentenceInfoStruct* info);

private:
	gpsSentenceInfoStruct m_info;

};

extern LGPSClass LGPS;

#endif
