/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPICTRLOEMTABLE_H
#define SAHPICTRLOEMTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiResourceIsHistorical is external */
        /** Index saHpiCtrlOemEntryId is internal */

typedef struct saHpiCtrlOemTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiCtrlOemEntryId;

        /** SaHpiInstrumentId = ASN_UNSIGNED */
            unsigned long saHpiCtrlOemNum;

        /** SaHpiCtrlOutputType = ASN_INTEGER */
            long saHpiCtrlOemOutputType;

        /** SaHpiCtrlMode = ASN_INTEGER */
            long saHpiCtrlOemDefaultMode;

        /** SaHpiCtrlMode = ASN_INTEGER */
            long saHpiCtrlOemMode;

        /** TruthValue = ASN_INTEGER */
            long saHpiCtrlOemIsReadOnly;

        /** TruthValue = ASN_INTEGER */
            long saHpiCtrlOemIsWriteOnly;

        /** SaHpiManufacturerId = ASN_UNSIGNED */
            unsigned long saHpiCtrlOemManufacturerId;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiCtrlOemDefaultConfigData[SAHPI_CTRL_OEM_CONFIG_LENGTH];
            long saHpiCtrlOemDefaultConfigData_len;

        /** SaHpiManufacturerId = ASN_UNSIGNED */
            unsigned long saHpiCtrlOemDefaultMId;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiCtrlOemDefaultState[SAHPI_CTRL_MAX_OEM_BODY_LENGTH];
            long saHpiCtrlOemDefaultState_len;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiCtrlOemState[SAHPI_CTRL_MAX_OEM_BODY_LENGTH];
            long saHpiCtrlOemState_len;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiCtrlOemValue;

        /** RowPointer = ASN_OBJECT_ID */
            oid saHpiCtrlOemRDR[MAX_OID_LEN];
            long saHpiCtrlOemRDR_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiCtrlOemTable_context;

/*************************************************************
 * set funtions
 */
int set_table_ctrl_oem (saHpiCtrlOemTable_context *row_ctx);

/*************************************************************
 * function declarations
 */
SaErrorT populate_ctrl_oem (SaHpiSessionIdT sessionid, 
			    SaHpiRdrT *rdr_entry,
			    SaHpiRptEntryT *rpt_entry,
			    oid *full_oid, size_t full_oid_len,
			    oid *child_oid, size_t *child_oid_len);

/*************************************************************
 * function declarations
 */
void init_saHpiCtrlOemTable(void);
void initialize_table_saHpiCtrlOemTable(void);
const saHpiCtrlOemTable_context * saHpiCtrlOemTable_get_by_idx(netsnmp_index *);
const saHpiCtrlOemTable_context * saHpiCtrlOemTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiCtrlOemTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiCtrlOemTable_oid[];
extern size_t saHpiCtrlOemTable_oid_len;

#define saHpiCtrlOemTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,4,7,13


/* Number of table Indexes */
#define CTRL_OEM_INDEX_NR 4 
#define saHpiDomainId_INDEX 0
#define saHpiResourceEntryId_INDEX 1
#define saHpiResourceIsHistorical_INDEX 2
#define saHpiCtrlOemEntryId_INDEX 3
    
/*************************************************************
 * column number definitions for table saHpiCtrlOemTable
 */
#define COLUMN_SAHPICTRLOEMENTRYID 1
#define COLUMN_SAHPICTRLOEMNUM 2
#define COLUMN_SAHPICTRLOEMOUTPUTTYPE 3
#define COLUMN_SAHPICTRLOEMDEFAULTMODE 4
#define COLUMN_SAHPICTRLOEMMODE 5
#define COLUMN_SAHPICTRLOEMISREADONLY 6
#define COLUMN_SAHPICTRLOEMISWRITEONLY 7
#define COLUMN_SAHPICTRLOEMMANUFACTURERID 8
#define COLUMN_SAHPICTRLOEMDEFAULTCONFIGDATA 9
#define COLUMN_SAHPICTRLOEMDEFAULTMID 10
#define COLUMN_SAHPICTRLOEMDEFAULTSTATE 11
#define COLUMN_SAHPICTRLOEMSTATE 12
#define COLUMN_SAHPICTRLOEMVALUE 13
#define COLUMN_SAHPICTRLOEMRDR 14
#define saHpiCtrlOemTable_COL_MIN 2
#define saHpiCtrlOemTable_COL_MAX 14

/* comment out the following line if you don't handle SET-REQUEST for saHpiCtrlOemTable */
#define saHpiCtrlOemTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiCtrlOemTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiCtrlOemTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiCtrlOemTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiCtrlOemTable_SET_HANDLING

int saHpiCtrlOemTable_extract_index( saHpiCtrlOemTable_context * ctx, netsnmp_index * hdr );

void saHpiCtrlOemTable_set_reserve1( netsnmp_request_group * );
void saHpiCtrlOemTable_set_reserve2( netsnmp_request_group * );
void saHpiCtrlOemTable_set_action( netsnmp_request_group * );
void saHpiCtrlOemTable_set_commit( netsnmp_request_group * );
void saHpiCtrlOemTable_set_free( netsnmp_request_group * );
void saHpiCtrlOemTable_set_undo( netsnmp_request_group * );

saHpiCtrlOemTable_context * saHpiCtrlOemTable_duplicate_row( saHpiCtrlOemTable_context* );
netsnmp_index * saHpiCtrlOemTable_delete_row( saHpiCtrlOemTable_context* );

int saHpiCtrlOemTable_can_activate(saHpiCtrlOemTable_context *undo_ctx,
                      saHpiCtrlOemTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiCtrlOemTable_can_deactivate(saHpiCtrlOemTable_context *undo_ctx,
                        saHpiCtrlOemTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiCtrlOemTable_can_delete(saHpiCtrlOemTable_context *undo_ctx,
                    saHpiCtrlOemTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiCtrlOemTable_ROW_CREATION
saHpiCtrlOemTable_context * saHpiCtrlOemTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiCtrlOemTable_IDX2
saHpiCtrlOemTable_context * saHpiCtrlOemTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPICTRLOEMTABLE_H */