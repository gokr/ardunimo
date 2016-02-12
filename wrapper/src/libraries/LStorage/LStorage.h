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



#ifndef _LINKITSTORAGE_h
#define _LINKITSTORAGE_h

#include <Arduino.h>
#include "LTask.h"
#ifdef C2NIM
#include "Stream.h"
#endif

#define LS_WRITE_BUF_SIZE 128
#define LS_MAX_PATH_LEN   260

#ifndef FILE_READ
#define FILE_READ   0x01
#endif

#ifndef FILE_WRITE
#define FILE_WRITE  0x13
#endif

// Class of LinkIt File support 
class LFile : public Stream
{
    friend class LSDClass;

/* DOM-NOT_FOR_SDK-BEGIN */	
// Constructor / Destructor    
public:
    LFile(unsigned int fd, boolean isdir, char drv, const char *name); // wraps an underlying SdFile
    LFile(void);                           // 'empty' constructor
    ~LFile(void);                          // destructor
/* DOM-NOT_FOR_SDK-END */	

// Method
public:
    using Print::write; // pull in write(str) and write(buf, size) from Print

	// DESCRIPTION
	//  Writes data info the file opened with FILE_WRITE mode. Similar to print().
	// RETURNS
	//  Number of bytes written
    virtual size_t write(
        uint8_t v   // [IN] byte to write
    );

    //virtual size_t write(const uint8_t *buf, size_t size);

	// DESCRIPTION
	//  Reads single byte from the file and moves the file cursor 1 step.
    //  In contrast, peek() reads from the file without moving the file cursor
	// RETURNS
	//  One byte of content the file cursor points to
    virtual int read();

	// DESCRIPTION
	//  Reads single byte from file without moving the file cursor.
    //  Due to the cursor is kept at the same place, repeatedly calling peek() will always get the same result.
    //  In contrast, read() moves the file cursor 1 step further.
	// RETURNS
	//  One byte of content the file cursor points to
    virtual int peek();

	// DESCRIPTION
	//  Queries if there are still data to be read (if it reaches the end of file or not).
	// RETURNS
	//  Number of bytes to be read, or 0 if it is the end of file
    virtual int available();

	// DESCRIPTION
	//  Makes sure the data are written into SD/flash storage to prevent data corruption in case of sudden power-off.
    //  Note: close() also guarantees flush() will be done.
    virtual void flush();

	// DESCRIPTION
	//  read array of bytes from file
	// RETURNS
	//  number of bytes read
    int read(
        void *buf,      // [OUT] buffer to retrieve data
        uint16_t nbyte  // [IN] size of buffer
    );

	// DESCRIPTION
	//  Changes the cursor position; can be number from 0 to the size of file.
	//
    //  * Use read() to retrieve the content on the current position and move cursor at the same time.
    //  * Use peek() to retrieve content on the current position without moving the cursor.
    //  * Use position() to get the current cursor position.
	// RETURNS
	//  true: Succeed
	//  false: Fail. The position is not changed.
    boolean seek(
        uint32_t pos    // [IN] new cursor position
    );

	// DESCRIPTION
	//  Returns the position of file cursor.
	//
    //  * Use read() to retrieve content from the current position and move cursor at the same time.
    //  * Use peek() to retrieve content from the current position without moving the cursor.
    //  * Use seek() to change the cursor position.
	// RETURNS
	//  Current position of file cursor
    uint32_t position();

	// DESCRIPTION
	//  Returns the size of file.
	// RETURNS
	//  Size of file
    uint32_t size();
    
	// DESCRIPTION
	//  Closes the file to release resource to prevent leakage.
    //  Make sure the data are completely written to the SD/flash storage.
    void close();

/* DOM-NOT_FOR_SDK-BEGIN */	
    operator bool();
    
    LFile& operator=(const LFile& other);
/* DOM-NOT_FOR_SDK-END */	

	// DESCRIPTION
	//  Returns the name of file.
	// RETURNS
	//  Name of file
    char * name();

