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

#include "LStorage.h"

#include "vmio.h"
#include "vmchset.h"
#include "vmstdlib.h"

/*****************************************************************************
* 
* Utility
* 
*****************************************************************************/

#ifdef LINKITSTORAGE_DEBUG
static void _printwstr(VMWCHAR *filepath_buf)
{
    int i = 0;
    while(filepath_buf[i])
    {
        Serial.write(filepath_buf[i]);
        i++;
    }
    Serial.println();
}
#endif

static boolean _conv_path(char drv, const char* filepath, VMWCHAR *filepath_buf)
{
    int i;
    
    memset(filepath_buf, 0, (LS_MAX_PATH_LEN)*sizeof(VMWCHAR));
    
    filepath_buf[i++] = drv;
    filepath_buf[i++] = ':';
    if(filepath[0] != '/')
        filepath_buf[i++] = '/';

    if (vm_ascii_to_ucs2(filepath_buf+i, (LS_MAX_PATH_LEN-i)*sizeof(VMWCHAR), (char*)filepath) < 0)
        return false;

    i = 0;
    while(filepath_buf[i])
    {
        if(filepath_buf[i] == '/')
            filepath_buf[i] = '\\';
        i++;
    }

#ifdef LINKITSTORAGE_DEBUG
    Serial.print("[conv1]");
    _printwstr(filepath_buf);
#endif

    return true;
}

static boolean _conv_path_back(const VMWCHAR* filepath, char *filepath_buf)
{
    int i = 0;
    
    memset(filepath_buf, 0, (LS_MAX_PATH_LEN)*sizeof(char));
    
    if (vm_ucs2_to_ascii(filepath_buf, (LS_MAX_PATH_LEN)*sizeof(char), (VMWCHAR*)filepath+2) < 0)
        return false;

    while(filepath_buf[i])
    {
        if(filepath_buf[i] == '\\')
            filepath_buf[i] = '/';
        i++;
    }

#ifdef LINKITSTORAGE_DEBUG
    Serial.print("[conv2]");
    LSLOG(filepath_buf);
#endif

    return true;
}

VMFILE linkit_file_open(const VMWSTR filename, VMUINT mode)
{
    if(mode == FILE_READ)
    {
        return vm_file_open(filename, MODE_READ, TRUE);
    }
    else if(mode == FILE_WRITE)
    {
        if(vm_file_get_attributes(filename) < 0)
        {
            return vm_file_open(filename, MODE_CREATE_ALWAYS_WRITE, TRUE);
        }
        else
        {
            VMFILE fd = vm_file_open(filename, MODE_WRITE, TRUE);
            vm_file_seek(fd, 0, BASE_END);
            return fd;
        }
    }
    else
        return -1;
}

/*****************************************************************************
* 
* structure data between Arduino / MMI thread
* 
*****************************************************************************/

struct linkit_file_general_struct
{
    VMUINT fd;
    VMINT result;
    VMUINT value;
};

struct linkit_file_flush_struct
{
    VMUINT fd;
    VMINT result;
    void *buf;
    VMUINT nbyte;
};

struct linkit_file_read_struct
{
    VMUINT fd;
    VMINT result;
    void *buf;
    VMUINT nbyte;
    boolean peek_mode;

};

struct linkit_file_seek_struct
{
    VMUINT fd;
    VMINT result;
    VMINT pos;
};

struct linkit_file_find_struct
{
    VMUINT findhdl;
    char *findpath;
    VMWCHAR drv;
    uint8_t mode;

    uint8_t is_dir;
    VMUINT fd;
    VMINT result;   // 0: ok, <0: error
    char name[LS_MAX_PATH_LEN];
};

