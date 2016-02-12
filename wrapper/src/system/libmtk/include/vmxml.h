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

#ifndef VMXML_SDK_H
#define VMXML_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  XML_start_doctype_hdlr
 * DESCRIPTION
 *  This function is document type start handler.
 * PARAMETERS
 *  data : [IN] Reserved.
 *  doctypeName : [IN] Document type name.
 *  sysid : [IN] System id.
 *  pubid : [IN] Public id.
 *  internal_subset : [IN] Internal subset.
 *  error : [IN] Error code.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*XML_start_doctype_hdlr) (void *data,
                                        const VMCHAR *doctypeName,
                                        const VMCHAR **sysid,
                                        const VMCHAR **pubid, VMINT internal_subset, VMINT error);

 /*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  XML_end_doctype_hdlr
 * DESCRIPTION
 *  This function is document type end handler.
 * PARAMETERS
 *  data : [IN] Reserved.
 *  error : [IN] Error code, refer to VM_XML_ERROR_ENUM.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*XML_end_doctype_hdlr) (void *data, VMINT error);

 /*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  XML_start_elem_hdlr
 * DESCRIPTION
 *  This function is element start handler.
 * PARAMETERS
 *  data : [IN] Reserved.
 *  el : [IN] Element name.
 *  attr : [IN] Attribution list.
 *  error : [IN] Error code, refer to VM_XML_ERROR_ENUM.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*XML_start_elem_hdlr) (void *data, const VMCHAR *el, const VMCHAR **attr, VMINT error);

 /*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  XML_end_elem_hdlr
 * DESCRIPTION
 *  This function is element end handler.
 * PARAMETERS
 *  data : [IN] Reserved.
 *  el : [IN] Element name.
 *  error : [IN] Error code, refer to VM_XML_ERROR_ENUM.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*XML_end_elem_hdlr) (void *data, const VMCHAR *el, VMINT error);

 /*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  XML_data_hdlr
 * DESCRIPTION
 *  This function is used to handle data.
 * PARAMETERS
 *  resv : [IN] Reserved.
 *  el : [IN] Element name.
 *  data : [IN] Data.
 *  len : [IN] Length.
 *  error : [IN] Error code.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*XML_data_hdlr) (void *resv, const VMCHAR *el, const VMCHAR *data, VMINT len, VMINT error);

 /* Define the error code */
typedef enum
{
    VM_XML_RESULT_FILE_NOT_FOUND = -4,  /* The file isn't found */
    VM_XML_RESULT_OUT_OF_MEMORY = -3,   /* The memory isn't enough */
    VM_XML_RESULT_ENCODING_ERROR = -2,  /* The char encoding error */
    VM_XML_RESULT_FAIL = -1,            /* Failed to parse xml */
    VM_XML_RESULT_OK = 0                /* Parsing xml successfully */
} VM_XML_RESULT_ENUM;

/* Define the error code */
typedef enum
{
    VM_XML_NO_ERROR,                            /* No error */
    VM_XML_ERROR_MISMATCH_TAG,                  /* Error string: end tag name */
    VM_XML_ERROR_MISMATCH_DOCTYPENAME_ROOTNAME, /* Error string: root element name */
    VM_XML_ERROR_INVALID_ATTRIBUTE,             /* Error string: attribute name */
    VM_XML_ERROR_DUPLICATE_ATTRIBUTE,           /* Error string: attribute name */
    VM_XML_ERROR_ENTITY_DEFINITION,             /* Error string: entity name */
    VM_XML_ERROR_UNDEFINED_ENTITY               /* Error string: entity name */
} VM_XML_ERROR_ENUM;

 /* XML parser struct with all the tag handler */
typedef struct _VM_XML_PARSER_STRUCT
{
    XML_start_doctype_hdlr start_doctype_hdlr;  /* Function pointer provided by app */
    XML_end_doctype_hdlr end_doctype_hdlr;      /* Function pointer provided by app */
    XML_start_elem_hdlr start_elem_hdlr;        /* Function pointer provided by app */
    XML_end_elem_hdlr end_elem_hdlr;            /* Function pointer provided by app */
    XML_data_hdlr data_hdlr;                    /* Function pointer provided by app */
} VM_XML_PARSER_STRUCT;

