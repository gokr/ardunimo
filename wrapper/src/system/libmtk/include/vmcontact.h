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

#ifndef VMPHONEBOOK_SDK_H_
#define VMPHONEBOOK_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* The maximum length of searching pattern string */
#define VM_PHB_MAX_SEARCH_LENGTH 60

/* Returned basic error codes */
typedef enum
{
    VM_PHB_REQ_NOT_READY = -2,  /* Phonebook is not ready  */
    VM_PHB_REQ_ERROR,           /* Operation unsuccessful */
    VM_PHB_REQ_NO_ERROR         /* Operation successful */
} vm_phb_req_error_enum;

/* Error codes */
typedef enum
{
    VM_PHB_NAME_MODIFIED = 1,       /* Name has been truncated due to length exceed SIM MAX name length. */
    VM_PHB_NO_ERROR = 0,            /* Operation successful */
    VM_PHB_ERROR = -1,              /* General failure */
    VM_PHB_NOT_READY = -2,          /* Phonebook is not ready */
    VM_PHB_NUM_NOT_READY = -3,      /* Search operation is not ready */
    VM_PHB_NOT_SUPPORT = -4,        /* Phonebook not supported  */
    VM_PHB_NOT_FOUND = -5,          /* No contact found */
    VM_PHB_DATAMGR_BUSY = -6,       /* Phonebook is busy */
    VM_PHB_STORAGE_FULL = -7,       /*  Storage is full */
    VM_PHB_NO_SIM_CARD = -8,        /* No SIM card */
    VM_PHB_ADN_FORBID = -9,         /* Failed to visit phonebook in SIM card */
    VM_PHB_OUT_OF_INDEX = -10,      /* Invalid index */
    VM_PHB_NUMBER_TOO_LONG = -11,   /* Invalid number */
    VM_PHB_BIRTHDAY_ERROR = -12     /* Invalid birthday format */
} vm_phb_error_enum;

/* Storage location of phonebook */
typedef enum
{
    VM_PHB_STORAGE_LOC_SIM  = 1,    /* SIM card 1 */ 
    VM_PHB_STORAGE_LOC_PHONE,   /* Phone */
    VM_PHB_STORAGE_LOC_SIM2,    /* SIM card 2 */
    VM_PHB_STORAGE_LOC_SIM3,	/* SIM card 3 */ 
    VM_PHB_STORAGE_LOC_SIM4,	/* SIM card 4 */ 
    VM_PHB_STORAGE_LOC_BOTH     /* Both SIM card and Phone */
} vm_phb_storage_loc_enum;

/* Search type */
typedef enum
{
    VM_PHB_SEARCH_TYPE_NAME,    /* Name */
    VM_PHB_SEARCH_TYPE_NUM      /* Number */
} vm_phb_search_type_enum;

/* Phonebook contact position struct */
typedef struct
{
    VMUSHORT index;                     /* Index: 1 - MAX index. It will not change the position of other contact when deleting a contact. */
    vm_phb_storage_loc_enum storage;    /* Storage location of phonebook */
} vm_phb_contact_pos_struct;

#define VM_MAX_PHB_NAME_LENGTH   30 /* Max length of name */
#define VM_MAX_PHB_NUMBER_LENGTH   40   /* Max length of number */
#define VM_MAX_PHB_EMAIL_LENGTH   60    /* Max length of email */
#define VM_MAX_PHB_COMPANY_LENGTH   20  /* Max length of company */
#define VM_MAX_PHB_TITLE_LENGTH  20 /* Max length of title */
#define VM_MAX_PHB_URL_LENGTH 128   /* Max length of url */
#define VM_MAX_PHB_ADDRESS_LENGTH   25  /* Max length of address */
#define VM_MAX_PHB_NOTE_LENGTH   30 /* Max length of note */
#define VM_MAX_PHB_GROUP_NAME_LENGTH 20 /* Max length of group name */

 /* Phonebook contact info struct, all the string are encoded by UCS2. */
