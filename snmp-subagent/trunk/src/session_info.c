/*
 * (C) Copyright IBM Corp. 2005
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
 * file and program are licensed under a BSD style license.  See
 * the Copying file included with the OpenHPI distribution for
 * full licensing terms.
 *
 * Authors:
 *   David Judkovics  <djudkovi@us.ibm.com>
 *
 *					  
 */
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <signal.h>



#include <SaHpi.h> 
#include <oh_utils.h>

#include <alarm.h>

#include <hpiSubagent.h>     
#include <session_info.h>

static SaHpiSessionIdT stored_session_id;
static SaHpiDomainIdT stored_domain_id;

/**************************************************/
/*** BEGIN: ***************************************/
/*** Manages All existing sessions and domains  ***/
/**************************************************/
/**
 * 
 * @session_id:
 * @domain_id:
 */
void store_session_info(SaHpiSessionIdT session_id, SaHpiDomainIdT domain_id)
{
	stored_session_id = session_id;
	stored_domain_id = domain_id;
}

/**
 * 
 * @domain_id:
 * 
 * @return:
 */
SaHpiSessionIdT get_session_id(SaHpiDomainIdT domain_id)
{
	return( stored_session_id );
}

/**
 * 
 * @session_id:
 * 
 * @return: 
 */
SaHpiDomainIdT get_domain_id(SaHpiSessionIdT session_id)
{
	return( stored_domain_id );
}

int subcsribe_all_sessions(void)
{
        SaErrorT rc = SA_OK;

        rc = saHpiSubscribe(stored_session_id);

        if (rc == SA_OK) {
                DEBUGMSGTL ((AGENT, "subcsribe_all_sessions() SUCCEEDED!!!!!!!\n"));
                return SNMP_ERR_NOERROR; 
        } else if (rc != SA_OK) {
                snmp_log (LOG_ERR,
                          "subcsribe_all_sessions: Call to saHpiSubscribe() failed to set Mode rc: %s.\n",
                          oh_lookup_error(rc));
                DEBUGMSGTL ((AGENT,
                             "subcsribe_all_sessions: Call to saHpiSubscribe() failed to set Mode rc: %s.\n",
                             oh_lookup_error(rc)));
                return get_snmp_error(rc);
        }

        return SA_ERR_HPI_ERROR;
}
/**************************************************/
/*** END: *****************************************/
/*** Manages All existing sessions and domains  ***/
/**************************************************/



/*
 *  int build_full_oid()
 */
int build_full_oid (oid * prefix, size_t prefix_len,
		    oid * column, size_t column_len,
		    netsnmp_index * index,
		    oid * out_oid, size_t in_len, size_t * out_len)
{

	int register len = prefix_len + column_len;
	int register i = 0;

	DEBUGMSGTL((AGENT, "build_full_oid() called\n"));

	if (index)
		len += index->len;

	if (len > in_len)
		return AGENT_ERR_MEMORY_FAULT;

	*out_len = len;
	memcpy (out_oid, prefix, prefix_len * sizeof (oid));

	for (; i < column_len; i++) {
		out_oid[prefix_len + i] = column[i];
	}
	len = prefix_len + i;

	if (index) {
		for (i = 0; i < index->len; i++) {
			out_oid[len + i] = index->oids[i];
		}
	}
	return AGENT_ERR_NOERROR;
}

/**************************************************/
/*** BEGIN: ***************************************/
/*** Translates from HPI to SNMP Error Codes s  ***/
/**************************************************/
/**************************************************/
/*
 * int get_snmp_error(SaErrorT val) 
 */
