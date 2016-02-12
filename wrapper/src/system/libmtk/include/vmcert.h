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

#ifndef _VM_CERT_MANAGER_SDK_
#define	_VM_CERT_MANAGER_SDK_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

#define	RSA_LEN					64

#define	DIG_MD5_LEN				16
#define	DIG_SHA_LEN				20

#define	DIG_MAX_LEN				DIG_SHA_LEN
#define	DIG_MIN_LEN				DIG_MD5_LEN

#define		CERT_HEAD_LEN				6

#define		CERT_DIGEST_TYPE_MD5		1
#define		CERT_DIGEST_TYPE_SHA		2

#define		CERT_DIGEST_LEN				64

#define		ISD_APP_NUM					-1

#define		RESERVED_BYTES_NUM			8

/* tag define */
enum{
	VM_CE_INFO_END = 0,           /* 0x00, null */
	VM_CE_INFO_DEV,               /* 0x01, application developer name */
	VM_CE_INFO_APP_ID,            /* 0x02, application identification */
	VM_CE_INFO_CERT_ID,           /* 0x03, index of key id */
	VM_CE_INFO_NAME,              /* 0x04, application name */
	VM_CE_INFO_VER,               /* 0x05, application version */
	VM_CE_INFO_ISSUE,             /* 0x06, valid start time (no use) */
	VM_CE_INFO_EXPIRED,           /* 0x07, valid end time (no use) */
	VM_CE_INFO_PAY,               /* 0x08, billing-related setting (no use) */
	VM_CE_INFO_PAY_NODE,          /* 0x09, billing-related setting (no use) */
	VM_CE_INFO_PRICE,             /* 0x0a, billing-related setting (no use) */
	VM_CE_INFO_PAY_MODE,          /* 0x0b, billing-related setting (no use) */
	VM_CE_INFO_PAY_PARAM,         /* 0x0c, billing-related setting (no use) */
	VM_CE_INFO_APP_USE,           /* 0x0d, billing-related setting (no use) */
	VM_CE_INFO_PAY_CHANNEL,       /* 0x0e, billing-related setting (no use) */
	VM_CE_INFO_MEM_REQ,           /* 0x0f, memory size application required */
	VM_CE_INFO_RESOLUTION_REQ,    /* 0x10, resolution application support */
	VM_CE_INFO_PLAT_REQ,          /* 0x11, engine version (no use) */
	VM_CE_INFO_IMSI,              /* 0x12, check for individual application */
	VM_CE_INFO_PERMISSION,        /* 0x13, system permission list */
	VM_CE_INFO_TRIAL,             /* 0x14, (no use) */
	VM_CE_INFO_COMPILER,          /* 0x15, compiler type (no use) */
	VM_CE_INFO_INPUT_MODE,        /* 0x16, (no use) */
	VM_CE_INFO_DESC,              /* 0x17, application descriptionl */
	VM_CE_INFO_SUPPORT_BG_RUN,    /* 0x18, is support background run or not */
	VM_CE_INFO_NAME_LIST,         /* 0x19, application name multilanguage */
	VM_CE_INFO_DESC_LIST,         /* 0x1a, application description multilanguage */
	VM_CE_INFO_ZIMO_LIST,         /* 0x1b, application name zimo multilanguage */
	VM_CE_INFO_ROTATE,            /* 0x1c, is support rotate or not */
	VM_CE_INFO_SM,                /* 0x1d, sm type (no use) */
	VM_CE_INFO_SM_TYPE,           /* 0x1e, sm type: general(0), UI(1) (no use)  */
	VM_CE_INFO_SM_PRIVATE,        /* 0x1f, private sm */
	VM_CE_INFO_SM_CRYPTEXT,       /* 0x20, private key */
	VM_CE_INFO_FILE_TYPE,         /* 0x21, file type */
    VM_CE_INFO_RO_RW_ZIP,         /* 0x22, is zipped or not */
    VM_CE_INFO_CHARSET,           /* 0x23, is encoding using UCS2 */
    VM_CE_INFO_SUPPORT_VP,        /* 0x24, 0 means not support Venus componet, 1 means support Venus component, and will link venus lib in package*/
    VM_CE_INFO_SYS_FILE_SIZE,     /* 0x25, system file max size*/
    VM_CE_INFO_MULTI_NAME_LIST,   /* 0x26, app name multi language support*/
    VM_CE_INFO_URL,               /* 0x27, update server URL*/
    VM_CE_INFO_UPDATE_INFO,       /* 0x28, update information*/    
    VM_CE_INFO_NO_SCREEN,         /* 0x29, is use screen or not*/ 
    VM_CE_INFO_VPP_TYPE,          /* 0x2a, vpp type:1:widget,2:wallpaper,3:launcher,4:screen lock*/ 
    VM_CE_INFO_PUSH = 0x2c,		  /* 0x2c, app support PUSH nor not ,1 means support,0 means NOT support*/
    VM_CE_INFO_PUSH_APPID,		  /* 0x2d, app push id */
    VM_CE_INFO_PUSH_SENDERID,	  /* 0x2e, app push sender id normal is a e-mail address */
    VM_CE_INFO_RES_AB2,           /* 0x2f, app use AB2 formant image */
    VM_CE_INFO_BUILD_ID,          /* 0x30 */
    VM_CE_INFO_ADV_ICON,          /* 0x31,  app use advanced ICON, support PNG and any size */
    VM_CE_INFO_AUTO_START,        /* 0x32,   app auto start when power on*/
    VM_CE_INFO_IDLE_SHORTCUT,     /* 0x33,  app set idle shortcut when install*/
    VM_CE_INFO_CLOCK_APP,     /* 0x34,  1 means app is clock app,0 means not*/
    VM_CE_INFO_AUTH,     /* 0x35,  app defined authorization info*/
    VM_CE_INFO_PADDING, /*0x36,app icon padding for 4bytes align*/
	VM_CE_INFO_TOTAL
};