boolean linkit_file_read_handler(void* userdata);
boolean linkit_file_seek_handler(void* userdata);
boolean linkit_file_position_handler(void* userdata);
boolean linkit_file_size_handler(void* userdata);
boolean linkit_file_close_handler(void* userdata);
boolean linkit_file_available_handler(void* userdata);
boolean linkit_file_flush_handler(void* userdata);
boolean linkit_file_find_handler(void* userdata);
boolean linkit_file_find_close_handler(void* userdata);

struct linkit_drv_general_op_struct
{
    const char *filepath;
    VMINT op;
    VMINT result;
    VMWCHAR drv;
};

struct linkit_drv_open_struct
{
    const char *filepath;
    VMINT mode;
    VMINT result;
    VMUINT fd;
    VMINT is_dir;    
    VMWCHAR drv;
};

boolean linkit_drv_general_handler(void* userdata);
boolean linkit_drv_read_handler(void* userdata);

struct linkit_file_handle_struct
{
    VMINT _hdl;
    VMINT _ref;
};

#define HDL(fd)  ((linkit_file_handle_struct*)fd)->_hdl
#define REF(fd) ((linkit_file_handle_struct*)fd)->_ref

/*****************************************************************************
* 
* LFile class
* 
*****************************************************************************/


LFile::LFile()
{
    _fd = 0;
    _isDir = false;
    _name[0] = 0;
    _drv = 0;
    _bufPos = 0;
}

LFile::LFile(unsigned int fd, boolean isdir, char drv, const char* name)
{
    _fd = fd;
    _isDir = isdir;
    _drv = drv;
    strncpy(_name, name, LS_MAX_PATH_LEN);
    _bufPos = 0;
}

LFile::~LFile()
{
    close();
}

size_t LFile::write(uint8_t v)
{
    if(!_fd || _isDir)
        return 0;

    _buf[_bufPos++] = v;
    if(_bufPos == LS_WRITE_BUF_SIZE)
        flush();
    return 1;
}

int LFile::read()
{
    uint8_t buf[1];
    int result;
 
    if(!_fd || _isDir)
        return -1;
    
    result = _read(buf, 1, false);
    if(result < 0)
        return result;
        
    return buf[0];
}

int LFile::peek()
{
    uint8_t buf[1];
    int result;
    
    if(!_fd || _isDir)
        return -1;

    result = _read(buf, 1, true);
    if(result < 0)
        return result;
        
    return buf[0];
}

int LFile::available()
{
    linkit_file_general_struct data;
    
    if(!_fd || _isDir)
        return -1;

    data.fd = _fd;

    LTask.remoteCall(linkit_file_available_handler, &data);
    
    return data.result;
}

void LFile::flush()
{
    linkit_file_flush_struct data;
    
    if(!_fd || _isDir || _bufPos == 0)
        return;

    data.fd = _fd;
    data.buf = _buf;
    data.nbyte = _bufPos;

    LTask.remoteCall(linkit_file_flush_handler, &data);

    _bufPos = 0;
}

int LFile::read(void *buf, uint16_t nbyte)
{
    return _read(buf, nbyte, false);
}

int LFile::_read(void *buf, uint16_t nbyte, boolean peek_mode)
{
    linkit_file_read_struct data;
    
    if(!_fd || _isDir)
        return -1;

    data.fd = _fd;
    data.buf = buf;
    data.nbyte = nbyte;
    data.peek_mode = peek_mode;

    LTask.remoteCall(linkit_file_read_handler, &data);
    
    return data.result;
}

boolean LFile::seek(uint32_t pos)
{
    linkit_file_seek_struct data;
    
    if(!_fd || _isDir)
        return false;

    data.fd = _fd;
    data.pos = pos;

    LTask.remoteCall(linkit_file_seek_handler, &data);
    
    return data.result;
}

uint32_t LFile::position()
{
    linkit_file_general_struct data;
    
    if(!_fd || _isDir)
        return 0;

    data.fd = _fd;

    LTask.remoteCall(linkit_file_position_handler, &data);
    
    return data.value;
}

