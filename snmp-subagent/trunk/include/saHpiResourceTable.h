/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#ifndef SAHPIRESOURCETABLE_H
#define SAHPIRESOURCETABLE_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>

#include <SaHpi.h>
#include <oh_utils.h>

typedef struct saHpiResourceTable_context_s {
    netsnmp_index index; /** THIS MUST BE FIRST!!! */

    /*************************************************************
     * You can store data internally in this structure.
     */
        /** UNSIGNED32 = ASN_UNSIGNED */
            unsigned long saHpiResourceId;

        /** SaHpiEntryId = ASN_UNSIGNED */
            unsigned long saHpiResourceEntryId;

        /** SaHpiEntityPath = ASN_OCTET_STR */
            unsigned char saHpiResourceEntityPath[sizeof(oh_big_textbuffer)];
            long saHpiResourceEntityPath_len;

        /** BITS = ASN_OCTET_STR */
            unsigned char saHpiResourceCapabilities[sizeof(SaHpiUint16T)];
            long saHpiResourceCapabilities_len;

        /** BITS = ASN_OCTET_STR */
            unsigned char saHpiResourceHotSwapCapabilities[sizeof(SaHpiUint8T)];
            long saHpiResourceHotSwapCapabilities_len;

        /** SaHpiSeverity = ASN_INTEGER */
            long saHpiResourceSeverity;

        /** TruthValue = ASN_INTEGER */
            long saHpiResourceFailed;

        /** Unsigned8 = ASN_INTEGER */
            long saHpiResourceInfoResourceRev;

        /** Unsigned8 = ASN_INTEGER */
            long saHpiResourceInfoSpecificVer;

        /** Unsigned8 = ASN_INTEGER */
            long saHpiResourceInfoDeviceSupport;

        /** SaHpiManufacturerId = ASN_UNSIGNED */
            unsigned long saHpiResourceInfoManufacturerId;

        /** Unsigned16 = ASN_INTEGER */
            long saHpiResourceInfoProductId;

        /** Unsigned8 = ASN_INTEGER */
            long saHpiResourceInfoFirmwareMajorRev;

        /** Unsigned8 = ASN_INTEGER */
            long saHpiResourceInfoFirmwareMinorRev;

        /** Unsigned8 = ASN_INTEGER */
            long saHpiResourceInfoAuxFirmwareRev;

        /** SaHpiGuid = ASN_OCTET_STR */
            unsigned char saHpiResourceInfoGuid[sizeof(SaHpiGuidT)];
            long saHpiResourceInfoGuid_len;

        /** SaHpiTextType = ASN_INTEGER */
            long saHpiResourceTagTextType;

        /** SaHpiTextLanguage = ASN_INTEGER */
            long saHpiResourceTagTextLanguage;

        /** SaHpiText = ASN_OCTET_STR */
            unsigned char saHpiResourceTag[SAHPI_MAX_TEXT_BUFFER_LENGTH];
            long saHpiResourceTag_len;

        /** INTEGER = ASN_INTEGER */
            long saHpiResourceParmControl;

        /** INTEGER = ASN_INTEGER */
            long saHpiResourceResetAction;

        /** INTEGER = ASN_INTEGER */
            long saHpiResourcePowerAction;

        /** TruthValue = ASN_INTEGER */
            long saHpiResourceIsHistorical;


    /*
     * OR
     *
     * Keep a pointer to your data
     */
    void * data;

    /*
     *add anything else you want here
     */

} saHpiResourceTable_context;

/*************************************************************
 * function declarations: OpenHpi
 */
int populate_saHpiResourceTable(SaHpiSessionIdT sessionid);

/*************************************************************
 * function declarations
 */
void init_saHpiResourceTable(void);
void initialize_table_saHpiResourceTable(void);
const saHpiResourceTable_context * saHpiResourceTable_get_by_idx(netsnmp_index *);
const saHpiResourceTable_context * saHpiResourceTable_get_by_idx_rs(netsnmp_index *,
                                        int row_status);
int saHpiResourceTable_get_value(netsnmp_request_info *, netsnmp_index *, netsnmp_table_request_info *);


/*************************************************************
 * set funtions
 */
int set_table_severity (saHpiResourceTable_context *row_ctx);
int set_table_resource_parm_control (saHpiResourceTable_context *row_ctx);
int set_table_resource_reset_action (saHpiResourceTable_context *row_ctx);
int set_table_resource_power_action (saHpiResourceTable_context *row_ctx);


/*************************************************************
 * oid and fucntion declarations scalars
 */
static oid saHpiResourceEntryCount_oid[] = { 1,3,6,1,4,1,18568,2,1,1,2,7 };
int handle_saHpiResourceEntryCount( netsnmp_mib_handler 	*handler,
				    netsnmp_handler_registration *reginfo,
				    netsnmp_agent_request_info   *reqinfo,
				    netsnmp_request_info         *requests);
