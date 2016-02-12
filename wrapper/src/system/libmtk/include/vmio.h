/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef VMIO_SDK_H_
#define VMIO_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmsim.h"
#include "vmtel.h"
#include "vmtouch.h"
#include "vmkeypad.h"
#include "vminput.h"

#ifndef MAX_APP_NAME_LEN
#define MAX_APP_NAME_LEN					(260)
#endif

typedef enum 
{
	VM_FILE_COMMIT_ERROR = -1,
	VM_FILE_OPEN_ERROR = -2,
	VM_FILE_NAME_ERROR = -1,
	VM_FILE_OK = 0
} vm_file_error_t;

typedef enum
{
      VM_STORE_PATH_TYPE_PHOTO,
      VM_STORE_PATH_TYPE_VIDEO,
      VM_STORE_PATH_TYPE_MUSIC,
      VM_STORE_PATH_TYPE_RINGTONE,
      VM_STORE_PATH_TYPE_DOCUMENT,
      VM_STORE_PATH_TYPE_OTHERS

} VM_STORE_PATH_TYPE;

/*
 * file attribution
 */
#define VM_FS_ATTR_READ_ONLY        	0x01
#define VM_FS_ATTR_HIDDEN           	0x02
#define VM_FS_ATTR_SYSTEM           	0x04
#define VM_FS_ATTR_VOLUME          	0x08
#define VM_FS_ATTR_DIR              		0x10
#define VM_FS_ATTR_ARCHIVE          	0x20
#define VM_FS_LONGNAME_ATTR         	0x0F

/* file info */
struct vm_fileinfo_t
{
	VMWCHAR filename[MAX_APP_NAME_LEN]; /* full path of file */
	VMINT size; /* file size */
};

/* file info */
typedef  struct  vm_fileinfo_ext
{
    /* file name without path */
    VMWCHAR filefullname[MAX_APP_NAME_LEN];
    /* file name character array by 8.3 format encoding with UCS2, and the last character may be not '\0' */
    VMCHAR filename[8];
    /* file extention name character array by 8.3 format encoding with UCS2, and the last character may be not '\0' */
    VMCHAR extension[3];/* file attributes */
   VMBYTE           attributes; 
   vm_time_t       create_datetime; /* create time */
   vm_time_t	    modify_datetime; /* modify time */
   VMUINT           filesize; /* file size */
   VMUINT           drive; /* drive */
   VMUINT           stamp; /* stamp */
} vm_fileinfo_ext;

/* Disk information */
typedef struct
{
    /* A zero-terminated <color Red><b>Short File Name</b></color> with the volume's label. */
    VMCHAR            Label[24];

    /* The drive letter in <color Red><b>UPPER</b></color> case. */
    VMCHAR            DriveLetter;

    /* Indicate the disk is in write protection or not. 1 for protect, 0 for not protect. */
    VMUINT8            WriteProtect;

    /* Reserved fields */
    VMCHAR            Reserved[2];

    /* The volume's serial number. */
    VMUINT32            SerialNumber;

    /* The LBA address of the logical drive's boot record. For diskettes, this value will be 0. */
    VMUINT32            FirstPhysicalSector;

    /* 2, 16, or 32 for FAT-12, FAT-16, or FAT-32 */
    VMUINT32            FATType;

    /* The number of FATs on the volume. */
    VMUINT32            FATCount;

    /* The number of FATs on the volume. */
    VMUINT32            MaxDirEntries;

    /* The sector size. This value will usually be 512. */
    VMUINT32            BytesPerSector;

    /* Specifies the size of the smallest unit of storage that can be allocated to a file in sectors. */
    VMUINT32            SectorsPerCluster;

    /* Number of clusters for file storage on the volume. */
    VMUINT32            TotalClusters;

    /* The number of clusters, which are marked bad and are unavailable for file storage. */
    VMUINT32            BadClusters;

    /* The number of clusters currently available. */
    VMUINT32            FreeClusters;

    /* The number of files on the volume including directories, but not counting the root directory and files with an allocated file size of 0. */
    VMUINT32            Files;

    /* The number of contiguous cluster chains. On a completely unfragmented volume, this value would be identical to Files. */
    VMUINT32            FileChains;

    /* The number of contiguous cluster chains of free clusters. On a completely unfragmented volume, this value would be 1. */
    VMUINT32            FreeChains;

    /* The maximum allocated file size for a newly allocated contiguous file in clusters. On a completely unfragmented volume, this value would be identical to FreeClusters. */
    VMUINT32            LargestFreeChain;
} vm_fs_disk_info;

/* vm_get_disk_info Parameter */
typedef enum
{
    /*
     * Returns all fields in structure vm_get_disk_info except FreeClusters, BadClusters, Files, FileChains, FreeChains, LargestFreeChain.
     * <color Red><b>This flag never requires a FAT scan.</b></color>
     */
    VM_FS_DI_BASIC_INFO     =  0x00000001L,

    /*
     * Returns field FreeClusters. This flags may require FS to scan the complete FAT if the amount of free space is not known.
     * In this case, FS_DI_FAT_STATISTICS is returned in addition to FS_DI_FREE_SPACE.
     */
    VM_FS_DI_FREE_SPACE     =  0x00000002L,

    /*
     * Returns fields BadClusters, Files, FileChains, FreeChains, LargestFreeChain.
     * This flag will always cause FS to scan the complete FAT.
     */
    VM_FS_DI_FAT_STATISTICS =  0x00000004L,

    /*
     * Get volume label of the target drive. The maximum length is 11 wide characters.
     * <color Red><b>This option must be used with FS_DI_BASIC_INFO.</b></color>
     */
    VM_FS_DI_VOLUME_LABEL   =  0x00000008L,

    VM_FS_DI_INVALID
}vm_fs_di_enum;


/**
 * open file with file Read-Only mode.
 */