uint32_t LFile::size()
{
    linkit_file_general_struct data;
    
    if(!_fd || _isDir)
        return 0;

    data.fd = _fd;

    LTask.remoteCall(linkit_file_size_handler, &data);
    
    return data.value;
}

void LFile::close()
{
    linkit_file_general_struct data;
    
    if(!_fd)
        return;

    flush();
        
    data.fd = _fd;

    if(_isDir)
        LTask.remoteCall(linkit_file_find_close_handler, &data);
    else
        LTask.remoteCall(linkit_file_close_handler, &data);
        
    _fd = 0;
}

LFile::operator bool()
{
    return (_fd || _isDir) ? true : false;
}

LFile& LFile::operator=(const LFile& other)
{
    memcpy(this, &other, sizeof(LFile));
    if(_fd)
        REF(_fd)++;
        
    return *this;
}

char * LFile::name()
{
    int i, len = strlen(_name);
    if (len == 1)
        return _name;
        
    for(i=len-2;i--;i>=0)
        if(_name[i]=='/')
            break;
            
    i++;
    return _name+i;
}

boolean LFile::isDirectory(void)
{
    if(_isDir)
        return true;

    return false;
}

LFile LFile::openNextFile(uint8_t mode)
{
    linkit_file_find_struct data = {0};
    if (!_isDir)
        return LFile();
        
    data.mode = mode;
    data.drv = _drv;
    data.findpath = _name;
    data.findhdl = _fd;

    LTask.remoteCall(linkit_file_find_handler, &data);

    _fd = data.findhdl;

    if (data.result < 0)
    {
        return LFile();
    }
    
    return LFile(data.fd, data.is_dir, _drv, data.name);
}

void LFile::rewindDirectory(void)
{
    linkit_file_general_struct data;
    if (!_isDir || !_fd)
        return;

    data.fd = _fd;
    LTask.remoteCall(linkit_file_find_close_handler, &data);
    _fd = 0;
}

/*****************************************************************************
* 
* LFile MMI part (running on MMI thread)
* 
*****************************************************************************/

boolean linkit_file_read_handler(void* userdata)
{
    linkit_file_read_struct *data = (linkit_file_read_struct*)userdata;
    VMUINT read;

    data->result = vm_file_read(HDL(data->fd), data->buf, data->nbyte, &read);
    
    if(data->peek_mode)
    {
        // peek mode, rewind back
        vm_file_seek(HDL(data->fd), -read, BASE_CURR);
    }
    
    return true;
}

boolean linkit_file_seek_handler(void* userdata)
{
    linkit_file_seek_struct *data = (linkit_file_seek_struct*)userdata;

    data->result = vm_file_seek(HDL(data->fd), data->pos, BASE_BEGIN);
    
    return true;
}

boolean linkit_file_position_handler(void* userdata)
{
    linkit_file_general_struct *data = (linkit_file_general_struct*)userdata;

    data->result = vm_file_tell(HDL(data->fd));
    
    if(data->result >= 0)
        data->value = data->result;
    else
        data->value = 0;

    return true;
}

boolean linkit_file_size_handler(void* userdata)
{
    linkit_file_general_struct *data = (linkit_file_general_struct*)userdata;
    VMUINT size;

    data->result = vm_file_getfilesize(HDL(data->fd), &size);
    if (data->result == 0)
        data->value = size;
    else
        data->value = 0;
        
    return true;
}

boolean linkit_file_close_handler(void* userdata)
{
    linkit_file_general_struct *data = (linkit_file_general_struct*)userdata;

    REF(data->fd)--;
    if(REF(data->fd) == 0)
    {
        vm_file_close(HDL(data->fd));
        free((void*)data->fd);
        data->fd = 0;
    }
    
    return true;
}

