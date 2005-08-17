/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIDOMAINALARMTABLE_H
#define SAHPIDOMAINALARMTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <oh_utils.h> /* For OH_MAX_TEXT_BUFFER_LENGTH */

        /** Index saHpiDomainId is external */
        /** Index saHpiDomainAlarmId is internal */
        /** Index saHpiDomainAlarmSeverity is internal */

typedef struct saHpiDomainAlarmTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    int sahpi_domain_alarm_severity_set;
    int sahpi_domain_alarm_acknowledged_set;
    int sahpi_domain_alarm_status_cond_type_set;
    int sahpi_domain_alarm_entitypath_set;
    int sahpi_domain_alarm_sensornum_set;
    int sahpi_domain_alarm_event_state_set;
    int sahpi_domain_alarm_name_set;
    int sahpi_domain_alarm_mid;
    int sahpi_domain_alarm_text_type_set;
    int sahpi_domain_alarm_text_language_set;
    int sahpi_domain_alarm_text;

    /*************************************************************
     * You can store data internally in this structure.
     *
     * TODO: You will probably have to fix a few types here...
     */
    /** TODO: add storage for external index(s)! */
        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiDomainAlarmId;

        /** SaHpiTime = ASN_COUNTER64 */
    /** TODO: Is this type correct? */
            long saHpiDomainAlarmTimestamp;

        /** SaHpiSeverity = ASN_INTEGER */
            long saHpiDomainAlarmSeverity;

        /** TruthValue = ASN_INTEGER */
            long saHpiDomainAlarmAcknowledged;

        /** SaHpiSeverity = ASN_INTEGER */
            long saHpiDomainAlarmAckBySeverity;

        /** INTEGER = ASN_INTEGER */
            long saHpiDomainAlarmCondStatusCondType;

        /** SaHpiEntityPath = ASN_OCTET_STR */
            unsigned char saHpiDomainAlarmCondEntityPath[OH_MAX_TEXT_BUFFER_LENGTH];
            long saHpiDomainAlarmCondEntityPath_len;

        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiDomainAlarmCondSensorNum;

        /** SaHpiEventState = ASN_OCTET_STR */
            unsigned char saHpiDomainAlarmCondEventState[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiDomainAlarmCondEventState_len;

        /** OCTETSTR = ASN_OCTET_STR */
            unsigned char saHpiDomainAlarmCondNameValue[SA_HPI_MAX_NAME_LENGTH];
            long saHpiDomainAlarmCondNameValue_len;

        /** SaHpiManufacturerId = ASN_UNSIGNED */
            unsigned long saHpiDomainAlarmCondMid;

        /** SaHpiTextType = ASN_INTEGER */
            long saHpiDomainAlarmCondTextType;

        /** SaHpiTextLanguage = ASN_INTEGER */
            long saHpiDomainAlarmCondTextLanguage;

        /** SaHpiText = ASN_OCTET_STR */
            unsigned char saHpiDomainAlarmCondText[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiDomainAlarmCondText_len;

        /** RowStatus = ASN_INTEGER */
            long saHpiDomainAlarmRowStatus;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiDomainAlarmTable_context;

/*************************************************************
 * function declarations
 */
void init_saHpiDomainAlarmTable(void);
void initialize_table_saHpiDomainAlarmTable(void);
const saHpiDomainAlarmTable_context * saHpiDomainAlarmTable_get_by_idx(netsnmp_index *);
const saHpiDomainAlarmTable_context * saHpiDomainAlarmTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiDomainAlarmTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);

/*************************************************************
 * function declarations: OpenHpi
 */
SaErrorT populate_saHpiDomainAlarmTable(SaHpiSessionIdT sessionid);

int domain_alarm_delete(saHpiDomainAlarmTable_context *row_ctx);
				      
/*************************************************************
 * oid declarations
 */
extern oid saHpiDomainAlarmTable_oid[];
extern size_t saHpiDomainAlarmTable_oid_len;

#define saHpiDomainAlarmTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,2,6
 
 
/*************************************************************
 * defines included from hpiB0101_enums.h
 */
#define SAHPIDOMAINALARMROWSTATUS_ACTIVE	     1
#define SAHPIDOMAINALARMROWSTATUS_NOTINSERVICE       2
#define SAHPIDOMAINALARMROWSTATUS_NOTREADY	     3
#define SAHPIDOMAINALARMROWSTATUS_CREATEANDGO	     4
#define SAHPIDOMAINALARMROWSTATUS_CREATEANDWAIT      5
#define SAHPIDOMAINALARMROWSTATUS_DESTROY	     6
	       
/*************************************************************
 * column number definitions for table saHpiDomainAlarmTable
 */
 
#define saHpiDomainAlarmDomainId_INDEX 0
#define saHpiDomainAlarmEntryId_INDEX 1
 
#define DOMAIN_ALARM_INDEX_NR 3
#define COLUMN_SAHPIDOMAINALARMID 1
#define COLUMN_SAHPIDOMAINALARMTIMESTAMP 2
#define COLUMN_SAHPIDOMAINALARMSEVERITY 3
#define COLUMN_SAHPIDOMAINALARMACKNOWLEDGED 4
#define COLUMN_SAHPIDOMAINALARMACKBYSEVERITY 5
#define COLUMN_SAHPIDOMAINALARMCONDSTATUSCONDTYPE 6
#define COLUMN_SAHPIDOMAINALARMCONDENTITYPATH 7
#define COLUMN_SAHPIDOMAINALARMCONDSENSORNUM 8
#define COLUMN_SAHPIDOMAINALARMCONDEVENTSTATE 9
#define COLUMN_SAHPIDOMAINALARMCONDNAMEVALUE 10
#define COLUMN_SAHPIDOMAINALARMCONDMID 11
#define COLUMN_SAHPIDOMAINALARMCONDTEXTTYPE 12
#define COLUMN_SAHPIDOMAINALARMCONDTEXTLANGUAGE 13
#define COLUMN_SAHPIDOMAINALARMCONDTEXT 14
#define COLUMN_SAHPIDOMAINALARMROWSTATUS 15
#define saHpiDomainAlarmTable_COL_MIN 2
#define saHpiDomainAlarmTable_COL_MAX 15

/* comment out the following line if you don't handle SET-REQUEST for saHpiDomainAlarmTable */
#define saHpiDomainAlarmTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiDomainAlarmTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiDomainAlarmTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiDomainAlarmTable_CAN_MODIFY_ACTIVE_ROW */

#ifdef saHpiDomainAlarmTable_SET_HANDLING

int saHpiDomainAlarmTable_extract_index( saHpiDomainAlarmTable_context * ctx, netsnmp_index * hdr );

void saHpiDomainAlarmTable_set_reserve1( netsnmp_request_group * );
void saHpiDomainAlarmTable_set_reserve2( netsnmp_request_group * );
void saHpiDomainAlarmTable_set_action( netsnmp_request_group * );
void saHpiDomainAlarmTable_set_commit( netsnmp_request_group * );
void saHpiDomainAlarmTable_set_free( netsnmp_request_group * );
void saHpiDomainAlarmTable_set_undo( netsnmp_request_group * );

saHpiDomainAlarmTable_context * saHpiDomainAlarmTable_duplicate_row( saHpiDomainAlarmTable_context* );
netsnmp_index * saHpiDomainAlarmTable_delete_row( saHpiDomainAlarmTable_context* );

int saHpiDomainAlarmTable_can_activate(saHpiDomainAlarmTable_context *undo_ctx,
                      saHpiDomainAlarmTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiDomainAlarmTable_can_deactivate(saHpiDomainAlarmTable_context *undo_ctx,
                        saHpiDomainAlarmTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiDomainAlarmTable_can_delete(saHpiDomainAlarmTable_context *undo_ctx,
                    saHpiDomainAlarmTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
    
#ifdef saHpiDomainAlarmTable_ROW_CREATION
saHpiDomainAlarmTable_context * saHpiDomainAlarmTable_create_row( netsnmp_index* );
#endif
#endif

#ifdef saHpiDomainAlarmTable_IDX2
saHpiDomainAlarmTable_context * saHpiDomainAlarmTable_get( const char *name, int len );
#endif

#ifdef __cplusplus
};
#endif

#endif /** SAHPIDOMAINALARMTABLE_H */