#define MODE_READ					1

/**
 * open file with Read-Write mode.
 */
#define MODE_WRITE					2

/**
 * open file with Read-Write mode, create if the file not exist.
 */
#define MODE_CREATE_ALWAYS_WRITE	4

/**
 * open file with Append mode.
 */
#define MODE_APPEND					8

/*****************************************************************************
* FUNCTION
 *    vm_file_open
 * DESCRIPTION
 *  open file 
 * PARAMETERS
 *  filename : [IN]  file full path encoding with UCS2
 *  mode : [IN] file open mode:
 *                MODE_READ: Read-Only
 *                MODE_WRITE : Read-Write
 *                MODE_CREATE_ALWAYS_WRITE : Read-Write mode, create if the file not exist.
 *  binary : [IN] TRUE means open with binary format, FALSE means open with ASCII format.
 * RETURNS
 *  non-negative file handle if successfully, and error code if failed to open. 
 *
*****************************************************************************/
VMFILE vm_file_open(const VMWSTR filename, VMUINT mode, VMUINT binary);

/*****************************************************************************
* FUNCTION
 *    vm_file_close
 * DESCRIPTION
 *  close file 
 * PARAMETERS
 *  handle : [IN]  file handle to be closed.
 *
*****************************************************************************/
void vm_file_close(VMFILE handle);

/*****************************************************************************
* FUNCTION
 *    vm_file_read
 * DESCRIPTION
 *  read file from current pointer of file
 * PARAMETERS
 *  handle : [IN]  file handle to be read.
 *  data : [OUT] output data address
 *  length : [IN] bytes to be read
 *  nread : [IN] bytes read actually
 * RETURNS
 *  bytes of read data if > 0, 0 means error happened or reach end of file.
 *
*****************************************************************************/
VMINT vm_file_read(VMFILE handle, void * data, VMUINT length, VMUINT *nread);

/*****************************************************************************
* FUNCTION
 *    vm_file_write
 * DESCRIPTION
 *  write data to current pointer of the file
 * PARAMETERS
 *  handle : [IN]  file handle to write.
 *  data : [IN] the address of data to be written
 *  length : [IN] bytes to be written
 *  written : [IN] bytes written actually
 * RETURNS
 *  bytes of written data if > 0, 0 means error happened.
 *
*****************************************************************************/
VMINT vm_file_write(VMFILE handle, void * data, VMUINT length, VMUINT * written);

/*****************************************************************************
* FUNCTION
 *    vm_file_commit
 * DESCRIPTION
 *  commit the I/O cache data to file.
 * PARAMETERS
 *  handle : [IN]  file handle to commit.
 * RETURNS
 *  0 means successfully, non-zero is error code.
 *
*****************************************************************************/
VMINT vm_file_commit(VMFILE handle);

#define BASE_BEGIN		1
#define BASE_CURR		2
#define BASE_END		3

/*****************************************************************************
* FUNCTION
 *    vm_file_seek
 * DESCRIPTION
 *  move the file pointer to specified position. If exceed file size, this operation will return error.
 * PARAMETERS
 *  handle : [IN]  file handle to seek.
 *  offset : [IN]  bytes to move.
 *  base: [IN]  base position to move.
 *          BASE_BEGIN means from begin of file;
 *          BASE_CURR means from current position; 
 *          BASE_END means from end of file.
 * RETURNS
 *  0 means successfully, non-zero is error code.
 * 
*****************************************************************************/
VMINT vm_file_seek(VMFILE handle, VMINT offset, VMINT base);

/*****************************************************************************
* FUNCTION
 *    vm_file_tell
 * DESCRIPTION
 *  get the position of current pointer of file.
 * PARAMETERS
 *  handle : [IN]  file handle.
 * RETURNS
 *  current pointer position,  or negative number error code if failed.
 *
*****************************************************************************/
VMINT vm_file_tell(VMFILE handle);

/*****************************************************************************
* FUNCTION
 *    vm_file_is_eof
 * DESCRIPTION
 *  check if the current pointer is end of file or not.
 * PARAMETERS
 *  handle : [IN]  file handle.
 * RETURNS
 *  current pointer is end of file or not.
 * RETURN VALUES                                      
 *  TRUE : current pointer is end of file.
 *  FALSE : current pointer is not end of file.
 *
*****************************************************************************/
VMINT vm_file_is_eof(VMFILE handle);

/*****************************************************************************
* FUNCTION
 *    vm_file_getfilesize
 * DESCRIPTION
 *  get file size by byte.
 * PARAMETERS
 *  handle : [IN]  file handle.
 *  file_size : [OUT] output the file size by byte
 * RETURNS
 *  get file size successfully or failed
 * RETURN VALUES                                      
 *  0 : get file size successfully.
 *  non-zero : failed to get file size
 * 
*****************************************************************************/
VMINT vm_file_getfilesize(VMFILE handle, VMUINT *file_size);

/*****************************************************************************
* FUNCTION
 *    vm_file_delete
 * DESCRIPTION
 *  delete specified file.
 * PARAMETERS
 *  filename : [IN]  file name full path  encoding with UCS2 format.
 * RETURNS
 *  delete file successfully or failed
 * RETURN VALUES                                      
 *  0 : delete file successfully.
 *  non-zero : failed to delete file.
 * 
*****************************************************************************/
VMINT vm_file_delete(const VMWSTR filename);

/*****************************************************************************
* FUNCTION
 *    vm_file_rename
 * DESCRIPTION
 *  delete specified file.
 * PARAMETERS
 *  filename : [IN]  old file name full path encoding with UCS2 format.
 *  newname : [IN]  new file name full path encoding with UCS2 format.
 * RETURNS
 *  rename file successfully or failed
 * RETURN VALUES                                      
 *  0 : rename file successfully.
 *  non-zero : failed to rename file.
 * 
*****************************************************************************/
VMINT vm_file_rename(const VMWSTR filename, const VMWSTR newname);