/*****************************************************************************
 * FUNCTION
 *  vm_xml_new_parser
 * DESCRIPTION
 *  Initialize a new XML parser. The default handlers will be assigned.
 * PARAMETERS
 *  parser : [IN] Pointer to a parser struct.
 * RETURN VALUES
 *  VM_XML_RESULT_OK : If successful.
 *  VM_XML_RESULT_FAIL : If unsuccessful.
 * EXAMPLE
 * <code>
 *
 * #define VMXML_TEST_FILE_RES "<html><body> <h1>Q's working space</h1> <a href=\"www.mediatek.com\">Mediatek</a> </body></html>"
 *
 * static void vmxml_doctype_start(void *data, const VMCHAR *doctypeName, const VMCHAR **sysid, 
 *							   const VMCHAR **pubid, VMINT internal_subset, VMINT error)
 * {
 *	 vm_log_info("doctype_start: doctypeName: %s, %d", doctypeName, error);
 * }
 *
 * static void vmxml_doctype_end(void *data, VMINT error)
 * {
 *	 vm_log_info("doctype_end: %d", error);
 * }
 *
 * static void vmxml_elem_start(void *data, const VMCHAR *el, const VMCHAR **attr, VMINT error)
 * {
 *	 vm_log_info("elem_start: [%s] [res = %d]", el, error);
 * }
 *
 * static void vmxml_elem_end(void *data, const VMCHAR *el, VMINT error)
 * {
 *	 if (VM_XML_NO_ERROR != error) 
 *	 {
 *         VMSTR err_str = vm_xml_get_error();
 *           if (err_str != NULL) 
 *           {
 *           	   vm_log_info("parse normally, error string %s", err_str);
 *           }
 *	 }
 *	 else 
 *	 {
 *		 if (0 == strcmp(el, "html")) 
 *		 {
 *		   vm_log_info("parse normally.");
 *            }
 *	 }
 * }
 *
 * static void vmxml_data(void *resv, const VMCHAR *el, const VMCHAR *data, VMINT len, VMINT error)
 * {
 *	 vm_log_info("Data: [%s][len = %d][res = %d]", el, len, error);
 *
 *	 if (0 == strcmp(el, "h1")) 
 *	 {
 *		 if (0 == strcmp(data, "Q's working space")) 
 *		 {
 *			 vm_log_info("get title text is correct");
 *		 }
 *		 else 
 *		 {
 *			 vm_log_info("get incorrect title");
 *		 }
 *	 }
 * }
 *
 *  void xml_test(void) 
 *  {
 *	  VM_XML_RESULT_ENUM ret = VM_XML_RESULT_FAIL;
 * 	  VM_XML_PARSER_STRUCT parser;
 *
 *	  memset(&parser, 0, sizeof(VM_XML_PARSER_STRUCT));
 *       ret = vm_xml_new_parser(&parser);
 *
 *	  if (ret == VM_XML_RESULT_OK) 
 *	  {
 *          vm_xml_set_data_handler(&parser, vmxml_data);
 *          vm_xml_set_doctype_handlers(&parser, vmxml_doctype_start, vmxml_doctype_end);
 *          vm_xml_set_element_handlers(&parser, vmxml_elem_start, vmxml_elem_end);
 *	      ret = vm_xml_parse(&parser, VMXML_TEST_FILE_RES, strlen(VMXML_TEST_FILE_RES));
 *	      if (ret != VM_XML_RESULT_OK) 
 *		{
 *			vm_log_info("vm_xml_parse() failed. error = %d", ret);
 *		}
 *	  }
 *  }
 * </code>
 *****************************************************************************/
VMINT vm_xml_new_parser(VM_XML_PARSER_STRUCT *parser);

/*****************************************************************************
 * FUNCTION
 *  vm_xml_set_doctype_handlers
 * DESCRIPTION
 *  Set document handlers.
 * PARAMETERS
 *  parser : [IN] Pointer to a parser struct.
 *  start_hdlr : [IN] Function handler to handle start doc data.
 *  end_hdlr : [IN] Function handler to handle end doc data.
 * SEE ALSO
 *  vm_xml_new_parser
 *****************************************************************************/
void vm_xml_set_doctype_handlers(
        VM_XML_PARSER_STRUCT *parser,
        XML_start_doctype_hdlr start_hdlr,
        XML_end_doctype_hdlr end_hdlr);

/*****************************************************************************
 * FUNCTION
 *  vm_xml_set_element_handlers
 * DESCRIPTION
 *  Set element handlers.
 * PARAMETERS
 *  parser : [IN] Pointer to a parser struct.
 *  start_hdlr : [IN] Function handler to handle start element data.
 *  end_hdlr : [IN] Function handler to handle end element data.
 * SEE ALSO
 *  vm_xml_new_parser
 *****************************************************************************/
void vm_xml_set_element_handlers(
        VM_XML_PARSER_STRUCT *parser,
        XML_start_elem_hdlr start_hdlr,
        XML_end_elem_hdlr end_hdlr);

/*****************************************************************************
 * FUNCTION
 *  vm_xml_set_data_handler
 * DESCRIPTION
 *  Set data handlers.
 * PARAMETERS
 *  parser : [IN] Pointer to a parser struct.
 *  start_hdlr : [IN] Function handler to handle data.
 * SEE ALSO
 *  vm_xml_new_parser
 *****************************************************************************/
void vm_xml_set_data_handler(VM_XML_PARSER_STRUCT *parser, XML_data_hdlr data_hdlr);

/*****************************************************************************
 * FUNCTION
 *  vm_xml_parse
 * DESCRIPTION
 *  This function is called by application to start parsing if application pass.
 * PARAMETERS
 *  parser : [IN] Pointer to a parser struct.
 *  xmlsource : [IN] Xml file name or XML string buffer.
 *  length : [IN] 0-from file; >0-from memory.
 * RETURN VALUES
 *  VM_XML_RESULT_OK : If successful.
 *  VM_XML_RESULT_FAIL : If unsuccessful.
 * SEE ALSO
 *  vm_xml_new_parser
 *****************************************************************************/
VMINT vm_xml_parse(VM_XML_PARSER_STRUCT *parser, const VMCHAR *xmlsource, VMINT length);

/*****************************************************************************
 * FUNCTION
 *  vm_xml_get_error
 * DESCRIPTION
 *  Get the error string.
 * RETURN
 *  Error string.
 * SEE ALSO
 *  vm_xml_new_parser
 *****************************************************************************/
VMCHAR *vm_xml_get_error(void);

#ifdef __cplusplus
}
#endif

#endif /* VMXML_SDK_H */ 

