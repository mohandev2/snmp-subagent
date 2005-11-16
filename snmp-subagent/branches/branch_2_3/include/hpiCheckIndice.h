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
 *
 */
#include <saHpiEventTable.h>

/**************************/
/* saHpiAnnouncementTable */    
/**************************/
int saHpiDomainId_check_index(long val);
int saHpiDomainAlarmId_check_index(long val);

/**************************/
/* saHpiResourceTable */    
/**************************/
int saHpiResourceEntryId_check_index(long val);
int saHpiResourceIsHistorical_check_index(long val);

/**************************/
/* saHpiCtrlDigitalTable  */    
/**************************/
int saHpiCtrlDigitalEntryId_check_index(long val);

/**************************/
/* saHpiCtrlDiscreteTable  */    
/**************************/
int saHpiCtrlDiscreteEntryId_check_index(long val);

/**************************/
/* saHpiCtrlAnalogTable  */    
/**************************/
int saHpiCtrlAnalogEntryId_check_index(long val);

/**************************/
/* saHpiCtrlStreamTable  */    
/**************************/
int saHpiCtrlStreamEntryId_check_index(long val);

/**************************/
/* saHpiCtrlTextTable  */    
/**************************/
int saHpiCtrlTextEntryId_check_index(long val);

/**************************/
/* saHpiCtrlOemTable  */    
/**************************/
int saHpiCtrlOemEntryId_check_index(long val);

/**************************/
/* saHpiRdrTable  */    
/**************************/
int saHpiRdrType_check_index(long val);

/**************************/
/* saHpiSensorTable  */    
/**************************/
int saHpiSensorNum_check_index(long val);

/**************************/
/* saHpiAnnunciatorTable  */    
/**************************/
int saHpiAnnunciatorNum_check_index(long val);

/**************************/
/* saHpiInventoryTable  */    
/**************************/
int saHpiInventoryId_check_index(long val);

/**************************/
/* saHpiAreaTable */    
/**************************/
int saHpiAreaId_check_index(long val);

/**************************/
/* saHpiFeildTable  */    
/**************************/
int saHpiFieldId_check_index(long val);

/**************************/
/* saHpiEeventTable  */    
/**************************/
int saHpiEventRowPointer_check_index(saHpiEventTable_context * ctx);

/**************************/
/* saHpiResourceEventTable */    
/**************************/
int saHpiResourceEventEntryId_check_index(long val);

/**************************/
/* saHpiDomainEventTable */    
/**************************/
int saHpiDomainEventEntryId_check_index(long val);

/**************************/
/* saHpiSensorEventTable */    
/**************************/
int saHpiSensorEventEntryId_check_index(long val);

/**************************/
/* saHpiHotSwapEventTable */    
/**************************/
int saHpiHotSwapEventEntryId_check_index(long val);

/**************************/
/* saHpiWatchdogEventTable */    
/**************************/
int saHpiWatchdogEventEntryId_check_index(long val);

/**************************/
/* saHpiSoftwareEventTable */    
/**************************/
int saHpiSoftwareEventEntryId_check_index(long val);

/**************************/
/* saHpiUserEventTable */
/**************************/
int saHpiUserEventEntryId_check_index(long val);

/**************************/
/* saHpiAnnouncementTable */
/**************************/
int saHpiAnnouncementEntryId_check_index(long val);

/**************************/
/* saHpiEventLogTable */
/**************************/
int saHpiEventLogIndex_check_index(long val);

/*******************************/
/* saHpiResourceEventLogTable */
/******************************/
int saHpiResourceEventLogEntryId_check_index(long val);

/*******************************/
/* saHpiSensorEnableChangeEventLogTable */
/******************************/
int saHpiSensorEnableChangeEventEntryId_check_index(long val);

/*******************************/
/* saHpiDomainAlarmTable */
/******************************/
int saHpiDomainAlarmSeverity_check_index(long val);

/*******************************/
/* saHpiOemEventTable */
/******************************/
int saHpiOemEventEntryId_check_index(long val);

/**************************************/
/**************************************/
/**************************************/
/**************************************/

/**************************/
/* saHpiDomainAlarmTable  */    
/**************************/
int saHpiDomainAlarmId_check_index(long val);

/**************************/
/* saHpiEventDomainTable  */    
/**************************/
int saHpiEventSeverity_check_index(long val);
int saHpiEventHistorical_check_index(long val);
int saHpiDomainEventTimestamp_check_index(netsnmp_variable_list *var_saHpiDomainEventTimestamp);

/**************************/
/* saHpiEventTable  */    
/**************************/
int saHpiEvent_check_index(netsnmp_variable_list *var_saHpiEventSaHpiTime);
int saHpiEventQueueStatus_check_index(netsnmp_variable_list *var_saHpiEventSaHpiTime);
int saHpiEventSaHpiTime_check_index(netsnmp_variable_list *var_saHpiEventSaHpiTime);

/***************************/
/* saHpiHotSwapEventTable  */    
/***************************/
int saHpiHotSwapEventTimestamp_check_index(netsnmp_variable_list *var_saHpiHotSwapEventTimestamp);

/**************************/
/* saHpiOemEventTable  */    
/**************************/
int saHpiOemEventTimestamp_check_index(netsnmp_variable_list *var_saHpiOemEventTimestamp);

/**************************/
/* saHpiRdrTable  */    
/**************************/
int saHpiRdrEntryId_check_index(long val);

/**************************/
/* saHpiResourceEventTable  */    
/**************************/
int saHpiResourceEventTimestamp_check_index( netsnmp_variable_list *var_saHpiResourceEventTimestamp);

/**************************/
/* saHpiResourceTable  */    
/**************************/
int saHpiResourceId_check_index(long val);
int saHpiEntryId_check_index(long val);

/********************************/
/* saHpiWatchdogTable  		*/    
/********************************/
int saHpiWatchdogNum_check_index(long val);





	       