/*****************************************************************************
* FUNCTION
 *    vm_file_mkdir
 * DESCRIPTION
 *  create new directory with specified path name.
 * PARAMETERS
 *  dirname : [IN]  path name encoding with UCS2 format.
 * RETURNS
 *  create directory successfully or failed
 * RETURN VALUES                                      
 *  0 : create directory successfully.
 *  non-zero : failed to create directory.
 *
*****************************************************************************/
VMINT vm_file_mkdir(const VMWSTR dirname);

/*****************************************************************************
* FUNCTION
 *    vm_file_rmdir
 * DESCRIPTION
 *  remove directory with specified path name.
 * PARAMETERS
 *  dirname : [IN]  path name encoding with UCS2 format.
 * RETURNS
 *  remove directory successfully or failed
 * RETURN VALUES                                      
 *  0 : remove directory successfully.
 *  non-zero : failed to remove directory.
 *
*****************************************************************************/
VMINT vm_file_rmdir(const VMWSTR dirname);

/*****************************************************************************
* FUNCTION
 *    vm_file_set_attributes
 * DESCRIPTION
 *  set attributes of specified full path file name encoding with UCS2 format. The attributes
 *  can not include VM_FS_ATTR_VOLUME, VM_FS_ATTR_DIR, or VM_FS_LONGNAME_ATTR.
 *  The value of attributes is the result of OR operator.
 * PARAMETERS
 *  filename : [IN]  file name encoding with UCS2 format.
 *  attributes : [IN]  file attributes.
 * RETURNS
 *  set attributes successfully or failed
 * RETURN VALUES                                      
 *  0 : set attributes successfully.
 *  non-zero : failed to set attributes.
 *
*****************************************************************************/
VMINT vm_file_set_attributes(const VMWSTR filename, VMBYTE attributes);

/*****************************************************************************
* FUNCTION
 *    vm_file_get_attributes
 * DESCRIPTION
 *  set attributes of specified full path file name encoding with UCS2 format. 
 *  The value of attributes is the result of OR operator.
 * PARAMETERS
 *  filename : [IN]  file name encoding with UCS2 format.
 * RETURNS
 *  get attributes successfully or failed
 * RETURN VALUES                                      
 *  -1 : failed to get attributes.
 *  else : get the attributes value.
 *
*****************************************************************************/
VMINT vm_file_get_attributes(const VMWSTR filename);

/*****************************************************************************
* FUNCTION
 *    vm_find_first
 * DESCRIPTION
 *  find files from specified path, support wild character finding.
 * PARAMETERS
 *  pathname : [IN]  path name encoding with UCS2 format.
 *  info : [OUT] result of finding
 * RETURNS
 *  find handle or error code
 * RETURN VALUES                                      
 *  non-negative number : find handle.
 *  negative number : error code.
 *
*****************************************************************************/
VMINT vm_find_first(VMWSTR pathname, struct vm_fileinfo_t* info);

/*****************************************************************************
* FUNCTION
 *    vm_find_next
 * DESCRIPTION
 *  continue to find next file.
 * PARAMETERS
 *  handle : [IN]  find handle.
 *  info : [OUT] result of finding
 * RETURNS
 *  find handle or error code
 * RETURN VALUES                                      
 *  0 : find next file successfully.
 *  negative number : end of finding.
 *
*****************************************************************************/
VMINT vm_find_next(VMINT handle, struct vm_fileinfo_t* info);

/*****************************************************************************
* FUNCTION
 *    vm_find_close
 * DESCRIPTION
 *  close finding process.
 * PARAMETERS
 *  handle : [IN]  find handle.
 *
*****************************************************************************/
void vm_find_close(VMINT handle);

#define vm_get_removable_driver vm_get_removeable_driver
/*****************************************************************************
* FUNCTION
 *    vm_get_removable_driver
 * DESCRIPTION
 *  get drive letter of removable disk, which normally is memory card.
 * RETURNS
 *  drive letter of removable disk. negative number means no removable drive.
 *
*****************************************************************************/
VMINT vm_get_removable_driver(void);

/*****************************************************************************
* FUNCTION
 *    vm_get_system_driver
 * DESCRIPTION
 *  get drive letter of phone disk, which normally is public drive.
 * RETURNS
 *  drive letter of phone disk. negative number means no public drive.
 *
*****************************************************************************/
VMINT vm_get_system_driver(void);

/*****************************************************************************
* FUNCTION
 *    vm_get_disk_free_space
 * DESCRIPTION
 *  get free space by byte of specified drive.
 * PARAMETERS
 *  drv_name : [IN]  drive letter string terminated with '\0' .
 * RETURNS
 *  free space by byte. 0 means specified disk does not exist.
 * 0xFFFFFFFF means exceed the max limitation, the free space size lager than this value.
 * another choice to use vm_get_disk_info
 * 
* EXAMPLE                                  [this TAG is optional]
 * <code>
 * VMINT sys_driver = -1;
 * VMUINT sys_driver_size = 0;
 * if ((sys_driver = vm_get_system_driver()) >= 0)
 * {
 *     VMCHAR driver_str[2] = {0};
 *     
 *     sprintf(driver_str, "%c", (VMCHAR)sys_driver);
 *     sys_driver_size = vm_get_disk_free_space(vm_ucs2_string(driver_str));
 * }
 * </code>
*****************************************************************************/
VMUINT vm_get_disk_free_space(VMWSTR drv_name);

/*****************************************************************************
 * FUNCTION
 *  vm_get_disk_info
 * DESCRIPTION
 *  Return information about a logical drive
 * PARAMETERS
 *  DriveName   :   [IN] <P>Must be a valid file name, e.g., a root directory name. 
 * Only the drive information (possibly the current default drive) is determined.
 *  DiskInfo    :   [OUT]<P>Refer to vm_fs_disk_info.
 *  Flags       :   [IN] <P>Refer to vm_fs_di_enum.
 * RETURNS
 *  success if >= 0, else failure.
 *****************************************************************************/
