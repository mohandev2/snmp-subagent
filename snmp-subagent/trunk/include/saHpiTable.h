/*
 * (C) Copyright IBM Corp. 2003
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *   Konrad Rzeszutek <konradr@us.ibm.com>
 *
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.15.2.1 2003/02/27 05:59:41 rstory Exp $
 *
 * $Id$
 *
 */
#ifndef SAHPITABLE_H
#define SAHPITABLE_H

#ifdef __cplusplus
extern          "C" {
#endif

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>
#include <SaHpi.h>
#include <hpiSubagent.h>

   /*
   * Number of index values in this table.
   * Consult the HPI-MIB
   *
   * If this number changes, look in the src code for this 
   * define, and make sure to add/remove the new index value(s).
   */
#define RPT_INDEX_NR 3
  /*
   * Different options for saving/restoring 
   * Consult the MIB
   */
#define PARAM_UNDEFINED 0
#define PARAM_RESTORE_DEFAULT_PARM 1
#define PARAM_SAVE_PARM 2
#define PARAM_RESTORE_PARM 3

  /*
   * Max size of OCTET STRING. Consult HPI-MIB
   */
#define SAHPI_RESOURCE_TAG_MAX 255

    typedef struct saHpiTable_context_s {
        netsnmp_index   index;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiDomainID;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiEntryID;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceID;

        /** OCTETSTR = ASN_OCTET_STR */
        unsigned char   saHpiResourceEntityPath[SNMP_MAX_MSG_SIZE];
        long            saHpiResourceEntityPath_len;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceCapabilities;

        /** INTEGER = ASN_INTEGER */
        long            saHpiResourceSeverity;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoResourceRev;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoSpecificVer;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoDeviceSupport;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoManufacturerId;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoProductId;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoFirmwareMajorRev;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoFirmwareMinorRev;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiResourceInfoAuxFirmwareRev;

        /** INTEGER = ASN_INTEGER */
        long            saHpiResourceTagTextType;

        /** INTEGER = ASN_INTEGER */
        long            saHpiResourceTagTextLanguage;

        /** OCTETSTR = ASN_OCTET_STR */
        unsigned char   saHpiResourceTag[SAHPI_RESOURCE_TAG_MAX];
        long            saHpiResourceTag_len;

         /** INTEGER = ASN_INTEGER */
        long            saHpiParamControl;

        /** RowStatus = ASN_INTEGER */
      long            saHpiClearEvents;

         /** HpiTimeStamp = ASN_COUNTER64 */
        integer64        saHpiEventLogTime;

      /** INTEGER = ASN_INTEGER */
        long            saHpiEventLogState;
        long  hash;

      /*
       * Dirty bit. When set to 0, means this context is not
       * used anywhere
       */
      unsigned int dirty_bit;
      
    } saHpiTable_context;

/*************************************************************
 * function declarations
 */

    void            initialize_table_saHpiTable(void);
 
    int             saHpiTable_get_value(netsnmp_request_info *,
                                         netsnmp_index *,
                                         netsnmp_table_request_info *);

  int populate_rpt( void );

  unsigned long purge_rpt( void );
  /* 
   * The various SET operations. 
   */
  int
  set_table_severity(saHpiTable_context *ctx);
  int
  set_table_tag(saHpiTable_context *ctx);

  int
  set_table_param_control(saHpiTable_context *ctx);

  int
  set_clear_events(saHpiTable_context *ctx);
  
  int 
  set_event_log_time(saHpiTable_context *ctx);

  int
  set_logstate(saHpiTable_context *ctx);
  /*
   * Remvoe the RTP row (from SNMP memory, not SaHPI).
   */


int 
delete_rpt_row(SaHpiDomainIdT domain_id,
	       SaHpiResourceIdT resource_id,
	       SaHpiEntryIdT num); 


int
update_event_status_flag(SaHpiDomainIdT domain_id,
			     SaHpiResourceIdT resource_id,
			     long event_status);

  /*
   * Handler for timestamp inforamtion
   */
int
update_timestamp_handler(netsnmp_mib_handler *handler,
			 netsnmp_handler_registration *reginfo,
			 netsnmp_agent_request_info *reqinfo,
			 netsnmp_request_info *requests);
/*************************************************************
 * oid declarations
 */
     extern oid      saHpiTable_oid[];
   extern size_t   saHpiTable_oid_len;

  //1,3,6,1,3,90,1,4

#define saHpiTable_TABLE_OID hpiEntity_OID,4

#define SCALAR_COLUMN_SAHPIENTRYUPDATETIMESTAMP 3
#define SCALAR_COLUMN_SAHPIENTRYUPDATECOUNT 2
#define SCALAR_COLUMN_SAHPIENTRYCOUNT 1

/*************************************************************
 * column number definitions for table saHpiTable
 */

#define COLUMN_SAHPIDOMAINID 1
#define COLUMN_SAHPIENTRYID 2
#define COLUMN_SAHPIRESOURCEID 3
#define COLUMN_SAHPIRESOURCEENTITYPATH 4
#define COLUMN_SAHPIRESOURCECAPABILITIES 5
#define COLUMN_SAHPIRESOURCESEVERITY 6
#define COLUMN_SAHPIRESOURCEINFORESOURCEREV 7
#define COLUMN_SAHPIRESOURCEINFOSPECIFICVER 8
#define COLUMN_SAHPIRESOURCEINFODEVICESUPPORT 9
#define COLUMN_SAHPIRESOURCEINFOMANUFACTURERID 10
#define COLUMN_SAHPIRESOURCEINFOPRODUCTID 11
#define COLUMN_SAHPIRESOURCEINFOFIRMWAREMAJORREV 12
#define COLUMN_SAHPIRESOURCEINFOFIRMWAREMINORREV 13
#define COLUMN_SAHPIRESOURCEINFOAUXFIRMWAREREV 14
#define COLUMN_SAHPIRESOURCETAGTEXTTYPE 15
#define COLUMN_SAHPIRESOURCETAGTEXTLANGUAGE 16
#define COLUMN_SAHPIRESOURCETAG 17
#define COLUMN_SAHPIPARAMCONTROL 18
#define COLUMN_SAHPICLEAREVENTS 19
#define COLUMN_SAHPIEVENTLOGTIME 20
#define COLUMN_SAHPIEVENTLOGSTATE 21
#define saHpiTable_COL_MIN 1
#define saHpiTable_COL_MAX 21



    int             saHpiTable_extract_index(saHpiTable_context * ctx,
                                             netsnmp_index * hdr);

    void            saHpiTable_set_reserve1(netsnmp_request_group *);
    void            saHpiTable_set_reserve2(netsnmp_request_group *);
    void            saHpiTable_set_action(netsnmp_request_group *);
    void            saHpiTable_set_commit(netsnmp_request_group *);
    void            saHpiTable_set_free(netsnmp_request_group *);
    void            saHpiTable_set_undo(netsnmp_request_group *);

    saHpiTable_context *saHpiTable_duplicate_row(saHpiTable_context *);
    netsnmp_index  *saHpiTable_delete_row(saHpiTable_context *);

    int             saHpiTable_can_delete(saHpiTable_context * undo_ctx,
                                          saHpiTable_context * row_ctx,
                                          netsnmp_request_group * rg);


    saHpiTable_context *saHpiTable_create_row(netsnmp_index *);



#ifdef __cplusplus
};
#endif

#endif /** SAHPITABLE_H */
