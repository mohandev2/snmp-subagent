/*
 * (C) Copyright IBM Corp. 2004
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

 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.array-user.conf,v 5.18 2003/11/07 17:03:52 rstory Exp $
 *
 * $Id$
 *
 */
#ifndef SAHPISENSORREADINGNORMALMINTABLE_H
#define SAHPISENSORREADINGNORMALMINTABLE_H

#ifdef __cplusplus
extern "C"
{
#endif


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/library/container.h>
#include <net-snmp/agent/table_array.h>
#include <SaHpi.h>
#include <hpiSubagent.h>


	/** Index saHpiDomainID is external */
	/** Index saHpiResourceID is external */
	/** Index saHpiSensorIndex is external */

  typedef struct saHpiSensorReadingNormalMinTable_context_s
  {
    netsnmp_index index;
	/** INTEGER = ASN_INTEGER */
    long saHpiSensorReadingNormalMinValuesPresent;

	/** UNSIGNED32 = ASN_UNSIGNED */
    unsigned long saHpiSensorReadingNormalMinRaw;

	/** OCTETSTR = ASN_OCTET_STR */
    unsigned char
      saHpiSensorReadingNormalMinInterpreted[SENSOR_READING_INTER_MAX];
    size_t saHpiSensorReadingNormalMinInterpreted_len;

	/** INTEGER = ASN_INTEGER */
    long saHpiSensorReadingNormalMinStatus;

	/** OCTETSTR = ASN_OCTET_STR */
    unsigned char
      saHpiSensorReadingNormalMinEventStatus[SENSOR_READING_EVENT_MAX];
    size_t saHpiSensorReadingNormalMinEventStatus_len;

    SaHpiResourceIdT resource_id;
    SaHpiDomainIdT domain_id;
    SaHpiSensorNumT sensor_id;
    long hash;


  } saHpiSensorReadingNormalMinTable_context;

/*************************************************************
 * function declarations
 */

  void initialize_table_saHpiSensorReadingNormalMinTable (void);

  int
    delete_ReadingNormalMin_row (SaHpiDomainIdT domain_id,
			       SaHpiResourceIdT resource_id,
			       SaHpiSensorNumT num);

  int populate_ReadingNormalMin (SaHpiDomainIdT domain_id,
			       SaHpiResourceIdT resource_id,
			       SaHpiSensorNumT sensor_id,
			       SaHpiEventCategoryT sensor_category,
			       SaHpiSensorReadingT * reading);


  int
    saHpiSensorReadingNormalMinTable_get_value (netsnmp_request_info *,
					      netsnmp_index *,
					      netsnmp_table_request_info *);


/*************************************************************
 * oid declarations
 */
  extern oid saHpiSensorReadingNormalMinTable_oid[];
  extern size_t saHpiSensorReadingNormalMinTable_oid_len;

#define saHpiSensorReadingNormalMinTable_TABLE_OID hpiSensor_OID,6

/*************************************************************
 * column number definitions for table saHpiSensorReadingNormalMinTable
 */
#define COLUMN_SAHPISENSORREADINGNORMALMINVALUESPRESENT 1
#define COLUMN_SAHPISENSORREADINGNORMALMINRAW 2
#define COLUMN_SAHPISENSORREADINGNORMALMININTERPRETED 3
#define COLUMN_SAHPISENSORREADINGNORMALMINSTATUS 4
#define COLUMN_SAHPISENSORREADINGNORMALMINEVENTSTATUS 5
#define saHpiSensorReadingNormalMinTable_COL_MIN 1
#define saHpiSensorReadingNormalMinTable_COL_MAX 5

  int
    saHpiSensorReadingNormalMinTable_extract_index
    (saHpiSensorReadingNormalMinTable_context * ctx, netsnmp_index * hdr);

  void saHpiSensorReadingNormalMinTable_set_reserve1 (netsnmp_request_group *);
  void saHpiSensorReadingNormalMinTable_set_reserve2 (netsnmp_request_group *);
  void saHpiSensorReadingNormalMinTable_set_action (netsnmp_request_group *);
  void saHpiSensorReadingNormalMinTable_set_commit (netsnmp_request_group *);
  void saHpiSensorReadingNormalMinTable_set_free (netsnmp_request_group *);
  void saHpiSensorReadingNormalMinTable_set_undo (netsnmp_request_group *);

    saHpiSensorReadingNormalMinTable_context
    * saHpiSensorReadingNormalMinTable_duplicate_row
    (saHpiSensorReadingNormalMinTable_context *);
    netsnmp_index
    * saHpiSensorReadingNormalMinTable_delete_row
    (saHpiSensorReadingNormalMinTable_context *);

  int
    saHpiSensorReadingNormalMinTable_can_delete
    (saHpiSensorReadingNormalMinTable_context * undo_ctx,
     saHpiSensorReadingNormalMinTable_context * row_ctx,
     netsnmp_request_group * rg);



    saHpiSensorReadingNormalMinTable_context
    * saHpiSensorReadingNormalMinTable_create_row (netsnmp_index *);

#ifdef __cplusplus
};
#endif

#endif /** SAHPISENSORREADINGNORMALMINTABLE_H */