boolean linkit_file_available_handler(void* userdata)
{
    linkit_file_general_struct *data = (linkit_file_general_struct*)userdata;
    
    VMUINT size = 0;
    VMINT pos = 0;

    vm_file_getfilesize(HDL(data->fd), &size);
    pos = vm_file_tell(HDL(data->fd));

    if(!size || pos < 0)
    {
        data->result = pos;
    }
    else
    {
        size -= pos;
        data->result = size > 0x7FFF ? 0x7FFF : size;  // follow Arduino File.cpp's rule
    }
    
    return true;
}

boolean linkit_file_flush_handler(void* userdata)
{
    linkit_file_flush_struct *data = (linkit_file_flush_struct*)userdata;

    if(data->nbyte)
    {
        VMUINT written;
        vm_file_write(HDL(data->fd), data->buf, data->nbyte, &written);
    }

    data->result = vm_file_commit(HDL(data->fd));
    
    return true;    
}

boolean linkit_file_find_handler(void* userdata)
{
    linkit_file_find_struct *data = (linkit_file_find_struct*)userdata;
    VMWCHAR filepath_buf[LS_MAX_PATH_LEN];
    vm_fileinfo_t info;
    VMINT attr;
    VMINT findhdl;
    
    data->result = -1;

    if(!_conv_path(data->drv, data->findpath, filepath_buf))
        return true;

    int len = vm_wstrlen(filepath_buf);
    if(filepath_buf[len-1] != '\\')
    {
        filepath_buf[len] = '\\';
        filepath_buf[len+1] = 0;
        len++;
    }
    
    if(!data->findhdl)
    {
        filepath_buf[len] = '*';
        filepath_buf[len+1] = 0;

#ifdef LINKITSTORAGE_DEBUG
        Serial.print("[find]");
        _printwstr(filepath_buf);
#endif

        findhdl = vm_find_first(filepath_buf, &info);
        if(findhdl < 0)
            return true;

        // skip . and ..
        while(  (info.filename[0] == '.' && info.filename[1] == 0) ||
                (info.filename[0] == '.' && info.filename[1] == '.' && info.filename[2] == 0) )
        {
            data->result = vm_find_next(findhdl, &info);
            if(data->result < 0)
            {
                vm_find_close(findhdl);
                return true;
            }
        }
        
        data->findhdl = (VMUINT)malloc(sizeof(linkit_file_handle_struct));
        HDL(data->findhdl) = findhdl;
        REF(data->findhdl) = 1;
    }
    else
    {
        findhdl = HDL(data->findhdl);
        data->result = vm_find_next(findhdl, &info);
        if(data->result < 0)
            return true;
    }

    vm_wstrcpy(filepath_buf+len, info.filename);
    
    attr = vm_file_get_attributes(filepath_buf);
    if (attr >= 0 && attr & VM_FS_ATTR_DIR)
    {
        LSLOG("[find]dir");
        data->is_dir = true;
        data->result = 0;
        data->fd = 0;
    }
    else if(attr < 0) // special case for SD label entry
    {
#ifdef LINKITSTORAGE_DEBUG
        Serial.print("[find]SD label?:");
        _printwstr(filepath_buf);
#endif
        data->is_dir = true;
        data->result = 0;        
        data->fd = 0;
    }
    else
    {
        LSLOG("[find]file");
        data->is_dir = false;
        data->result = linkit_file_open(filepath_buf, data->mode);
        if(data->result < 0)
        {
            REF(data->findhdl)--;
            if(REF(data->findhdl) == 0)
            {
                vm_find_close(HDL(data->findhdl));
                free((void*)data->findhdl);
                data->findhdl = 0;
            }
        }
        else
        {
            data->fd = (VMUINT)malloc(sizeof(linkit_file_handle_struct));
            HDL(data->fd) = data->result;
            REF(data->fd) = 1;
        }
    }
    _conv_path_back(filepath_buf, data->name);
    
    return true;
}