VMINT vm_get_disk_info(const VMCHAR * drv_name, vm_fs_disk_info * fs_disk, vm_fs_di_enum e_di);

/*****************************************************************************
* FUNCTION
 *    vm_file_get_modify_time
 * DESCRIPTION
 *  get the latest modified time of specified file.
 * PARAMETERS
 *  filename : [IN]  file name of full path encoding with UCS2 format.
 *  modify_time : [OUT]  output the latest modified time
 * RETURNS
 *  0 means get modified time successfully, -1 means failed.
 *
*****************************************************************************/
VMINT vm_file_get_modify_time(const VMWSTR filename, vm_time_t * modify_time);

/*****************************************************************************
* FUNCTION
 *    vm_find_first_ext
 * DESCRIPTION
 *  find files from specified path, support wild character finding.
 * PARAMETERS
 *  pathname : [IN]  path name encoding with UCS2 format.
 *  direntry : [OUT] result of finding
 * RETURNS
 *  find handle or error code
 * RETURN VALUES                                      
 *  non-negative number : find handle.
 *  negative number : error code.
 *
*****************************************************************************/
VMINT vm_find_first_ext(VMWSTR pathname, vm_fileinfo_ext * direntry);

/*****************************************************************************
* FUNCTION
 *    vm_find_next_ext
 * DESCRIPTION
 *  continue to find next file.
 * PARAMETERS
 *  handle : [IN]  find handle.
 *  direntry : [OUT] result of finding
 * RETURNS
 *  find handle or error code
 * RETURN VALUES                                      
 *  0 : find next file successfully.
 *  negative number : end of finding.
 *
*****************************************************************************/
VMINT vm_find_next_ext(VMINT handle,  vm_fileinfo_ext * direntry);

/*****************************************************************************
* FUNCTION
 *    vm_find_close_ext
 * DESCRIPTION
 *  close finding process.
 * PARAMETERS
 *  handle : [IN]  find handle.
 *
*****************************************************************************/
void vm_find_close_ext(VMINT handle);

typedef struct
{
    VMUINT8 home_city;
    VMUINT8 foreign_city;
    VMUINT8 date_seperator;
    VMUINT8 date_format;
    VMUINT8 time_format;
    VMINT current_dst;

    VMUINT8 current_city;
    float current_timezone;
    
    VMUINT8 foreign_index;
    VMUINT8 wc_dst;
    VMUINT8 setting_dt_dst;
    VMUINT16 timezone;
    VMUINT16 frn_timezone;

    VMUINT8     wc_entry_screen;    /* wc_entry_screen, 0:worldclock, 1:homecity, 2:foreigncity */
    VMUINT8     tz_city_match;      /* tz_city_match, 0:Not Match, 1:Match */
} vm_phoneset_info_struct;


/* DOM-NOT_FOR_SDK-BEGIN */


/* error code of storage */
typedef enum
{
    VM_STORAGE_ERR_RES = -10, /* resource is not enough */
    VM_STORAGE_ERR_PARAM = -9, /* input param error */
    VM_STORAGE_ERR_FILE_CREATE = -8, /* sto create failure */
    VM_STORAGE_ERR_FILE_OPEN = -7, /* sto open failure */
    VM_STORAGE_ERR_FILE_SEEK = -6, /* sto seek failure */
    VM_STORAGE_ERR_FILE_WRITE = -5, /* sto wirte failure */
    VM_STORAGE_ERR_FILE_READ = -4, /* sto read failure */
    VM_STORAGE_ERR_AUTHORIZATION = -3, /* no authorization */
    VM_STORAGE_ERR_NONE = 0 /* no error */
}vm_storage_error_type;

/*****************************************************************************
 * FUNCTION
 *  vm_storage_open
 * DESCRIPTION
 *  open storage.
 * PARAMETERS
 *  void
 * RETURNS
 *  storage handle or error code
 * RETURN VALUES
 *  vm_storage_error_type
*****************************************************************************/
VMINT vm_storage_open(void);

/*****************************************************************************
 * FUNCTION
 *  vm_storage_close
 * DESCRIPTION
 *  close storage.
 * PARAMETERS
 *  h : [IN] handle of storage
*****************************************************************************/
void vm_storage_close(VMINT h);

/*****************************************************************************
 * FUNCTION
 *  vm_storage_read
 * DESCRIPTION
 *  read data from storage.
 * PARAMETERS
 *  h : [IN] handle of storage
 * data : [OUT] buffer will be filled
 * offset : [IN] offset from head of storage
 * size : [IN] buffer size
 * read : [OUT] read size
 * RETURNS
 *  0 or error code
 * RETURN VALUES
 *  vm_storage_error_type
*****************************************************************************/
VMINT vm_storage_read(VMINT h, void * data, VMUINT offset, VMUINT size, VMUINT * read);

/*****************************************************************************
 * FUNCTION
 *  vm_storage_write
 * DESCRIPTION
 *  write data to storage
 * PARAMETERS
 *  h : [IN] handle of storage
 * data : [IN] buffer will be written to storage
 * offset : [IN] offset from head of storage
 * size : [IN] buffer size
 * written : [OUT] written size
 * RETURNS
 *  0 or error code
 * RETURN VALUES
 *  vm_storage_error_type
*****************************************************************************/
VMINT vm_storage_write(VMINT h, const void * data, VMUINT offset, VMUINT size, VMUINT * written);
/* DOM-NOT_FOR_SDK-END */

