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
 *   Daniel de Araujo <ddearauj@us.ibm.com>
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
/* saHpiCtrlDigitalTable  */    
/**************************/
int saHpiCtrlDigitalEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiCtrlDiscreteTable  */    
/**************************/
int saHpiCtrlDiscreteEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiCtrlAnalogTable  */    
/**************************/
int saHpiCtrlAnalogEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiCtrlStreamTable  */    
/**************************/
int saHpiCtrlStreamEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiCtrlTextTable  */    
/**************************/
int saHpiCtrlTextEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiCtrlOemTable  */    
/**************************/
int saHpiCtrlOemEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiAnnunciatorTable  */    
/**************************/
int saHpiSensorNum_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiSensorTable  */    
/**************************/
int saHpiAnnunciatorNum_check_index(long val)
{
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
/* saHpiAreaTable */    
/**************************/
int saHpiAreaId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiFeildTable  */    
/**************************/
int saHpiFieldId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiEeventTable  */    
/**************************/
/*int saHpiEventRowPointer_check_index(saHpiEventTable_context * ctx)
{
	return 0;
}
*/
/**************************/
/* saHpiResourceEventTable */    
/**************************/
int saHpiResourceEventEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiDomainEventTable */    
/**************************/
int saHpiDomainEventEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiSensorEventTable */    
/**************************/
int saHpiSensorEventEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiHotSwapEventTable */    
/**************************/
int saHpiHotSwapEventEntryId_check_index(long val)
{
	return 0;
}

/**************************/
/* saHpiWatchdogEventTable */    
/**************************/
int saHpiWatchdogEventEntryId_check_index(long val)
{
        return 0;
}

/**************************/
/* saHpiSoftwareEventTable */    
/**************************/
int saHpiSoftwareEventEntryId_check_index(long val)	
{
        return 0;
}

/**************************/
/* saHpiUserEventTable */
/**************************/
int saHpiUserEventEntryId_check_index(long val)
{
        return 0;
}

/**************************/
/* saHpiAnnouncementTable */
/**************************/
int saHpiAnnouncementEntryId_check_index(long val)
{
        return 0;
}

/**************************/
/* saHpiEventLogTable */
/**************************/
int saHpiEventLogIndex_check_index(long val)
{
        return 0;
}

/*******************************/
/* saHpiResourceEventLogTable */
/******************************/
int saHpiResourceEventLogEntryId_check_index(long val)
{
        return 0;
}

/*******************************/
/* saHpiSensorEnableChangeEventLogTable */
/******************************/
int saHpiSensorEnableChangeEventEntryId_check_index(long val)
{
        return 0;
}

/*******************************/
/* saHpiDomainAlarmTable */
/******************************/
int saHpiDomainAlarmSeverity_check_index(long val)
{
        return 0;
}

/*******************************/
/* saHpiOemEventTable */
/******************************/
int saHpiOemEventEntryId_check_index(long val)
{
        return 0;
}

/**************************/
/* saHpiEeventTable  */    
/**************************/
int saHpiEventRowPointer_check_index(saHpiEventTable_context * ctx)
{
	return 0;
}
/*******************************************/
/*******************************************/
/*******************************************/
/*******************************************/



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



/***************************/
/* saHpiHotSwapEventTable  */    
/***************************/
int saHpiHotSwapEventTimestamp_check_index(netsnmp_variable_list *var_saHpiHotSwapEventTimestamp)
{
	snmp_log(LOG_ERR, "saHpiHotSwapEventTimestamp_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
	return 0;

}


/**************************/
/* saHpiOemEventTable  */    
/**************************/
int saHpiOemEventTimestamp_check_index(netsnmp_variable_list *var_saHpiOemEventTimestamp)
{
	snmp_log(LOG_ERR, "saHpiOemEventTimestamp_check_index OCTET_STR: NEED TO INVESTIGATE A BETTER CHECK!\n" );
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
/* saHpiWatchdogTable  */    
/********************************/
int saHpiWatchdogNum_check_index(long val)
{
	return 0;
}

#endif /* _HPI_CHECK_INDICE_ */