typedef struct
{
    vm_phb_contact_pos_struct pos;                          /* Contact position */
    VMUWCHAR name[VM_MAX_PHB_NAME_LENGTH + 1];              /* Contact name field (UCS2) */
    VMUWCHAR number[VM_MAX_PHB_NUMBER_LENGTH + 1 + 1];      /* Contact mobile number field (UCS2) */
    VMUWCHAR home_number[VM_MAX_PHB_NUMBER_LENGTH + 1 + 1]; /* Contact home number field (UCS2) */
    VMUWCHAR office_number[VM_MAX_PHB_NUMBER_LENGTH + 1 + 1];   /* Contact office number field (UCS2) */
    VMUWCHAR fax_number[VM_MAX_PHB_NUMBER_LENGTH + 1 + 1];  /* Contact fax number field (UCS2) */
    VMUWCHAR email_address[VM_MAX_PHB_EMAIL_LENGTH + 1];    /* Contact email field (UCS2) */
    VMUWCHAR email_address2[VM_MAX_PHB_EMAIL_LENGTH + 1];   /* Contact email2 field (UCS2) */
    VMUWCHAR company_name[VM_MAX_PHB_COMPANY_LENGTH + 1];   /* Contact company name field (UCS2) */
    VMUCHAR birth_day;                                      /* Contact birthday-day field */
    VMUCHAR birth_mon;                                      /* Contact birthday-month field */
    VMUINT16 birth_year;                                    /* contact birthday-year field */
    VMUWCHAR title[VM_MAX_PHB_TITLE_LENGTH + 1];            /* Contact title field (UCS2) */
    VMUWCHAR url[VM_MAX_PHB_URL_LENGTH + 1];                /* Contact url field (UCS2) */
    VMUWCHAR adr_pobox[VM_MAX_PHB_ADDRESS_LENGTH + 1];      /* Contact address-pobox field (UCS2) */
    VMUWCHAR adr_extension[VM_MAX_PHB_ADDRESS_LENGTH + 1];  /* Contact address-extention field (UCS2) */
    VMUWCHAR adr_street[VM_MAX_PHB_ADDRESS_LENGTH + 1];     /* Contact address-street field (UCS2) */
    VMUWCHAR adr_city[VM_MAX_PHB_ADDRESS_LENGTH + 1];       /* Contact address-city field (UCS2) */
    VMUWCHAR adr_state[VM_MAX_PHB_ADDRESS_LENGTH + 1];      /* Contact address-state field (UCS2) */
    VMUWCHAR adr_postal_code[VM_MAX_PHB_ADDRESS_LENGTH + 1];    /* Contact address-postal code field (UCS2) */
    VMUWCHAR adr_country[VM_MAX_PHB_ADDRESS_LENGTH + 1];    /* Contact address-country field (UCS2) */
    VMUWCHAR note[VM_MAX_PHB_NOTE_LENGTH + 1];              /* Contact note field (UCS2) */
    VMUINT group_mask;                                      /* Contact group field(bitmask), a contact can have multiple group id. (group_mask = 1<< group_id1 + 1<< group_id2 + ... . If group_mask=1, then group_id=0;  if group_mask=3, then group_id=0 group_id=1) */
} vm_phb_contact_struct;

/* Phonebook group struct */
typedef struct
{
    VMUINT group_id; /* Group id */
    VMWCHAR group_name[VM_MAX_PHB_GROUP_NAME_LENGTH + 1]; /* Group name */
} vm_phb_group_struct;

/*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  vm_phb_callback_type
 * DESCRIPTION
 *  Callback function type for phonebook operation.
 * PARAMETERS
 *  result : [IN] Operation result, refer to vm_phb_error_enum.
 *  contact_ptr : [IN] Pointer to contact info, as a part of request data when sending request.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_phb_callback_type) (VMINT result, vm_phb_contact_struct *contact_ptr);

/* Phonebook contact add request info struct */
typedef struct
{
    vm_phb_storage_loc_enum storage;    /* Storage location of phonebook */
    vm_phb_contact_struct *contact_ptr; /* Phonebook contact info */
} vm_phb_add_req_struct;

