/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPISENSORENABLECHANGEEVENTTABLE_H
#define SAHPISENSORENABLECHANGEEVENTTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

        /** Index saHpiDomainId is external */
        /** Index saHpiResourceId is external */
        /** Index saHpiSensorNum is external */
        /** Index saHpiEventSeverity is external */
        /** Index saHpiSensorEnableChangeEventEntryId is internal */

typedef struct saHpiSensorEnableChangeEventTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiSensorEnableChangeEventEntryId;

        /** SaHpiTime = ASN_COUNTER64 */
    /** TODO: Is this type correct? */
            long saHpiSensorEnableChangeEventTimestamp;

        /** SaHpiSensorType = ASN_INTEGER */
            long saHpiSensorEnableChangeEventType;

        /** SaHpiEventCategory = ASN_INTEGER */
            long saHpiSensorEnableChangeEventCategory;

        /** TruthValue = ASN_INTEGER */
            long saHpiSensorEnableChangeEventEnabled;

        /** TruthValue = ASN_INTEGER */
            long saHpiSensorEnableChangeEventEventsEnabled;

        /** SaHpiEventState = ASN_OCTET_STR */
            unsigned char saHpiSensorEnableChangeEventAssertEvents[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiSensorEnableChangeEventAssertEvents_len;

        /** SaHpiEventState = ASN_OCTET_STR */
            unsigned char saHpiSensorEnableChangeEventDeassertEvents[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiSensorEnableChangeEventDeassertEvents_len;

        /** SaHpiOptionalData = ASN_OCTET_STR */
            unsigned char saHpiSensorEnableChangeEventOptionalData[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiSensorEnableChangeEventOptionalData_len;

        /** SaHpiEventState = ASN_OCTET_STR */
            unsigned char saHpiSensorEnableChangeEventState[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiSensorEnableChangeEventState_len;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiSensorEnableChangeEventTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiSensorEnableChangeEventTable(void);
void initialize_table_saHpiSensorEnableChangeEventTable(void);
const saHpiSensorEnableChangeEventTable_context * saHpiSensorEnableChangeEventTable_get_by_idx(netsnmp_index *);
const saHpiSensorEnableChangeEventTable_context * saHpiSensorEnableChangeEventTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiSensorEnableChangeEventTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);

/*************************************************************
 * function declarations: OpenHpi
 */
SaErrorT populate_saHpiSensorEnableChangeEventTable(SaHpiSessionIdT sessionid,
                                        SaHpiEventT *event,
                                        oid * event_oid, 
                                        size_t *event_oid_len);


/*************************************************************
 * oid declarations
 */
extern oid saHpiSensorEnableChangeEventTable_oid[];
extern size_t saHpiSensorEnableChangeEventTable_oid_len;

#define saHpiSensorEnableChangeEventTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,3,1,15
    
/*************************************************************
 * column number definitions for table saHpiSensorEnableChangeEventTable
 */
#define SENSOR_ENABLE_CHANGE_EVENT_INDEX_NR 5
#define COLUMN_SAHPISENSORENABLECHANGEEVENTENTRYID 1
#define COLUMN_SAHPISENSORENABLECHANGEEVENTTIMESTAMP 2
#define COLUMN_SAHPISENSORENABLECHANGEEVENTTYPE 3
#define COLUMN_SAHPISENSORENABLECHANGEEVENTCATEGORY 4
#define COLUMN_SAHPISENSORENABLECHANGEEVENTENABLED 5
#define COLUMN_SAHPISENSORENABLECHANGEEVENTEVENTSENABLED 6
#define COLUMN_SAHPISENSORENABLECHANGEEVENTASSERTEVENTS 7
#define COLUMN_SAHPISENSORENABLECHANGEEVENTDEASSERTEVENTS 8
#define COLUMN_SAHPISENSORENABLECHANGEEVENTOPTIONALDATA 9
#define COLUMN_SAHPISENSORENABLECHANGEEVENTSTATE 10
#define saHpiSensorEnableChangeEventTable_COL_MIN 2
#define saHpiSensorEnableChangeEventTable_COL_MAX 10

/* comment out the following line if you don't handle SET-REQUEST for saHpiSensorEnableChangeEventTable */
#define saHpiSensorEnableChangeEventTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiSensorEnableChangeEventTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiSensorEnableChangeEventTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiSensorEnableChangeEventTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiSensorEnableChangeEventTable_SET_HANDLING

int saHpiSensorEnableChangeEventTable_extract_index( saHpiSensorEnableChangeEventTable_context * ctx, netsnmp_index * hdr );

void saHpiSensorEnableChangeEventTable_set_reserve1( netsnmp_request_group * );
void saHpiSensorEnableChangeEventTable_set_reserve2( netsnmp_request_group * );
void saHpiSensorEnableChangeEventTable_set_action( netsnmp_request_group * );
void saHpiSensorEnableChangeEventTable_set_commit( netsnmp_request_group * );
void saHpiSensorEnableChangeEventTable_set_free( netsnmp_request_group * );
void saHpiSensorEnableChangeEventTable_set_undo( netsnmp_request_group * );

saHpiSensorEnableChangeEventTable_context * saHpiSensorEnableChangeEventTable_duplicate_row( saHpiSensorEnableChangeEventTable_context* );
netsnmp_index * saHpiSensorEnableChangeEventTable_delete_row( saHpiSensorEnableChangeEventTable_context* );

int saHpiSensorEnableChangeEventTable_can_activate(saHpiSensorEnableChangeEventTable_context *undo_ctx,
                      saHpiSensorEnableChangeEventTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiSensorEnableChangeEventTable_can_deactivate(saHpiSensorEnableChangeEventTable_context *undo_ctx,
                        saHpiSensorEnableChangeEventTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiSensorEnableChangeEventTable_can_delete(saHpiSensorEnableChangeEventTable_context *undo_ctx,
                    saHpiSensorEnableChangeEventTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiSensorEnableChangeEventTable_ROW_CREATION
saHpiSensorEnableChangeEventTable_context * saHpiSensorEnableChangeEventTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiSensorEnableChangeEventTable_IDX2
saHpiSensorEnableChangeEventTable_context * saHpiSensorEnableChangeEventTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPISENSORENABLECHANGEEVENTTABLE_H */