/* error code of storage */
typedef enum
{
    VM_SYS_FILE_ERR_DISK_FULL = -12, 
    VM_SYS_FILE_ERR_RES , /* resource is not enough */
    VM_SYS_FILE_ERR_PARAM, /* input param error */
    VM_SYS_FILE_ERR_FILE_CREATE, /* create failure */
    VM_SYS_FILE_ERR_FILE_OPEN, /* open failure */
    VM_SYS_FILE_ERR_FILE_DELETE,
    VM_SYS_FILE_ERR_FILE_SEEK, /* seek failure */
    VM_SYS_FILE_ERR_FILE_WRITE, /* wirte failure */
    VM_SYS_FILE_ERR_FILE_WRITE_PARTLY, 
    VM_SYS_FILE_ERR_FILE_READ, /* read failure */
    VM_SYS_FILE_ERR_AUTHORIZATION, /* no authorization */
    VM_SYS_FILE_ERR_NONE = 0 /* no error */
}vm_sys_file_error_type;


/*****************************************************************************
* FUNCTION
 *    vm_sys_file_open
 * DESCRIPTION
 *  open file in system drive disk
 * PARAMETERS
 *  mode : [IN] file open mode:
 *                MODE_READ: Read-Only
 *                MODE_WRITE : Read-Write
 *                MODE_CREATE_ALWAYS_WRITE : Read-Write mode, create if the file not exist.
 *  binary : [IN] TRUE means open with binary format, FALSE means open with ASCII format.
 * RETURNS
 *  non-negative file handle if successfully, and error code if failed to open. 
 *
*****************************************************************************/
VMFILE vm_sys_file_open(VMUINT mode, VMUINT binary);

/*****************************************************************************
* FUNCTION
 *    vm_sys_file_seek
 * DESCRIPTION
 *  move the sys file pointer to specified position. If exceed file size, this operation will return error.
 * PARAMETERS
 *  handle : [IN]  sys file handle to seek.
 *  offset : [IN]  bytes to move.
 *  base: [IN]  base position to move.
 *          BASE_BEGIN means from begin of file;
 *          BASE_CURR means from current position; 
 *          BASE_END means from end of file.
 * RETURNS
 *  0 means successfully, non-zero is error code.
 * 
*****************************************************************************/
VMINT vm_sys_file_seek(VMFILE handle, VMINT offset, VMINT base);


/*****************************************************************************
* FUNCTION
 *    vm_sys_file_read
 * DESCRIPTION
 *  read file from current pointer of sys file
 * PARAMETERS
 *  handle : [IN]  file handle to be read.
 *  data : [OUT] output data address
 *  length : [IN] bytes to be read
 *  nread : [IN] bytes read actually
 * RETURNS
 *  bytes of read data if > 0, 0 means error happened or reach end of file.
 *
*****************************************************************************/
VMINT vm_sys_file_read(VMFILE handle, void * data, VMUINT length, VMUINT *nread);

/*****************************************************************************
* FUNCTION
 *    vm_sys_file_write
 * DESCRIPTION
 *  write data to current pointer of the sys file
 * PARAMETERS
 *  handle : [IN]  file handle to write.
 *  data : [IN] the address of data to be written
 *  length : [IN] bytes to be written
 *  written : [IN] bytes written actually
 * RETURNS
 *  bytes of written data if > 0, 0 means error happened.
 *
*****************************************************************************/
VMINT vm_sys_file_write(VMFILE handle, void * data, VMUINT length, VMUINT * written);


/*****************************************************************************
* FUNCTION
 *    vm_sys_file_close
 * DESCRIPTION
 *  close sys file 
 * PARAMETERS
 *  handle : [IN]  sys file handle to be closed.
 *
*****************************************************************************/
void vm_sys_file_close(VMFILE h);

/*****************************************************************************
* FUNCTION
 *    vm_sys_file_delete
 * DESCRIPTION
 *  delete sys file.
 * RETURNS
 *  delete sys file successfully or failed
 * RETURN VALUES                                      
 *  0 : delete file successfully.
 *  non-zero : failed to delete sys file.
 * 
*****************************************************************************/
VMINT vm_sys_file_delete(void);

/*****************************************************************************
* FUNCTION
 *    vm_sys_file_get_space
 * DESCRIPTION
 *  get the current free size of sys file 
 * PARAMETERS
 * RETURNS
 *  rest space size. 
 *
*****************************************************************************/
VMINT vm_sys_file_get_space(void);


/*****************************************************************************
* FUNCTION
 *    vm_get_default_store_path_by_type
 * DESCRIPTION
 *  get default store path of  different types
 * PARAMETERS
 * RETURNS
 *  path string. 
 *
*****************************************************************************/

VMUWSTR vm_get_default_store_path_by_type(VMINT disk_letter, VM_STORE_PATH_TYPE type);


/*****************************************************************************
 * FUNCTION
 *  vm_startup_email
 * DESCRIPTION
 *  startup email
 * PARAMETERS
 *  to_addr : [IN] email address of receiver (UCS2)
 * RETURN VALUES
 *  0 : success
 *  non-zero : failure
 *  -2 : platform not support
 *  -3 : no email account
 *****************************************************************************/
VMINT vm_startup_email(const VMWSTR to_addr);

/* vm_fmgr_default_folder_enum */
typedef enum
{
    VM_FMGR_DEFAULT_FOLDER_EBOOKS, /* path of defualt ebooks */
    VM_FMGR_DEFAULT_FOLDER_IMAGES, /* path of defualt images */
    VM_FMGR_DEFAULT_FOLDER_AUDIO, /* path of defualt audio */
    VM_FMGR_DEFAULT_FOLDER_VIDEO, /* path of defualt video */
    VM_FMGR_DEFAULT_FOLDER_SWFLASH, /* path of defualt swflash */
    VM_FMGR_DEFAULT_FOLDER_LANGLN, /* path of defualt langln */
    VM_FMGR_DEFAULT_FOLDER_TEMP, /* path of defualt temp */
    VM_FMGR_DEFAULT_FOLDER_THEMES, /* path of defualt themes */
    VM_FMGR_DEFAULT_FOLDER_BARCODE, /* path of defualt barcode */
    VM_FMGR_DEFAULT_FOLDER_MMSBOX, /* path of defualt mmsbox */
    VM_FMGR_DEFAULT_FOLDER_ROOT,  /* path of defualt root */
    VM_FMGR_DEFAULT_FOLDER_TOTAL
}vm_fmgr_default_folder_enum;