	// DESCRIPTION
	//  Folder is a special type of file. isDirectory() is used for knowing if an LFile object is a file or a folder.
	// RETURNS
	//  true: Folder
    //  false: File
    boolean isDirectory(void);

	// DESCRIPTION
	//  Folder is a special type of file. openNextFile() is used for enumerating sub-files in a folder.
    //  It returns the next sub-file or sub-folder in the folder.
	// RETURNS
	//  Next sub-file or sub-folder in the folder
    LFile openNextFile(
        uint8_t mode = FILE_READ    // [IN] open mode, can be FILE_READ or FILE_WRITE
    );

	// DESCRIPTION
	//  Folder is a special type of file. rewindDirectory() is used with openNextFile() to rewind the enumeration and start from the beginning; so that the next openNextFile() call will return the first sub-file (or sub-folder).
    void rewindDirectory(void);

private:
    int _read(void *buf, uint16_t nbyte, boolean peek_mode);

private:
    unsigned int _fd;
    char _name[LS_MAX_PATH_LEN];
    boolean _isDir;
    char _drv;
 
    uint8_t _buf[LS_WRITE_BUF_SIZE];
    uint8_t _bufPos;
};


// Base Class of LinkIt SD/Flash
class LDrive
{
// Constructor / Destructor    
protected:
    LDrive(void) { _drv = 0; };
    ~LDrive(void) {};

// Method
public: 

	// DESCRIPTION
	//  Initialzes the SD or Flash module
	// RETURNS
	//  true if succeed, false if failed
    virtual boolean begin() = 0;

	// DESCRIPTION
	//  Opens a file (or folder).
    //  When the file path does not exist: If FILE_WRITE mode is given, an empty file will be created; if FILE_READ mode is given, it will simply return "fail".
    //
    //  * FILE_READ: Read only, cannot write, starting from the beginning of file (so that you can read its content from the beginning)
    //  * FILE_WRITE: Can read and write, starting from the end of file (so that when you write data it will append to tail). 
    //
	// RETURNS
	//  An LFile object to represent the file (or folder)
    //  If the opening fails. it will return an empty LFile object. An empty LFile object can be evaluated as false, so you can use "if (f)" to test the result.
    LFile open(
        const char *filename,       // [IN] file to open
        uint8_t mode = FILE_READ    // [IN] mode of opening, FILE_READ by default if not specified.
    );

	// DESCRIPTION
	//  Tests the given file exists or not.
	// RETURNS
    //  true: It exists.
    //  false: It does not exist.
    boolean exists(
        char *filepath              // [IN] File (or folder) to check
    )  { return general_op(1, filepath); }

	// DESCRIPTION
	//  Creates folder. It can create multiple sub folders at once; for example, LSD.mkdir("a/b/c") can create a, b, c, 3 folders at the same time.
	// RETURNS
    //	true: Succeed
    //  false: Fail
    boolean mkdir(
        char *filepath              // [IN] Name of the folder to be created. Use "/" to seperate sub-folders. 
    )   { return general_op(2, filepath); }

	// DESCRIPTION
	//  Deletes a file.
	// RETURNS
    //	true: Succeed
    //  false: Fail
    boolean remove(
        char *filepath              // [IN] file to be deleted
    )  { return general_op(3, filepath); }
  
	// DESCRIPTION
	//  Deletes a folder. The folder must be empty, or it will fail.
	// RETURNS
    //	true: Succeed
    //  false: Fail
    boolean rmdir(
        char *filepath              // [IN] folder to be deleted
    )   { return general_op(4, filepath); }

protected:
    char getDrv() {return _drv;}
    void initDrv(char drv_letter) { _drv = drv_letter; };

private:
        
    boolean general_op(int op, char *filepath);

private:
    char _drv;
    
};


#undef LINKITSTORAGE_DEBUG

#ifdef LINKITSTORAGE_DEBUG
#define LSLOG(x) Serial.println(x)
#else
#define LSLOG(x)  
#endif

#endif