/* DOM-NOT_FOR_SDK-BEGIN */
#define		VM_CE_INFO_LIST_START		VM_CE_INFO_NAME_LIST
#define		VM_CE_INFO_LIST_END			VM_CE_INFO_ZIMO_LIST

/* define the Cert envelop head */
typedef struct _MRECertHead
{
	VMINT		digestype;   /* digest type  MD5 or SHA1 */
	VMUCHAR		signature[RSA_LEN];  /* signature */
	VMINT		offset;  /* offset of signature */
	VMUCHAR		reserve[RESERVED_BYTES_NUM];  /* reserve */
} MRECertHead;

/* Extend Cert envelop head */
typedef struct _MRECertHead_Ex
{
	VMINT		digestype; /* digest type MD5 or SHA1 */
	VMUCHAR		signature[RSA_LEN * 2];  /* signature */
	VMINT		offset; /* offset of signature */
	VMUCHAR		reserve[RESERVED_BYTES_NUM]; /* reserve */
} MRECertHead_Ex;

/* Cert structure */
typedef struct _MRECert
{
	VMUCHAR* digest;   /* digest data */
	VMINT    diglen;  /* digest lenth */
	VMINT    digesttype;  /* digest type  */
} MRECert;
/* DOM-NOT_FOR_SDK-END */

/* Auth type */
enum
{
	VERIFY_SIG = 1, /* only signature */
	VERIFY_FULL /* full Auth */
};

/*****************************************************************************
 * FUNCTION
 *  vm_ce_auth_app_ex
 * DESCRIPTION
 * verify the file, to check if it is legal
 * PARAMETERS 
 *    filename : [IN]    full path to check
 *    cache_buf : [IN]  buffer for engine used
 *    cache_len :  [IN] size of buffer
 *    mode :     [IN]   VERIFY_SIG(signature, resolution), VERIFY_FULL(include memory)
 * RETURNS
 *  if succeed, return >=0, otherwise failure.
 * EXAMPLE
 * <code>
 *  VMUCHAR* ce_digest_buffer = NULL;
 *  VMINT ce_digest_buffer_len = (10 * 1024);
 *
 *  VMINT	 rescode = -1;
 *
 *  if ((ce_digest_buffer = vm_malloc(ce_digest_buffer_len)) == NULL)
 *		 return ;
 *
 *  rescode = vm_ce_auth_app_ex( vxp_filename, ce_digest_buffer, ce_digest_buffer_len, VERIFY_SIG);
 *	 
 *  vm_free( ce_digest_buffer );
 *	 
 *  return rescode;
 * </code>
 *****************************************************************************/
extern VMINT vm_ce_auth_app_ex( VMWSTR filename, VMUCHAR * cache_buf, VMINT cache_len, VMINT mode );

#ifdef __cplusplus
}
#endif

#endif /* _VM_CERT_MANAGER_SDK_ */
