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
#ifndef SAHPIHOTSWAPTABLE_H
#define SAHPIHOTSWAPTABLE_H

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
#define HOTSWAP_INDEX_NR 2

  /* Per the MIB
   */
#define MIB_OFF 2
#define MIB_ON 1

    typedef struct saHpiHotSwapTable_context_s {
        netsnmp_index   index;
   
        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapIndicator;

        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapPowerState;

        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapResetState;

        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapState;

        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapPreviousState;

        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapEventSeverity;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiHotSwapInsertTimeout;

        /** UNSIGNED32 = ASN_UNSIGNED */
        unsigned long   saHpiHotSwapExtractTimeout;

        /** INTEGER = ASN_INTEGER */
        long            saHpiHotSwapActionRequest;

        /** RowPointer = ASN_OBJECT_ID */
        oid             saHpiHotSwapRTP[MAX_OID_LEN];
        long            saHpiHotSwapRTP_len;

      long hash;
      long domain_id;
      long resource_id;
      
    } saHpiHotSwapTable_context;

    void            initialize_table_saHpiHotSwapTable(void);

    int             saHpiHotSwapTable_get_value(netsnmp_request_info *,
                                                netsnmp_index *,
                                                netsnmp_table_request_info
                                                *);

int
populate_hotswap(SaHpiRptEntryT *rpt_entry,
		 oid *rpt_oid, size_t rpt_oid_len);

  /* Write methods
   */
int 
set_hotswap_indicator(saHpiHotSwapTable_context *ctx);
int
  set_hotswap_powerstate(saHpiHotSwapTable_context *ctx);
int
 set_hotswap_reset_state(saHpiHotSwapTable_context *ctx);
int
  set_hotswap_insert_t(saHpiHotSwapTable_context *ctx);
int
  set_hotswap_extract_t(saHpiHotSwapTable_context *ctx);
int
  set_hotswap_action_request(saHpiHotSwapTable_context *ctx);

int
delete_hotswap_row(SaHpiDomainIdT ,
		   SaHpiResourceIdT);

int
update_hotswap_event(SaHpiDomainIdT,
		     SaHpiResourceIdT,
		     SaHpiHotSwapEventT *);
/*************************************************************
 * oid declarations
 */
//    extern oid      saHpiHotSwapTable_oid[];
  //   extern size_t   saHpiHotSwapTable_oid_len;
//1,3,6,1,3,90,3,11
#define saHpiHotSwapTable_TABLE_OID hpiResources_OID,11


/*************************************************************
 * column number definitions for table saHpiHotSwapTable
 */
#define COLUMN_SAHPIHOTSWAPINDICATOR 1
#define COLUMN_SAHPIHOTSWAPPOWERSTATE 2
#define COLUMN_SAHPIHOTSWAPRESETSTATE 3
#define COLUMN_SAHPIHOTSWAPSTATE 4
#define COLUMN_SAHPIHOTSWAPPREVIOUSSTATE 5
#define COLUMN_SAHPIHOTSWAPEVENTSEVERITY 6
#define COLUMN_SAHPIHOTSWAPINSERTTIMEOUT 7
#define COLUMN_SAHPIHOTSWAPEXTRACTTIMEOUT 8
#define COLUMN_SAHPIHOTSWAPACTIONREQUEST 9
#define COLUMN_SAHPIHOTSWAPRTP 10
#define saHpiHotSwapTable_COL_MIN 1
#define saHpiHotSwapTable_COL_MAX 10


    int            
        saHpiHotSwapTable_extract_index(saHpiHotSwapTable_context * ctx,
                                        netsnmp_index * hdr);

    void            saHpiHotSwapTable_set_reserve1(netsnmp_request_group
                                                   *);
    void            saHpiHotSwapTable_set_reserve2(netsnmp_request_group
                                                   *);
    void            saHpiHotSwapTable_set_action(netsnmp_request_group *);
    void            saHpiHotSwapTable_set_commit(netsnmp_request_group *);
    void            saHpiHotSwapTable_set_free(netsnmp_request_group *);
    void            saHpiHotSwapTable_set_undo(netsnmp_request_group *);

    saHpiHotSwapTable_context
        *saHpiHotSwapTable_duplicate_row(saHpiHotSwapTable_context *);
    netsnmp_index  *saHpiHotSwapTable_delete_row(saHpiHotSwapTable_context
                                                 *);

  
    int             saHpiHotSwapTable_can_delete(saHpiHotSwapTable_context
                                                 * undo_ctx,
                                                 saHpiHotSwapTable_context
                                                 * row_ctx,
                                                 netsnmp_request_group *
                                                 rg);



    saHpiHotSwapTable_context *saHpiHotSwapTable_create_row(netsnmp_index
                                                            *);

#ifdef __cplusplus
};
#endif

#endif /** SAHPIHOTSWAPTABLE_H */