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

#ifndef _LAUDIO_H
#define _LAUDIO_H

#include "chip.h"
#include "vmsys.h"
#include "LTask.h"
#include "Arduino.h"

// playing status
typedef enum 
{
	AudioCommonFailed = -1,     // Playback fails (e.g. the audio file is corrupted).
	AudioStop = 1,                       // Playback is stopped.
	AudioPause = 2,                     // Playback is paused (and can resume).
	AudioResume = 3,                  // Playback resumes
	AudioEndOfFile = 5               // Playback is finished.
}AudioStatus;

// storage location
typedef enum 
{
	storageFlash,    // Flash
	storageSD         // SD
}StorageEnum;

// LAudio class interface
class LAudioClass  : public _LTaskClass {

// Constructor / Destructor
public:
	LAudioClass() { };

public:	
	 // DESCRIPTION
	 //    Plays an audio file on SD card or flash storage.
	 // EXAMPLE
	 //<code>
	 //	#include <LAudio.h>  
	 //	void setup()
	 //	{
	 //   	    LAudio.begin();
	 //   	    LAudio.playFile(storageFlash, (char*)"sample.mp3");
	 //   	    LAudio.setVolume(2);
	 //   	    delay(2000);
	 //   	    LAudio.pause();
	 //   	    delay(2000);
	 //   	    LAudio.resume();
	 //   	    delay(2000);
	 //   	    LAudio.stop();
	 //	}	
	 //</code>
	void    playFile(
			StorageEnum drv,        // [IN] Storage, can be storageSD (SD card) or storageFlash (flash storage)
			char *songName         // [IN]  Path of audio file in ascii (char*) 
			);
	
	 // DESCRIPTION
	 //    Plays an audio file on SD card or flash storage.
	void    playFile(
			StorageEnum drv,        // [IN] Storage, can be storageSD (SD card) or storageFlash (flash storage)
			wchar_t* songName        // [IN] Path of audio file in unicode (wchar_t*) encoding
			);

	 // DESCRIPTION
	 //    Adjusts the playback volume; range is from 0 (silent) to 6 (maximum).
	void    setVolume(
			unsigned char volume       // [IN] Volume level, can be 0 to 6; 0 as silent and 6 as max volume
			);

	 // DESCRIPTION
	 //    Pauses the playback. It only works when there is an active playback ongoing (by playFile()).
	void    pause(void);

	 // DESCRIPTION
	 //    Resumes playback. It only works when the playback has been paused.
	void    resume(void);

	 // DESCRIPTION
	 //    Stops playback.
	void    stop(void);

	 // DESCRIPTION
	 //    Queries the current playback status.
	 // RETURNS
	 //    AudioStatus: Playback status, can be:
	 //    AudioStop: Playback is stopped.
	 //    AudioPause: Playback is paused (and can resume).
	 //    AudioResume: Playback resumes
	 //    AudioEndOfFile: Playback is finished.
	 //    AudioCommonFailed: Playback fails (e.g. the audio file is corrupted).
	AudioStatus    getStatus(void);
	
public:
	VMSTR getFile();
	char getDriver();
	boolean getType();
	unsigned char getVolume();
	static void onCallback(int result);
private:
	char m_path[256];
	unsigned char  m_volume;
	char m_drv;
	boolean m_type;
};

extern LAudioClass LAudio;

#endif