/* Phonebook contact delete request info struct */
typedef struct
{
    vm_phb_contact_pos_struct pos;  /* Contact position */
} vm_phb_delete_req_struct;

/* Phonebook contact update request info struct */
typedef struct
{
    vm_phb_contact_pos_struct pos;      /* Contact position */
    vm_phb_contact_struct *contact_ptr; /* Phonebook contact info */
} vm_phb_update_req_struct;

/* Contact get request info struct */
typedef struct
{
    vm_phb_contact_pos_struct pos;      /* Contact position */
    vm_phb_contact_struct *contact_ptr; /* Phonebook contact info */
} vm_phb_get_req_struct;

/* Search contact request info struct */
typedef struct
{
    VMWCHAR pattern_ucs2[VM_PHB_MAX_SEARCH_LENGTH]; /* Search pattern(UCS2) */
    vm_phb_search_type_enum search_type;            /* Search type */
    vm_phb_contact_struct *contact_ptr;             /* Pointer to contact info, this pointer will be returned by callback function */
} vm_phb_search_req_struct;

 /* Search contact list request info struct */
typedef struct
{
    VMWCHAR pattern_ucs2[VM_PHB_MAX_SEARCH_LENGTH]; /* Search pattern(UCS2) */
    vm_phb_search_type_enum search_type;            /* Search type */
} vm_phb_search_list_req_struct;

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_add_contact
 * DESCRIPTION
 *  Add a phonebook contact.  If you want to add multiple contacts, 
 *  the next contact must be added after the callback function returns.
 * PARAMETERS
 *  req_info : [IN] Contact's info. If added successfully, the content and location info can be obtained by the callback function. 
 *  cb : [IN] Callback function.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_add_contact(vm_phb_add_req_struct *req_info, vm_phb_callback_type cb);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_delete_contact
 * DESCRIPTION
 *  Delete a phonebook contact. If you want to delete multiple contacts, 
 *  the next contact must be deleted after the callback function returns.
 * PARAMETERS
 *  req_info : [IN] Delete contact request info.
 *  cb : [IN] Callback function.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_delete_contact(vm_phb_delete_req_struct *req_info, vm_phb_callback_type cb);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_update_contact
 * DESCRIPTION
 *  Edit a phonebook contact. If you want to edit multiple contacts, 
 *  the next contact must be edited after the callback function returns.
 * PARAMETERS
 *  req_info : [IN] Contact's info.
 *  cb : [IN] Callback function.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_update_contact(vm_phb_update_req_struct *req_info, vm_phb_callback_type cb);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_search_contact
 * DESCRIPTION
 *  Search a contact by name or number. The matching contact of every searching is returned by callback function.
 * PARAMETERS
 *  req_info : [IN] Search request info.
 *  cb : [IN] Callback function.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_search_contact(vm_phb_search_req_struct *req_info, vm_phb_callback_type cb);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_search_contact_list
 * DESCRIPTION
 *  Search contact list by name or number. The matching contact list will be filled to pos_array.
 * PARAMETERS
 *  req_info : [IN] Search request info.
 *  pos_array : [OUT] Buffer to all the matching contacts.
 *  post_array_len : [IN] Buffer size.
 * RETURNS
 *  The number of matching contacts.
 *****************************************************************************/
VMINT vm_phb_search_contact_list(
        vm_phb_search_list_req_struct *req_info,
        vm_phb_contact_pos_struct *pos_array,
        VMINT post_array_len);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_get_contact
 * DESCRIPTION
 *  Get contact's info by position, and the info will be returned by callback function.
 * PARAMETERS
 *  req_info : [IN] Pointer to request info.
 *  cb : [IN] Callback function.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_get_contact(vm_phb_get_req_struct *req_info, vm_phb_callback_type cb);