/*****************************************************************************
 * FUNCTION
 *  vm_get_default_folder_path
 * DESCRIPTION
 *  get the default path of folder type
 * PARAMETERS
 *  mode : [IN] see vm_fmgr_default_folder_enum
 * RETURNS
 *  const VMWCHAR * (UCS2)
 * RETURN VALUES
 *  non-NULL : success
 *  NULL : failure
 *****************************************************************************/
const VMWCHAR * vm_get_default_folder_path(vm_fmgr_default_folder_enum type);


/* vm_file_copy Callback Return Value */
typedef enum
{
   /* <color red>if something wrong, will call once</color>
    * Fail to do the copy action. Total and Completed will be zero.
    */
    VM_FS_MOVE_PGS_FAIL = -1,

    /*
     * <color red>Always call once</color>
     * Prepare to do the copy action. Parameter checking and remove target will be done at this stage.
     * Total and Completed will be zero.
     */
    VM_FS_MOVE_PGS_PREPARE,

   /*
    * <color red>If pass parameter checking, always call once.</color>
    * Start to do the copy action. Total and Completed will be zero.
    */
    VM_FS_MOVE_PGS_START,

   /*
    * <color red>Not always call even if nothing wrong.</color>
    * If you move/copy a folder recursively, Total will be the number of files/folders to be moved/copied.
    * Completed will be the files/folders that had been copied.
    * If you just copy a file, Total will be the size of this file and Completed will be the bytes that had been copied.
    * <color red>Note</color> that if move/copy only one file, this callback will be triggered when interval is longer than 100ms around.
    */
    VM_FS_MOVE_PGS_ING,

   /*
    * <color redIf nothing fail, always call once</color>
    * Move/copy action is done. Total and Completed will be zero.
    */
    VM_FS_MOVE_PGS_DONE
} vm_fs_move_pgs_enum;


/*****************************************************************************
 * <GROUP  CallbackFunctions>
 * FUNCTION
 *  vm_file_copy_cb
 * DESCRIPTION
 *  Callback function type for file copy.
 * PARAMETERS
 *  act : [IN] see vm_fs_move_pgs_enum.
 *  total : [IN] the size of source file.
 *  completed : [IN] copied size.
 *  hdl : [IN] handle of file copy.
 * RETURNS
 *  VMINT
 *****************************************************************************/
typedef VMINT (*vm_file_copy_cb)(VMINT act, VMUINT32 total, VMUINT32 completed, VMINT hdl);

/*****************************************************************************
 * FUNCTION
 *  vm_file_copy
 * DESCRIPTION
 *  copy file
 * PARAMETERS
 *  dst : [IN] the file path of destination UCS2
 *  src : [IN] the file path of source UCS2
 *  cb : [IN] callback of file copy
 * RETURNS
 *  VMINT
 * RETURN VALUES
 *  successful if 0, else failure
 *  (-2): bad parameter.
 *  (-3): Either source full path or destination full path is wrong
 *  (-19): Cannot find source full path specified.
 *  (-36): destination full path exists.
 *  (-44): Cannot get memory to do the operation
 *  (-46): busy.
 *  (-47): This action has been aborted in the user's callback function.
 *****************************************************************************/
VMINT vm_file_copy(const VMWSTR dst, const VMWSTR src, vm_file_copy_cb cb);

/*****************************************************************************
 * FUNCTION
 *  vm_file_copy_abort
 * DESCRIPTION
 *  abort file copy
 * PARAMETERS
 *  hdl : [IN] handle of file copy
 * RETURNS
 *  VMINT
 * RETURN VALUES
 *  success if 0, else failure
 *****************************************************************************/
VMINT vm_file_copy_abort(VMINT hdl);


/* flag for async fs */
#define VM_FS_READ_WRITE           0x00000000L
#define VM_FS_READ_ONLY            0x00000100L
#define VM_FS_OPEN_SHARED          0x00000200L
#define VM_FS_OPEN_NO_DIR          0x00000400L
#define VM_FS_OPEN_DIR             0x00000800L
#define VM_FS_CREATE               0x00010000L
#define VM_FS_CREATE_ALWAYS        0x00020000L
#define VM_FS_COMMITTED            0x01000000L
#define VM_FS_CACHE_DATA           0x02000000L
#define VM_FS_LAZY_DATA            0x04000000L
#define VM_FS_NONBLOCK_MODE        0x10000000L
#define VM_FS_PROTECTION_MODE      0x20000000L
#define VM_FS_NOBUSY_CHECK_MODE    0x40000000L



typedef VMINT vm_fs_api_enum;
typedef VMINT vm_fs_job_state_enum;
typedef VMINT vm_fs_job_id;
typedef VMINT vm_module_type;
typedef VMINT VM_FS_HANDLE;
typedef VMINT (*vm_fs_async_callback)(vm_fs_job_id jid, VMINT64 * result, void *data);


typedef enum
{
    VM_FS_PRIORITY_DEFAULT         = 0,        // Default: This job will use lower priority to run. Suitable to non-critical jobs.
    VM_FS_PRIORITY_INHERITED,                  // Inherited: This job will inherites the priority of user. Suitable to critical jobs.
    VM_FS_PRIORITY_INVALID         = 0xFF
}vm_fs_prioity_enum;