int initialize_table_saHpiResourceEntryCount(void);
SaErrorT async_resource_add(SaHpiSessionIdT sessionid, SaHpiEventT *event, 
                         SaHpiRdrT *rdr, SaHpiRptEntryT *rpt_entry);

/*************************************************************
 * oid declarations
 */
extern oid saHpiResourceTable_oid[];
extern size_t saHpiResourceTable_oid_len;

#define saHpiResourceTable_TABLE_OID 1,3,6,1,4,1,18568,2,1,1,2,8

/* Number of table Indexes */
#define RESOURCE_INDEX_NR 3 
#define saHpiDomainId_INDEX 0
#define saHpiResourceEntryId_INDEX 1
#define saHpiResourceIsHistorical_INDEX 2
    
/*************************************************************
 * column number definitions for table saHpiResourceTable
 */
#define COLUMN_SAHPIRESOURCEID 1
#define COLUMN_SAHPIRESOURCEENTRYID 2
#define COLUMN_SAHPIRESOURCEENTITYPATH 3
#define COLUMN_SAHPIRESOURCECAPABILITIES 4
#define COLUMN_SAHPIRESOURCEHOTSWAPCAPABILITIES 5
#define COLUMN_SAHPIRESOURCESEVERITY 6
#define COLUMN_SAHPIRESOURCEFAILED 7
#define COLUMN_SAHPIRESOURCEINFORESOURCEREV 8
#define COLUMN_SAHPIRESOURCEINFOSPECIFICVER 9
#define COLUMN_SAHPIRESOURCEINFODEVICESUPPORT 10
#define COLUMN_SAHPIRESOURCEINFOMANUFACTURERID 11
#define COLUMN_SAHPIRESOURCEINFOPRODUCTID 12
#define COLUMN_SAHPIRESOURCEINFOFIRMWAREMAJORREV 13
#define COLUMN_SAHPIRESOURCEINFOFIRMWAREMINORREV 14
#define COLUMN_SAHPIRESOURCEINFOAUXFIRMWAREREV 15
#define COLUMN_SAHPIRESOURCEINFOGUID 16
#define COLUMN_SAHPIRESOURCETAGTEXTTYPE 17
#define COLUMN_SAHPIRESOURCETAGTEXTLANGUAGE 18
#define COLUMN_SAHPIRESOURCETAG 19
#define COLUMN_SAHPIRESOURCEPARMCONTROL 20
#define COLUMN_SAHPIRESOURCERESETACTION 21
#define COLUMN_SAHPIRESOURCEPOWERACTION 22
#define COLUMN_SAHPIRESOURCEISHISTORICAL 23
#define saHpiResourceTable_COL_MIN 1
#define saHpiResourceTable_COL_MAX 23

/* comment out the following line if you don't handle SET-REQUEST for saHpiResourceTable */
#define saHpiResourceTable_SET_HANDLING

/* comment out the following line if you can't create new rows */
#define saHpiResourceTable_ROW_CREATION

/* comment out the following line if you don't want the secondary index */
#define saHpiResourceTable_IDX2

/* uncommend the following line if you allow modifications to an
 * active row */
/** define saHpiResourceTable_CAN_MODIFY_ACTIVE_ROW */

int saHpiResourceTable_extract_index( saHpiResourceTable_context * ctx, netsnmp_index * hdr );

void saHpiResourceTable_set_reserve1( netsnmp_request_group * );
void saHpiResourceTable_set_reserve2( netsnmp_request_group * );
void saHpiResourceTable_set_action( netsnmp_request_group * );
void saHpiResourceTable_set_commit( netsnmp_request_group * );
void saHpiResourceTable_set_free( netsnmp_request_group * );
void saHpiResourceTable_set_undo( netsnmp_request_group * );

saHpiResourceTable_context * saHpiResourceTable_duplicate_row( saHpiResourceTable_context* );
netsnmp_index * saHpiResourceTable_delete_row( saHpiResourceTable_context* );

int saHpiResourceTable_can_activate(saHpiResourceTable_context *undo_ctx,
                      saHpiResourceTable_context *row_ctx,
                      netsnmp_request_group * rg);
int saHpiResourceTable_can_deactivate(saHpiResourceTable_context *undo_ctx,
                        saHpiResourceTable_context *row_ctx,
                        netsnmp_request_group * rg);
int saHpiResourceTable_can_delete(saHpiResourceTable_context *undo_ctx,
                    saHpiResourceTable_context *row_ctx,
                    netsnmp_request_group * rg);
    
saHpiResourceTable_context * saHpiResourceTable_create_row( netsnmp_index* );

saHpiResourceTable_context * saHpiResourceTable_get( const char *name, int len );

#ifdef __cplusplus
};
#endif

#endif /** SAHPIRESOURCETABLE_H */