/*****************************************************************************
 * FUNCTION
 *  vm_phb_search_contact_syn
 * DESCRIPTION
 *  Search a contact by name or number synchronously.
 * PARAMETERS
 *  req_info : [IN] Pointer to request info.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_search_contact_syn(vm_phb_search_req_struct *req_info);

/*****************************************************************************
 * FUNCTION
 *  vm_phb_get_contact_syn
 * DESCRIPTION
 *  Get contact's info by position synchronously.
 * PARAMETERS
 *  req_info : [IN] Pointer to request info.
 * RETURNS
 *  The error code of the operation. Refer to vm_phb_req_error_enum.
 *****************************************************************************/
vm_phb_req_error_enum vm_phb_get_contact_syn(vm_phb_get_req_struct *req_info);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_get_total_contacts
 * DESCRIPTION
 *  Get total number of contacts of phonebook.
 * PARAMETERS
 *  storage : [IN] Storage location.
 * RETURNS
 *  The total number of contacts.
 * RETURN VALUES
 *  <0 : Get failed.
 *  >0 : The total number of contacts.
 *****************************************************************************/
VMINT vm_phb_get_total_contacts(vm_phb_storage_loc_enum storage);

 /*****************************************************************************
 * FUNCTION
 *  vm_phb_get_used_contacts
 * DESCRIPTION
 *  Get the stored contact list by location.
 * PARAMETERS
 *  pos_array : [OUT] Buffer stores contact list.
 *  storage : [IN] Storage location.
 * RETURNS
 *  The number of stored contacts.
 * RETURN VALUES
 *  <0 : Operation failed.
 *  >0 : The number of stored contacts.
 *****************************************************************************/
VMINT vm_phb_get_used_contacts(vm_phb_contact_pos_struct *pos_array, vm_phb_storage_loc_enum storage);

/*****************************************************************************
 * FUNCTION
 *  vm_phb_get_used_contacts_count
 * DESCRIPTION
 *  Get the number of stored contacts in phonebook storage.
 * PARAMETERS
 *  storage : [IN] Storage location.
 * RETURNS
 *  The number of stored contacts.
 * RETURN VALUES
 *  <0 : Operation failed.
 *  >0 : The number of stored contacts.
 *****************************************************************************/
VMINT vm_phb_get_used_contacts_count(vm_phb_storage_loc_enum storage);

/*****************************************************************************
 * FUNCTION
 *  vm_phb_get_group_list_count
 * DESCRIPTION
 *  Get the number of group in phonebook.
 * PARAMETERS
 *  void
 * RETURNS
 *  The number of group.
 *****************************************************************************/
VMINT vm_phb_get_group_list_count(void);

/*****************************************************************************
 * FUNCTION
 *  vm_phb_get_group_list
 * DESCRIPTION
 *  Get group id list ordered by group name.
 * PARAMETERS
 *  group_array : [OUT] Buffer stores group id list.
 *  group_array_len : [IN] Size of the buffer.
 * RETURNS
 *  The number of group id.
 *****************************************************************************/
VMINT vm_phb_get_group_list(vm_phb_group_struct *group_array, VMINT group_array_len);

/*****************************************************************************
 * FUNCTION
 *  vm_phb_get_group_name_by_id
 * DESCRIPTION
 *  Get group name by group id.
 * PARAMETERS
 *  group_id : [IN] Group id.
 *  group_name : [OUT] Buffer stores group name.
 *  len : [IN] Size of the buffer.
 * RETURN VALUES
 *  TRUE : If successful.
 *  FALSE : If unsuccessful.
 *****************************************************************************/
VMINT vm_phb_get_group_name_by_id(VMUINT group_id, VMWCHAR *group_name, VMINT len);

#ifdef __cplusplus
}
#endif

#endif /* VMPHONEBOOK_SDK_H_ */ 