int get_snmp_error(SaErrorT val) 
{
	switch (val) {
	case SA_ERR_HPI_ERROR:
		return SNMP_ERR_GENERR;
		break;
	case SA_ERR_HPI_UNSUPPORTED_API:
		return SNMP_ERR_GENERR;
		break;
	case SA_ERR_HPI_BUSY:
		return SNMP_ERR_GENERR;
		break;
	case SA_ERR_HPI_INTERNAL_ERROR:
		return SNMP_ERR_GENERR;
		break;
	case SA_ERR_HPI_INVALID_CMD:
		return SNMP_ERR_GENERR;
		break;
	case SA_ERR_HPI_TIMEOUT:
		return SNMP_ERR_RESOURCEUNAVAILABLE;
		break;
	case SA_ERR_HPI_OUT_OF_SPACE:
		return SNMP_ERR_TOOBIG;
		break;
	case SA_ERR_HPI_OUT_OF_MEMORY:
		return SNMP_ERR_TOOBIG;
		break;
	case SA_ERR_HPI_INVALID_PARAMS:
		return SNMP_ERR_INCONSISTENTVALUE;
		break;
	case SA_ERR_HPI_INVALID_DATA:
		return SNMP_ERR_WRONGVALUE;
		break;
	case SA_ERR_HPI_NOT_PRESENT:
		return SNMP_ERR_NOSUCHNAME;
		break;
	case SA_ERR_HPI_NO_RESPONSE:
		return SNMP_ERR_RESOURCEUNAVAILABLE;
		break;
	case SA_ERR_HPI_DUPLICATE:
		return SNMP_ERR_INCONSISTENTNAME;
		break;
	case SA_ERR_HPI_INVALID_SESSION:
		return SNMP_ERR_INCONSISTENTNAME;
		break;
	case SA_ERR_HPI_INVALID_DOMAIN:
		return SNMP_ERR_INCONSISTENTNAME;
		break;
	case SA_ERR_HPI_INVALID_RESOURCE:
		return SNMP_ERR_INCONSISTENTNAME;
		break;
	case SA_ERR_HPI_INVALID_REQUEST:
		return SNMP_ERR_BADVALUE;
		break;
	case SA_ERR_HPI_ENTITY_NOT_PRESENT:
		return SNMP_ERR_RESOURCEUNAVAILABLE;
		break;
	case SA_ERR_HPI_READ_ONLY:
		return SNMP_ERR_READONLY;
		break;
	case SA_ERR_HPI_CAPABILITY:
		return SNMP_ERR_NOACCESS;
		break;
	case SA_ERR_HPI_UNKNOWN:
		return SNMP_ERR_GENERR;
		break;
	default:
		return SNMP_ERR_GENERR;
		break;
	}
}


/**************************************************/
/*** BEGIN: ***************************************/
/*** Hash Table Used for generating and         ***/
/*** tracking unique indices when required      ***/
/**************************************************/
/**************************************************/
#define HASH_FILE "session_info.c"
/* for hash table usage */
guint domain_resource_pair_hash(gconstpointer key);
gboolean domain_resource_pair_equal(gconstpointer a, gconstpointer b);


/*
 * oh_entity_path_hash: used by g_hash_table_new() 
 * in oh_uid_initialize(). See glib library for
 * further details.
 */
guint domain_resource_pair_hash(gconstpointer key)
{
	const char *p = key;
	guint h = *p;

	int i;

	int dr_pair_len;

	dr_pair_len = sizeof(SaHpiDomainIdResourceIdArrayT);

	p += 1;

	for ( i=0; i < dr_pair_len - 1; i++ ) {
		h = (h * 131) + *p;
		p++;                          
	}

	/* don't change the 1009, its magic */
	return( h % 1009 );

}

/*
 * oh_entity_path_equal: used by g_hash_table_new() 
 * in oh_uid_initialize(). See glib library for
 * further details.
 */