typedef struct
{
    vm_fs_api_enum             api;        // The API enumeration of this job
    vm_fs_job_state_enum       reserved1;  // Reserved
    VMUINT8               reserved2;  // Reserved
    vm_fs_job_id               jid;         // Job ID. It also appears in the 1st parameter of callback function.
    vm_module_type             reserved3;  // Reserved
    VMINT64               result;     // Execution result of FS API. It also appears in the 2nd parameter of callback function.
    vm_fs_async_callback       callback;   // Callback function pointer
    void                    *param;     // Parameter of callback function. It is defined in by user whenever FS async I/F is used.
    void                    *reserved4;  // Reserved
}vm_fs_async_callback_data_struct;


typedef struct
{
    vm_fs_async_callback_data_struct head;
    VMINT   job_id;
    VMINT    aborted;
}vm_fs_job_abort_struct;

typedef struct
{
    vm_fs_async_callback_data_struct head;
    VMWCHAR *  filename;
    VMUINT  flag;
}vm_fs_job_open_struct;

typedef struct
{
    vm_fs_async_callback_data_struct head;
    VMINT   fs_hdl;
    void        * data;
    VMUINT  length;
    VMUINT  * read;
}vm_fs_job_read_struct;

typedef struct
{
    vm_fs_async_callback_data_struct head;
    VMINT   fs_hdl;
    void        * data;
    VMUINT  length;
    VMUINT  * written;
}vm_fs_job_write_struct;

typedef struct
{
    vm_fs_async_callback_data_struct head;
    const VMWCHAR * filename;
}vm_fs_job_delete_struct;

typedef struct
{
    vm_fs_async_callback_data_struct head;
    VMINT   fs_hdl;
    VMINT64   offset;
    VMINT   whence;
}vm_fs_job_seek_struct;


typedef struct
{
    vm_fs_prioity_enum         priority;   // priority configuration of this job
    vm_fs_async_callback       callback;   // callback function pointer
    void                    *param;     // parameter of callback function
}vm_fs_overlapped_struct;