boolean linkit_file_find_close_handler(void* userdata)
{
    linkit_file_general_struct *data = (linkit_file_general_struct*)userdata;

    REF(data->fd)--;
    if(REF(data->fd) == 0)
    {
        vm_find_close(HDL(data->fd));
        free((void*)data->fd);
        data->fd = 0;
    }

    return true;
}

/*****************************************************************************
* 
* LDrive class
* 
*****************************************************************************/


boolean LDrive::general_op(int op, char *filepath)
{
    linkit_drv_general_op_struct data;
    
    data.filepath = filepath;
    data.op = op;
    data.drv = _drv;

    LTask.remoteCall(linkit_drv_general_handler, &data);
    
    return data.result;
}

LFile LDrive::open(const char *filename, uint8_t mode)
{
    linkit_drv_open_struct data;
    
    data.filepath = filename;
    data.mode = mode;
    data.drv = _drv;

    LTask.remoteCall(linkit_drv_read_handler, &data);

    if (!data.result)   // fail, return empty object
    {
        LSLOG("open() fail");
        return LFile();
    }

    return LFile(data.fd, data.is_dir, _drv, filename);
}

/*****************************************************************************
* 
* LFile MMI part (running on MMI thread)
* 
*****************************************************************************/

static int recur_mkdir(VMWCHAR* path)
{
    int result;
    VMWCHAR *pos;
    
    // check if already exist
    result = vm_file_get_attributes(path);
    if(result >= 0)
        return -1;  // already exist
    
    pos = path+3;
    while(*pos)
    {
        if(*pos == '\\')
        {
            *pos = 0;
            vm_file_mkdir(path);
            *pos = '\\';
        }
        pos++;
    }
    vm_file_mkdir(path);
    
    // check if final path exist
    result = vm_file_get_attributes(path);
    if(result >= 0)
        result = 0; // succeed
        
    return result;
}

boolean linkit_drv_general_handler(void* userdata)
{
    linkit_drv_general_op_struct *data = (linkit_drv_general_op_struct*)userdata;
    VMWCHAR filepath_buf[LS_MAX_PATH_LEN];
    int result;

    data->result = false;
    
    if(!_conv_path(data->drv, data->filepath, filepath_buf))
        return true;

    switch(data->op)
    {
    case 1: // exists
        result = vm_file_get_attributes(filepath_buf);
        break;

    case 2: // mkdir
        result = recur_mkdir(filepath_buf);
        break;

    case 3: // remove
        result = vm_file_delete(filepath_buf);
        break;

    case 4: // rmdir
        result = vm_file_rmdir(filepath_buf);
        break;
    }

#ifdef LINKITSTORAGE_DEBUG
    Serial.print("[gen_op]");
    Serial.print(data->op);
    Serial.print(":");
    Serial.println(result);
#endif
    
    data->result = result < 0 ? false : true;
    return true;
}

boolean linkit_drv_read_handler(void* userdata)
{
    linkit_drv_open_struct *data = (linkit_drv_open_struct*)userdata;
    VMWCHAR filepath_buf[LS_MAX_PATH_LEN];
    VMINT attr;
    VMINT fd;

    data->result = false;
    
    if(!_conv_path(data->drv, data->filepath, filepath_buf))
    {
        return true;
    }

    // identify if this is a file or dir
    attr = vm_file_get_attributes(filepath_buf);
        
    if (attr >= 0 && attr & VM_FS_ATTR_DIR)
    {
        data->is_dir = true;
        data->fd = 0;
        data->result = true;
        LSLOG("open ok (dir)");
    }
    else
    {
        data->is_dir = false;
        fd = linkit_file_open(filepath_buf, data->mode);
        if (fd > 0)
        {
            LSLOG("open ok (file)");
            data->result = true;
            
            data->fd = (VMUINT)malloc(sizeof(linkit_file_handle_struct));
            HDL(data->fd) = fd;
            REF(data->fd) = 1;
        }
    }
    
    return true;
}


