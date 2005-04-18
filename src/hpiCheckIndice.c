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
 *   David Judkovics <djudkovi@us.ibm.com>
 *
 *
 */
#ifndef _HPI_CHECK_INDICE_
#define  _HPI_CHECK_INDICE_

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <net-snmp/library/snmp_assert.h>


#include "hpiCheckIndice.h"

/**************************/
/* saHpiDomainInfoTable */    
/**************************/
int saHpiDomainId_check_index(long val) 
{
	return 0;
}

/**************************/
/* saHpiResourceTable */    
/**************************/
int saHpiResourceEntryId_check_index(long val) 
{
	return 0;
}
int saHpiResourceIsHistorical_check_index(long val) 
{
	return 0;
}


/**************************/
/* saHpiRrdTable */    
/**************************/
int saHpiRdrEntryId_check_index(long val)
{
	return 0;
}


/**************************/
/* saHpiAnnunciatorTable */    
/**************************/
int saHpiAnnunciatorNum_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiAreaTable */    
/**************************/
int saHpiAreaId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiCtrlTable	 */    
/**************************/
int saHpiCtrlNum_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiDomainAlarmTable  */    
/**************************/
int saHpiDomainAlarmId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiEventDomainTable  */    
/**************************/
int saHpiEventSeverity_check_index(long val)
{
	return 0;
}

int saHpiEventHistorical_check_index(long val)
{
	return 0;
}

int saHpiDomainEventTimestamp_check_index(netsnmp_variable_list *var_saHpiDomainEventTimestamp)
{
	snmp_log(LOG_ERR, "saHpiDomainEventTimestamp_check_index OCTET_STR:NEED TO INVESTIGATE A BETTER CHECK!\n" );

	return 0;
}

/**************************/
/* saHpiEventTable  */    
/**************************/
int saHpiEvent_check_index(netsnmp_variable_list *var_saHpiEventSaHpiTime)
{
	snmp_log(LOG_ERR, "saHpiEvent_check_index ASN_OBJECT_ID: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;
}

int saHpiEventQueueStatus_check_index(netsnmp_variable_list *var_saHpiEventSaHpiTime)
{
	return 0;
}

int saHpiEventSaHpiTime_check_index(netsnmp_variable_list *var_saHpiEventSaHpiTime)
{
	snmp_log(LOG_ERR, "saHpiEventSaHpiTime_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;
}


/**************************/
/* saHpiFeildTable  */    
/**************************/
int saHpiFieldId_check_index(long val)
{
	return 0;
}

/***************************/
/* saHpiHotSwapEventTable  */    
/***************************/
int saHpiHotSwapEventTimestamp_check_index(netsnmp_variable_list *var_saHpiHotSwapEventTimestamp)
{
	snmp_log(LOG_ERR, "saHpiHotSwapEventTimestamp_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;

}

/**************************/
/* saHpiInventoryTable  */    
/**************************/
int saHpiInventoryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiOEMEventTable  */    
/**************************/
int saHpiOEMEventTimestamp_check_index(netsnmp_variable_list *var_saHpiOEMEventTimestamp)
{
	snmp_log(LOG_ERR, "saHpiOEMEventTimestamp_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;

}

/**************************/
/* saHpiRdrTable  */    
/**************************/
int saHpiRdrType_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiResourceEventTable  */    
/**************************/
int saHpiResourceEventTimestamp_check_index( netsnmp_variable_list *var_saHpiResourceEventTimestamp)
{
	snmp_log(LOG_ERR, "saHpiResourceEventTimestamp_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;

}

/**************************/
/* saHpiResourceTable  */    
/**************************/
int saHpiResourceId_check_index(long val)
{
	return 0;
}

int saHpiEntryId_check_index(long val)
{
	return 0;
}
  
/********************************/
/* saHpiEnableChangeEventTable  */    
/********************************/
int saHpiTimeString_check_index( netsnmp_variable_list *var_saHpiTimeString_check_index)
{
	snmp_log(LOG_ERR, "saHpiSensorEnableChangeEventTimestamp_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;

}

/********************************/
/* saHpiSensorTable  */    
/********************************/
int saHpiSensorNum_check_index(long val)
{
	return 0;
}

/********************************/
/* saHpiWatchdogTable  */    
/********************************/
int saHpiWatchdogNum_check_index(long val)
{
	return 0;
}

#endif /* _HPI_CHECK_INDICE_ */