/*****************************************************************************
 * FUNCTION
 *    fs_aysnc_open
 *
 * DESCRIPTION
 *    Open a file
 *
 * PARAMETERS
 *  filename         :[IN]  Must point to the name of the file to open/create.
 *                          File names are not case sensitive; they will be converted to
 *                          upper case when file system searches this file, and they should
 *                          be two-byte aligned and UCS2 encoded. The file name can have one
 *                          of the following formats:
 *  flag             :[IN]  Can be a combination of the following flags:
 *                          VM_FS_READ_WRITE       VM_FS_READ_ONLY        VM_FS_OPEN_SHARED      VM_FS_OPEN_NO_DIR
 *                          VM_FS_OPEN_DIR         VM_FS_CREATE           VM_FS_CREATE_ALWAYS    VM_FS_COMMITTED
 *                          VM_FS_CACHE_DATA       VM_FS_LAZY_DATA        VM_FS_ATTR_HIDDEN      VM_FS_ATTR_SYSTEM
 *                          VM_FS_ATTR_ARCHIVE     VM_FS_NONBLOCK_MODE    VM_FS_PROTECTION_MODE
 *  overlapped       :[IN]  Overlapped structure has 3 members,
 *                          1. callback :[IN]   (Optional) Call back function. This function will be executed just after response message is received by user.
 *                          2. param    :[IN]   (Optional) Parameters for call back function
 *                          3. priority :[IN]   (*Required) Priority of this job, it can be any one of following options,
 *                                                  1. VM_FS_PRIORITY_DEFAULT  : User has no priority concern for this job)
 *                                                  2. VM_FS_PRIORITY_INHERITED: FS task will be raised to a higher priorty to execute this job)
 * RETURNS
 *  Successful  : A positive integer. It is Job ID.
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_open(const VMWSTR file_name, VMINT flag, vm_fs_overlapped_struct *overlapped);

/*****************************************************************************
 * FUNCTION
 *    vm_fs_async_write
 *
 * DESCRIPTION
 *    Write data to a file
 *
 * PARAMETERS
 *  fs_hdl          :[IN]   file handle, get it from *result in VMINT (*vm_fs_async_callback)(vm_fs_job_id jid, VMINT64 * result, void *data);
 *  data            :[IN]   Specifies the address of the data to be written.
 *  length          :[IN]   Specifies the number of bytes to write.
 *  written         :[OUT]  Pointer to an unsigned integer to receive the number of
 *                          bytes actually been written. Usually, *Written will contain
 *                          Length after the call. However, in case of an error, the
 *                          returned value may be less. Written may be set to NULL if
 *                          this information is not required by an application.
 *  overlapped       :[IN]  Overlapped structure has 3 members,
 *                          1. callback :[IN]   (Optional) Call back function. This function will be executed just after response message is received by user.
 *                          2. param    :[IN]   (Optional) Parameters for call back function
 *                          3. priority :[IN]   (*Required) Priority of this job, it can be any one of following options,
 *                                                  1. VM_FS_PRIORITY_DEFAULT  : User has no priority concern for this job)
 *                                                  2. VM_FS_PRIORITY_INHERITED: FS task will be raised to a higher priorty to execute this job)
 * RETURNS
 *  Successful  : A positive integer. It is Job ID.
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_write(VM_FS_HANDLE fs_hdl, void *data, VMUINT length, VMUINT *written, vm_fs_overlapped_struct *overlapped);

/*****************************************************************************
 * FUNCTION
 *    vm_fs_async_write
 *
 * DESCRIPTION
 *    Read data to a file
 *
 * PARAMETERS
 *  fs_hdl          :[IN]   file handle, get it from *result in VMINT (*vm_fs_async_callback)(vm_fs_job_id jid, VMINT64 * result, void *data);
 *  data            :[IN]   Specifies the address of the data to be read.
 *  length          :[IN]   Specifies the number of bytes to write.
 *  read         :[OUT]  Pointer to an unsigned integer to receive the number of
 *                          bytes actually been read. Usually, *Written will contain
 *                          Length after the call. However, in case of an error, the
 *                          returned value may be less. Written may be set to NULL if
 *                          this information is not required by an application.
 *  overlapped       :[IN]  Overlapped structure has 3 members,
 *                          1. callback :[IN]   (Optional) Call back function. This function will be executed just after response message is received by user.
 *                          2. param    :[IN]   (Optional) Parameters for call back function
 *                          3. priority :[IN]   (*Required) Priority of this job, it can be any one of following options,
 *                                                  1. VM_FS_PRIORITY_DEFAULT  : User has no priority concern for this job)
 *                                                  2. VM_FS_PRIORITY_INHERITED: FS task will be raised to a higher priorty to execute this job)
 * RETURNS
 *  Successful  : A positive integer. It is Job ID.
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_read(VM_FS_HANDLE fs_hdl, void *data, VMUINT length, VMUINT *read, vm_fs_overlapped_struct *overlapped);

/*****************************************************************************
 * FUNCTION
 *    vm_fs_async_seek
 *
 * DESCRIPTION
 *    Seek to a specific position of a file
 *
 * PARAMETERS
 *  fs_hdl          :[IN]   file handle, get it from *result in VMINT (*vm_fs_async_callback)(vm_fs_job_id jid, VMINT64 * result, void *data);
 *  offset          :[IN]   Specifies the offset (bytes) of the file to be seeked.
 *  whence          :[IN]   Specifies the method (start address) of the seek.
 *  overlapped       :[IN]  Overlapped structure has 3 members,
 *                          1. callback :[IN]   (Optional) Call back function. This function will be executed just after response message is received by user.
 *                          2. param    :[IN]   (Optional) Parameters for call back function
 *                          3. priority :[IN]   (*Required) Priority of this job, it can be any one of following options,
 *                                                  1. VM_FS_PRIORITY_DEFAULT  : User has no priority concern for this job)
 *                                                  2. VM_FS_PRIORITY_INHERITED: FS task will be raised to a higher priorty to execute this job)
 * RETURNS
 *  Successful  : A positive integer. It is Job ID.
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_seek(VM_FS_HANDLE fs_hdl, VMINT64 * offset, VMINT whence, vm_fs_overlapped_struct *overlapped);


/*****************************************************************************
 * FUNCTION
 *    vm_fs_async_delete
 *
 * DESCRIPTION
 *    Delete a file
 *
 * PARAMETERS
 *  filename        :[IN]   References the open file to seek to.
 *  overlapped       :[IN]  Overlapped structure has 3 members,
 *                          1. callback :[IN]   (Optional) Call back function. This function will be executed just after response message is received by user.
 *                          2. param    :[IN]   (Optional) Parameters for call back function
 *                          3. priority :[IN]   (*Required) Priority of this job, it can be any one of following options,
 *                                                  1. VM_FS_PRIORITY_DEFAULT  : User has no priority concern for this job)
 *                                                  2. VM_FS_PRIORITY_INHERITED: FS task will be raised to a higher priorty to execute this job)
 * RETURNS
 *  Successful  : A positive integer. It is Job ID.
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_delete(const VMWSTR filename, vm_fs_overlapped_struct *overlapped);

/*****************************************************************************
 * FUNCTION
 *  vm_fs_async_abort
 *
 * DESCRIPTION
 *  This function provides the facility to abort a specific job by Job ID
 *
 * PARAMETERS
 *  jid      :[IN]   Job ID
 * 
 * RETURNS
 *  Successful  : A non-negative integer
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_abort(vm_fs_job_id jid);


/*****************************************************************************
 * FUNCTION
 *  vm_fs_async_commit
 *
 * PARAMETERS
 *  fs_hdl          :[IN]   file handle, get it from *result in VMINT (*vm_fs_async_callback)(vm_fs_job_id jid, VMINT64 * result, void *data);
 *
 * DESCRIPTION
 *  Immediately flushes all buffers associated with a file to disk.
 *
 * PARAMETERS
 *  jid      :[IN]   Job ID
 * 
 * RETURNS
 *  Successful  : A non-negative integer
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_commit(VM_FS_HANDLE fs_hdl);

/*****************************************************************************
 * FUNCTION
 *  vm_fs_async_close
 *
 * PARAMETERS
 *  fs_hdl          :[IN]   file handle, get it from *result in VMINT (*vm_fs_async_callback)(vm_fs_job_id jid, VMINT64 * result, void *data);
 *
 * DESCRIPTION
 *  Immediately flushes all buffers associated with a file to disk.
 *
 * RETURNS
 *  Successful  : A non-negative integer
 *  Failed      : A negative integer. -1 means no authorization.
 *****************************************************************************/
VMINT vm_fs_async_close(VM_FS_HANDLE fs_hdl);

VMINT vm_fs_async_get_working_buf_size(void);

/*****************************************************************************
 * FUNCTION
 *  vm_kbd_is_key_supported
 * DESCRIPTION
 *  query if specified key code is supported
 * PARAMETERS
 *  keycode    [IN]    key code
 * RETURNS
 *  non-zero  : supported.
 *  zero      : unsupported
 *****************************************************************************/
VMINT vm_kbd_is_key_supported(VMINT keycode);



typedef struct
{
    VMBYTE * dst;
    VMUINT dst_size;
    VMBYTE * src;
    VMUINT src_size;
}vm_zip_t;

VMINT vm_uncompress(const vm_zip_t * info, void * (*app_malloc)(VMUINT items, VMUINT size), void (*app_free)(void * address));


#ifdef __cplusplus
}
#endif

#endif /* VMIO_SDK_H_ */ 