gboolean domain_resource_pair_equal(gconstpointer a, gconstpointer b)
{
	if (!memcmp(a, b, sizeof(SaHpiDomainIdResourceIdArrayT))) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * oh_uid_initialize
 *
 * UID utils initialization routine
 * This functions must be called before any other uid_utils
 * are made. 
 * 
 * Returns: success 0, failure -1.
 **/
SaErrorT domain_resource_pair_initialize(int *initialized, GHashTable **oh_ep_table) 
{
	SaErrorT rval = SA_OK;

	if (!*initialized) {

		/* initialize hash tables */
		*oh_ep_table = g_hash_table_new(domain_resource_pair_hash, 
						domain_resource_pair_equal);

		*initialized = TRUE;

	} else {
		rval = SA_ERR_HPI_ERROR;
	}

	return(rval);

}

/**
 * oh_uid_from_entity_path
 * @ep: value to be removed from used
 *
 * This function returns an unique value to be used as
 * an uid/resourceID base upon a unique entity path specified
 * by @ep.  If the entity path already exists, the already assigned 
 * resource id is returned.   
 * 
 * Returns: 
 **/
DR_XREF *domain_resource_pair_get(SaHpiDomainIdResourceIdArrayT *dr, GHashTable **oh_ep_table) 
{
	gpointer key;
	gpointer value;

	DR_XREF *dr_xref;

	if (!dr) return 0;

	key = dr;

	/* check for presence of EP and */
	/* previously assigned uid      */        
	dr_xref = (DR_XREF *)g_hash_table_lookup (*oh_ep_table, key);        
	if (dr_xref) {
		return dr_xref;
	}

	/* allocate storage for EP cross reference data structure*/
	dr_xref = (DR_XREF *)g_malloc0(sizeof(DR_XREF));
	if (!dr_xref) {
		DEBUGMSGTL ((HASH_FILE, "malloc failed"));
		return NULL;                
	}
	memcpy(&dr_xref->dr_pair, dr, sizeof(SaHpiDomainIdResourceIdArrayT));

	/* entity path based key */   
	key = (gpointer)&dr_xref->dr_pair; 
	value = (gpointer)dr_xref;
	g_hash_table_insert(*oh_ep_table, key, value);

	return dr_xref;
}               

/**
 * oh_uid_lookup
 * @ep: pointer to entity path used to identify resourceID/uid
 *
 * Fetches resourceID/uid based on entity path in @ep.
 *  
 * Returns: success returns resourceID/uid, failure is 0.
 **/
DR_XREF *domain_resoruce_pair_lookup(SaHpiDomainIdResourceIdArrayT *dr, GHashTable **oh_ep_table)
{
	DR_XREF *dr_xref;

	gpointer key;

	if (!dr) return 0;

	key = dr;

	/* check hash table for entry in oh_ep_table */
	dr_xref = (DR_XREF *)g_hash_table_lookup (*oh_ep_table, key);
	if (!dr_xref) {
		DEBUGMSGTL ((HASH_FILE, "error looking up EP to get uid"));
		return NULL;
	}

	return dr_xref;
}
/**************************************************/
/*** END: *****************************************/
/*** Hash Table Used for generating and         ***/
/*** tracking unique indices when required      ***/
/**************************************************/
/**************************************************/

/**************************************************/
/*** BEGIN: ***************************************/
/*** decode_sensor_range_flags		        ***/
/**************************************************/
/**************************************************/
typedef struct  {
	SaHpiSensorRangeFlagsT 	flag;
	const unsigned char* 	str;
} sensor_range_flags;

static sensor_range_flags range_flags[] = {
	{SAHPI_SRF_MIN,"MIN, "},
	{SAHPI_SRF_MAX, "MAX, "},
	{SAHPI_SRF_NORMAL_MIN, "NORMAL_MIN, "},
	{SAHPI_SRF_NORMAL_MAX, "NORMAL_MAX, "},
	{SAHPI_SRF_NOMINAL,"NOMINAL, "}};
#define RANGE_FLAGS_LEN 5

/**
 * 
 * @buffer:
 * @sensor_range_flags:
 * 
 * Returns: 
 */
SaErrorT decode_sensor_range_flags(SaHpiTextBufferT *buffer, 
				   SaHpiSensorRangeFlagsT sensor_range_flags)
{

	int i = 0;
	int len = 0;

	memset(buffer, 0, sizeof(*buffer));

	for (i = 0; i < RANGE_FLAGS_LEN; i++) {

		if ((sensor_range_flags & range_flags[i].flag) == range_flags[i].flag) {

			len = strlen(range_flags[i].str);

			if (len + buffer->DataLength  > SAHPI_MAX_TEXT_BUFFER_LENGTH)
				return SA_ERR_HPI_OUT_OF_SPACE;

			memcpy(buffer->Data + buffer->DataLength,
			       range_flags[i].str,
			       len);

			buffer->DataLength += len;
		}

	}

	return SA_OK;
}



/**
 * 
 * @netsnmp_variable_list:
 * @saHpiSensorThdLowCriticalTable_context:
 * 
 * Checks length of var.string val is correct for data type supported. 
 * 
 * Returns: 
 */
int check_sensor_reading_value(size_t val_len, long type)
{
	switch (type - 1) {                        
	case SAHPI_SENSOR_READING_TYPE_INT64:
		if(val_len <= sizeof(SaHpiInt64T))
			return SNMP_ERR_NOERROR;
		break;
	case SAHPI_SENSOR_READING_TYPE_UINT64:
		if(val_len <= sizeof(SaHpiUint64T))
			return SNMP_ERR_NOERROR;
		break;
	case SAHPI_SENSOR_READING_TYPE_FLOAT64:
		if(val_len <= sizeof(SaHpiFloat64T))
			return SNMP_ERR_NOERROR;
		break;
	case SAHPI_SENSOR_READING_TYPE_BUFFER:
		if(val_len <= (SAHPI_SENSOR_BUFFER_LENGTH * sizeof(SaHpiUint8T)))
			return SNMP_ERR_NOERROR;
		break;
	default:
		return SNMP_ERR_WRONGLENGTH;
	}

	return SNMP_ERR_WRONGLENGTH;
}

/**
 * 
 * @reading:
 * @saHpiCurrentSensorStateValue:
 * 
 * Copies reading into text buffer and returns number of 
 * bytes copied.
 * 
 * Returns: 
 */
int set_sensor_reading_value(SaHpiSensorReadingT *reading, 
			     unsigned char *saHpiCurrentSensorStateValue)
{
	switch (reading->Type) {
	case SAHPI_SENSOR_READING_TYPE_INT64:
		memcpy(saHpiCurrentSensorStateValue, 
		       &reading->Value.SensorInt64, 
		       sizeof(SaHpiInt64T));
		return sizeof(SaHpiInt64T);
		break;
	case SAHPI_SENSOR_READING_TYPE_UINT64:
		memcpy(saHpiCurrentSensorStateValue, 
		       &reading->Value.SensorUint64, 
		       sizeof(SaHpiUint64T));
		return sizeof(SaHpiUint64T);
		break;
	case SAHPI_SENSOR_READING_TYPE_FLOAT64:
		memcpy(saHpiCurrentSensorStateValue, 
		       &reading->Value.SensorFloat64, 
		       sizeof(SaHpiFloat64T));
		return sizeof(SaHpiFloat64T);
		break;
	case SAHPI_SENSOR_READING_TYPE_BUFFER:
		memcpy(saHpiCurrentSensorStateValue, 
		       reading->Value.SensorBuffer, 
		       SAHPI_SENSOR_BUFFER_LENGTH * sizeof(SaHpiUint8T));
		return SAHPI_SENSOR_BUFFER_LENGTH * sizeof(SaHpiUint8T);
		break;
	default:
		return 0;
	}

	return 0;
}

/**
 * 
 * @value:
 * @type:
 * @val:
 * @val_len:
 * 
 * @returns: 
 */
SaErrorT set_sen_thd_value(SaHpiSensorReadingUnionT *value, 
			       SaHpiSensorReadingTypeT type,
			       u_char *val, size_t val_len)
{
	switch (type) {
	case SAHPI_SENSOR_READING_TYPE_INT64:
		if (val_len > sizeof(SaHpiInt64T)) 
			return SA_ERR_HPI_INVALID_DATA;
		memcpy(&value->SensorInt64, val, val_len);
	case SAHPI_SENSOR_READING_TYPE_UINT64:
		if (val_len > sizeof(SaHpiUint64T)) 
			return SA_ERR_HPI_INVALID_DATA;
		memcpy(&value->SensorUint64, val, val_len);
	case SAHPI_SENSOR_READING_TYPE_FLOAT64:
		if (val_len > sizeof(SaHpiFloat64T)) 
			return SA_ERR_HPI_INVALID_DATA;
		memcpy(&value->SensorFloat64, val, val_len);
	case SAHPI_SENSOR_READING_TYPE_BUFFER:
		if (val_len > SAHPI_SENSOR_BUFFER_LENGTH * sizeof(SaHpiUint8T)) 
			return SA_ERR_HPI_INVALID_DATA;
		memcpy(&value->SensorBuffer, val, val_len);
	default:
		return SA_ERR_HPI_UNKNOWN;
	}

	return SA_OK;

}



/**
 * 
 * @buffer
 * 
 * Changes '|' to a ','
 */
void oh_decode_char(SaHpiTextBufferT *buffer)
{
	int i = 0;

	for (i = 0; i < buffer->DataLength; i++) {
		if ( buffer->Data[i] == '|' )
			buffer->Data[i] = ',';
	}
}

/**
 * 
 * @buffer
 * 
 * Changes ',' to a '|'
 */
void oh_encode_char(SaHpiTextBufferT *buffer)
{
	int i = 0;

	for (i = 0; i < buffer->DataLength; i++) {
		if ( buffer->Data[i] == ',' )
			buffer->Data[i] = '|';
	}
}

typedef struct {
    SaHpiWatchdogExpFlagsT exp_flag;
    unsigned char *str;
} watchdog_exp_flags;

static watchdog_exp_flags watchdog_string[] = {
  {SAHPI_WATCHDOG_EXP_BIOS_FRB2, "BIOS_FRB2"},
  {SAHPI_WATCHDOG_EXP_BIOS_POST, "BIOS_POST"},
  {SAHPI_WATCHDOG_EXP_OS_LOAD,   "OS_LOAD"},
  {SAHPI_WATCHDOG_EXP_SMS_OS,    "SMS_OS"},
  {SAHPI_WATCHDOG_EXP_OEM,       "OEM"}
};

#define MAX_EXP_FLAGS_STRINGS 5

SaErrorT oh_decode_exp_flags(SaHpiWatchdogExpFlagsT exp_flags,
			     SaHpiTextBufferT *buffer)
{
	int i, found;
	SaErrorT err;
	SaHpiTextBufferT working;

	err = oh_init_textbuffer(&working);
	if (err != SA_OK) 
                return(err);

	found = 0;
	/* Look for category's event states */
	for (i=0; i < MAX_EXP_FLAGS_STRINGS; i++) {
                if ((watchdog_string[i].exp_flag & exp_flags) == watchdog_string[i].exp_flag) {
				found++;
				err = oh_append_textbuffer(&working, (char *)watchdog_string[i].str);
				if (err != SA_OK) 
                                        return(err);
				err = oh_append_textbuffer(&working, OH_ENCODE_DELIMITER);
				if (err != SA_OK) 
                                        return(err);
                }
	}

	/* Remove last delimiter */
	if (found) {
		for (i=0; i < OH_ENCODE_DELIMITER_LENGTH + 1; i++) {
			working.Data[working.DataLength - i] = 0x00;
		}
		working.DataLength = working.DataLength - OH_ENCODE_DELIMITER_LENGTH;
	}

	err = oh_copy_textbuffer(buffer, &working);

        oh_decode_char(buffer);

	return(SA_OK);
}

int oh_encode_exp_flags(SaHpiTextBufferT *buffer, SaHpiWatchdogExpFlagsT *exp_flags)
{
        int i,j;

        int rv = SNMP_ERR_BADVALUE;

        gchar *gstr = NULL;
	gchar **eventdefs = NULL;

	if (!buffer || !exp_flags || 
            buffer->Data == NULL || buffer->Data[0] == '\0') {
                DEBUGMSGTL ((AGENT, "oh_encode_exp_flags: SA_ERR_HPI_INVALID_PARAMS"));
		return SA_ERR_HPI_INVALID_PARAMS;
	}

        oh_encode_char(buffer);

	/* Split out event definitions */
	if (buffer->DataLength < SAHPI_MAX_TEXT_BUFFER_LENGTH) {
		buffer->Data[buffer->DataLength] = '\0';
	}
	gstr = g_strstrip(g_strndup((gchar *)buffer->Data, SAHPI_MAX_TEXT_BUFFER_LENGTH));
	if (gstr == NULL || gstr[0] == '\0') {
                DEBUGMSGTL ((AGENT, "g_strstrip failed"));
		return SA_ERR_HPI_INTERNAL_ERROR;
	}

	eventdefs = g_strsplit(gstr, OH_ENCODE_DELIMITER_CHAR, -1);
	if (eventdefs == NULL) {
                DEBUGMSGTL ((AGENT, "No event definitions"));
		return SA_ERR_HPI_INVALID_PARAMS;
	}

	for (i=0; eventdefs[i] != NULL && eventdefs[i][0] != '\0'; i++) {
		eventdefs[i] = g_strstrip(eventdefs[i]);

		for (j=0; j < MAX_EXP_FLAGS_STRINGS; j++) {
			if (strcasecmp(eventdefs[i], (char *)watchdog_string[j].str) == 0) {
                                *exp_flags += watchdog_string[j].exp_flag;
                                rv = SNMP_ERR_NOERROR;
			}
		}
	}
	
        g_free(gstr);
        g_strfreev(eventdefs);

        return rv;
}
