/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPISENSORTHDLOWCRITICALTABLE_H
#define SAHPISENSORTHDLOWCRITICALTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>
#include "SaHpi.h"

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiSensorNum is external */

typedef struct saHpiSensorThdLowCriticalTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** TruthValue = ASN_INTEGER */
            long saHpiSensorThdLowCriticalIsReadable;

        /** TruthValue = ASN_INTEGER */
            long saHpiSensorThdLowCriticalIsWritable;

        /** SaHpiSensorReadingType = ASN_INTEGER */
            long saHpiSensorThdLowCriticalType;

        /** SaHpiSensorReadingValue = ASN_OCTET_STR */
            unsigned char saHpiSensorThdLowCriticalValue[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiSensorThdLowCriticalValue_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiSensorThdLowCriticalTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiSensorThdLowCriticalTable(void);
void initialize_table_saHpiSensorThdLowCriticalTable(void);
const saHpiSensorThdLowCriticalTable_context * saHpiSensorThdLowCriticalTable_get_by_idx(netsnmp_index *);
const saHpiSensorThdLowCriticalTable_context * saHpiSensorThdLowCriticalTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiSensorThdLowCriticalTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
extern oid saHpiSensorThdLowCriticalTable_oid[];
extern size_t saHpiSensorThdLowCriticalTable_oid_len;

#define saHpiSensorThdLowCriticalTable_TABLE_OID 1,3,6,1,4,1,18568,1,1,1,6,3,7,7
    
/*************************************************************
 * column number definitions for table saHpiSensorThdLowCriticalTable
 */
#define COLUMN_SAHPISENSORTHDLOWCRITICALISREADABLE 1
#define COLUMN_SAHPISENSORTHDLOWCRITICALISWRITABLE 2
#define COLUMN_SAHPISENSORTHDLOWCRITICALTYPE 3
#define COLUMN_SAHPISENSORTHDLOWCRITICALVALUE 4
#define saHpiSensorThdLowCriticalTable_COL_MIN 1
#define saHpiSensorThdLowCriticalTable_COL_MAX 4

/* comment out the following line if you don't handle SET-REQUEST for saHpiSensorThdLowCriticalTable */
#define saHpiSensorThdLowCriticalTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiSensorThdLowCriticalTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiSensorThdLowCriticalTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiSensorThdLowCriticalTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiSensorThdLowCriticalTable_SET_HANDLING

int saHpiSensorThdLowCriticalTable_extract_index( saHpiSensorThdLowCriticalTable_context * ctx, netsnmp_index * hdr );

void saHpiSensorThdLowCriticalTable_set_reserve1( netsnmp_request_group * );
void saHpiSensorThdLowCriticalTable_set_reserve2( netsnmp_request_group * );
void saHpiSensorThdLowCriticalTable_set_action( netsnmp_request_group * );
void saHpiSensorThdLowCriticalTable_set_commit( netsnmp_request_group * );
void saHpiSensorThdLowCriticalTable_set_free( netsnmp_request_group * );
void saHpiSensorThdLowCriticalTable_set_undo( netsnmp_request_group * );

saHpiSensorThdLowCriticalTable_context * saHpiSensorThdLowCriticalTable_duplicate_row( saHpiSensorThdLowCriticalTable_context* );
netsnmp_index * saHpiSensorThdLowCriticalTable_delete_row( saHpiSensorThdLowCriticalTable_context* );

int saHpiSensorThdLowCriticalTable_can_activate(saHpiSensorThdLowCriticalTable_context *undo_ctx,
                      saHpiSensorThdLowCriticalTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiSensorThdLowCriticalTable_can_deactivate(saHpiSensorThdLowCriticalTable_context *undo_ctx,
                        saHpiSensorThdLowCriticalTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiSensorThdLowCriticalTable_can_delete(saHpiSensorThdLowCriticalTable_context *undo_ctx,
                    saHpiSensorThdLowCriticalTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiSensorThdLowCriticalTable_ROW_CREATION
saHpiSensorThdLowCriticalTable_context * saHpiSensorThdLowCriticalTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiSensorThdLowCriticalTable_IDX2
saHpiSensorThdLowCriticalTable_context * saHpiSensorThdLowCriticalTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPISENSORTHDLOWCRITICALTABLE_H */
