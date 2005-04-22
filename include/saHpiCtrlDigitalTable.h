/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPICTRLDIGITALTABLE_H
#define SAHPICTRLDIGITALTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <SaHpi.h>
#include <oh_utils.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiResourceIsHistorical is external */
        /** Index saHpiCtrlDigitalEntryId is internal */

typedef struct saHpiCtrlDigitalTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiCtrlDigitalEntryId;

        /** SaHpiInstrumentId = ASN_UNSIGNED */
            unsigned long saHpiCtrlDigitalNum;

        /** SaHpiCtrlOutputType = ASN_INTEGER */
            long saHpiCtrlDigitalOutputType;

        /** SaHpiCtrlMode = ASN_INTEGER */
            long saHpiCtrlDigitalDefaultMode;

        /** SaHpiCtrlMode = ASN_INTEGER */
            long saHpiCtrlDigitalMode;

        /** TruthValue = ASN_INTEGER */
            long saHpiCtrlDigitalIsReadOnly;

        /** TruthValue = ASN_INTEGER */
            long saHpiCtrlDigitalIsWriteOnly;

        /** SaHpiCtrlStateDigital = ASN_INTEGER */
            long saHpiCtrlDigitalDefaultState;

        /** SaHpiCtrlStateDigital = ASN_INTEGER */
            long saHpiCtrlDigitalState;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiCtrlDigitalOem;

        /** RowPointer = ASN_OBJECT_ID */
            oid saHpiCtrlDigitalRDR[MAX_OID_LEN];
            long saHpiCtrlDigitalRDR_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiCtrlDigitalTable_context;

/*************************************************************
 * function declarations
 */
SaErrorT populate_ctrl_digital(SaHpiSessionIdT sessionid, 
			       SaHpiRdrT *rdr_entry,
			       SaHpiRptEntryT *rpt_entry,
			       oid *full_oid, size_t full_oid_len,
			       oid *child_oid, size_t *child_oid_len);

/*************************************************************
 * function declarations
 */
void init_saHpiCtrlDigitalTable(void);
void initialize_table_saHpiCtrlDigitalTable(void);
const saHpiCtrlDigitalTable_context * saHpiCtrlDigitalTable_get_by_idx(netsnmp_index *);
const saHpiCtrlDigitalTable_context * saHpiCtrlDigitalTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiCtrlDigitalTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiCtrlDigitalTable_oid[];
extern size_t saHpiCtrlDigitalTable_oid_len;

#define saHpiCtrlDigitalTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,4,7,2

/* Number of table Indexes */
#define CTRL_DIGITAL_INDEX_NR 4 
#define saHpiDomainId_INDEX 0
#define saHpiResourceEntryId_INDEX 1
#define saHpiResourceIsHistorical_INDEX 2
#define saHpiCtrlDigitalEntryId_INDEX 3
    
/*************************************************************
 * column number definitions for table saHpiCtrlDigitalTable
 */
#define COLUMN_SAHPICTRLDIGITALENTRYID 1
#define COLUMN_SAHPICTRLDIGITALNUM 2
#define COLUMN_SAHPICTRLDIGITALOUTPUTTYPE 3
#define COLUMN_SAHPICTRLDIGITALDEFAULTMODE 5
#define COLUMN_SAHPICTRLDIGITALMODE 6
#define COLUMN_SAHPICTRLDIGITALISREADONLY 7
#define COLUMN_SAHPICTRLDIGITALISWRITEONLY 8
#define COLUMN_SAHPICTRLDIGITALDEFAULTSTATE 9
#define COLUMN_SAHPICTRLDIGITALSTATE 10
#define COLUMN_SAHPICTRLDIGITALOEM 11
#define COLUMN_SAHPICTRLDIGITALRDR 12
#define saHpiCtrlDigitalTable_COL_MIN 2
#define saHpiCtrlDigitalTable_COL_MAX 12

/* comment out the following line if you don't handle SET-REQUEST for saHpiCtrlDigitalTable */
#define saHpiCtrlDigitalTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiCtrlDigitalTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiCtrlDigitalTable_IDX2

#ifdef saHpiCtrlDigitalTable_SET_HANDLING

int saHpiCtrlDigitalTable_extract_index( saHpiCtrlDigitalTable_context * ctx, netsnmp_index * hdr );

void saHpiCtrlDigitalTable_set_reserve1( netsnmp_request_group * );
void saHpiCtrlDigitalTable_set_reserve2( netsnmp_request_group * );
void saHpiCtrlDigitalTable_set_action( netsnmp_request_group * );
void saHpiCtrlDigitalTable_set_commit( netsnmp_request_group * );
void saHpiCtrlDigitalTable_set_free( netsnmp_request_group * );
void saHpiCtrlDigitalTable_set_undo( netsnmp_request_group * );

saHpiCtrlDigitalTable_context * saHpiCtrlDigitalTable_duplicate_row( saHpiCtrlDigitalTable_context* );
netsnmp_index * saHpiCtrlDigitalTable_delete_row( saHpiCtrlDigitalTable_context* );

int saHpiCtrlDigitalTable_can_delete(saHpiCtrlDigitalTable_context *undo_ctx,
                    saHpiCtrlDigitalTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiCtrlDigitalTable_ROW_CREATION
saHpiCtrlDigitalTable_context * saHpiCtrlDigitalTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiCtrlDigitalTable_IDX2
saHpiCtrlDigitalTable_context * saHpiCtrlDigitalTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPICTRLDIGITALTABLE_H */
