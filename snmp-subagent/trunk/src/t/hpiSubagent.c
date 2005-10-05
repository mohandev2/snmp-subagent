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
 * $Id$
 *					  
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <signal.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <hpiSubagent.h>
#include <hpiEventThread.h>

#include <SaHpi.h> 
#include <oh_utils.h>

#include "/home/dearaujo/openhpi/include/oh_event.h"
#include "/home/dearaujo/openhpi/include/oh_handler.h"
#include "/home/dearaujo/openhpi/plugins/simulator/sim_injector.h"
#include "/home/dearaujo/openhpi/plugins/simulator/sim_resources.h"

#include <hpiCheckIndice.h>
#include <session_info.h>

#include <saHpiDomainInfoTable.h>
#include <saHpiDomainAlarmTable.h>
#include <saHpiDomainReferenceTable.h>

#include <saHpiResourceTable.h>
#include <saHpiRdrTable.h>

#include <saHpiAnnunciatorTable.h>

#include <saHpiInventoryTable.h>
#include <saHpiFieldTable.h>
#include <saHpiAreaTable.h>

#include <saHpiSensorTable.h>
#include <saHpiCurrentSensorStateTable.h>
#include <saHpiSensorReadingMaxTable.h>
#include <saHpiSensorReadingMinTable.h>
#include <saHpiSensorReadingNominalTable.h>
#include <saHpiSensorReadingNormalMaxTable.h>
#include <saHpiSensorReadingNormalMinTable.h>
#include <saHpiSensorThdLowCriticalTable.h>
#include <saHpiSensorThdLowMajorTable.h>
#include <saHpiSensorThdLowMinorTable.h>
#include <saHpiSensorThdNegHysteresisTable.h>
#include <saHpiSensorThdPosHysteresisTable.h>
#include <saHpiSensorThdUpCriticalTable.h>
#include <saHpiSensorThdUpMajorTable.h>
#include <saHpiSensorThdUpMinorTable.h>

#include <saHpiCtrlAnalogTable.h>
#include <saHpiCtrlDigitalTable.h>
#include <saHpiCtrlDiscreteTable.h>
#include <saHpiCtrlOemTable.h>
#include <saHpiCtrlStreamTable.h>
#include <saHpiCtrlTextTable.h>

#include <saHpiWatchdogTable.h>
#include <saHpiHotSwapTable.h>
#include <saHpiAutoInsertTimeoutTable.h>

#include <saHpiEventTable.h>
#include <saHpiResourceEventTable.h>
#include <saHpiDomainEventTable.h>
#include <saHpiSensorEventTable.h>
#include <saHpiSensorEnableChangeEventTable.h>
#include <saHpiHotSwapEventTable.h>
#include <saHpiWatchdogEventTable.h>
#include <saHpiSoftwareEventTable.h>
#include <saHpiOEMEventTable.h>
#include <saHpiUserEventTable.h>
#include <saHpiAnnouncementTable.h>

#include <saHpiEventLogInfoTable.h>
#include <saHpiEventLogTable.h>
#include <saHpiResourceEventLogTable.h>
#include <saHpiDomainEventLogTable.h>
#include <saHpiSensorEventLogTable.h>
#include <saHpiSensorEnableChangeEventLogTable.h>
#include <saHpiHotSwapEventLogTable.h>
#include <saHpiWatchdogEventLogTable.h>
#include <saHpiSoftwareEventLogTable.h>
#include <saHpiOEMEventLogTable.h>
#include <saHpiUserEventLogTable.h>
#include <saHpiAnnouncementEventLogTable.h>

/*
 * OIDs for subagent
 */
//  .iso.org.dod.internet.private.enterprises.saforum.experimental.hpiE.openhpiE
/*
#define hpi0101_OID 			1,3,6,1,4,1,18568,2,1,1

#define hpiAdministration_OID 	hpi0101_OID,1

#define hpiDomain_OID 			hpi0101_OID,2
#define hpiHotswap				hpiDomain_OID,11

#define hpiEvents_OID 			hpi0101_OID,3
#define hpiEvents_events_OID 	hpiEvents_OID,1
#define hpiEvents_eventlogs_OID	hpiEvents_OID,2

#define hpiResources_OID 		hpi0101_OID,4
#define hpiControl_OID 			hpiResources_OID,7
#define hpiInventory_OID 		hpiResources_OID,8
#define hpiSensor_OID 			hpiResources_OID,9

#define hpiNotifications_OID 	hpi0101_OID,5
*/
// SnmpTrapOID.0
/* 
#define snmptrap_oid 1,3,6,1,6,3,1,1,4,1,0
*/

/*
 * Internal data for the sub-agent.
 */
static int keep_running;
static int session_avail = AGENT_FALSE;
static SaErrorT err;

static const char *version =
  "$Id$";


/*
 * Configuration options. Changed by config file.
 */

#define REDISCOVER_COUNT_MAX 10;

int send_traps = AGENT_FALSE;
static int send_traps_on_startup = AGENT_FALSE;

static int rediscover_count = 0;
int MAX_EVENT_ENTRIES = 512; // Max EVENT rows. 

//Use syslog 
static int do_syslog = AGENT_TRUE;
static int do_fork = AGENT_FALSE;


/*
 * Internal prototypes
 */
static void usage(char *applName);
static RETSIGTYPE stop_server (int a);

static RETSIGTYPE stop_server (int a)
{
        //DMJ TODO  Really need to signal event thread to break out first
        set_run_threaded(FALSE);
        keep_running = 0;
}

void hpiSubagent_parse_config_traps (const char *token, char *cptr)
{
  int x = -1;
  char buf[BUFSIZ];

  if (!strncasecmp (cptr, "on", 2) ||
      !strncasecmp (cptr, "yes", 3) || !strncasecmp (cptr, "true", 4))
    {
      x = AGENT_TRUE;
      snmp_log (LOG_INFO, "Sending EVENTS during startup.\n");
    }
  else if (!strncasecmp (cptr, "off", 3) ||
	   !strncasecmp (cptr, "no", 2) || !strncasecmp (cptr, "false", 5))
    {
      x = AGENT_FALSE;
      snmp_log (LOG_INFO, "Not sending events during startup.\n");
    }

  if ((x != AGENT_TRUE) && (x != AGENT_FALSE))
    {
	  snprintf(buf, 3, "hpiSubagent: hpiSubagent_parse_config_traps, '%s' unrecognized", cptr);
      config_perror (buf);
    }
  else
    {

      send_traps_on_startup = x;
    }
}

void hpiSubagent_parse_config_max_event (const char *token, char *cptr)
{
  int x = atoi (cptr);
  char buf[BUFSIZ];

  if (x < -1)
    {

	  snprintf(buf, 3, "hpiSubagent: hpiSubagent_parse_config_max_event, '%s' unrecognized", cptr);
      config_perror (buf);
    }
  else
    {
      snmp_log (LOG_INFO, "Max Event rows %d.\n", x);
      MAX_EVENT_ENTRIES = x;
    }
}

static void usage(char *applName)
{
  printf("Usage: %s [OPTION]...\n", applName);
  printf("\n");
  printf("Options:\n");
  printf("  -d            enables debug mode\n");
  printf("  -f            enables forking\n");
  printf("  -s            disables logging via syslog facility\n");
  printf("  -C            do not read default SNMP configuration files\n");
  printf("  -x ADDRESS    use ADDRESS as AgentX address\n");  
  printf("  -h            print this help and exit\n");

  return;
}

int
main (int argc, char **argv)
{
	
	  	int agentx_subagent = AGENT_TRUE;
	  	int c;
	  	int rc = 0;
        	  
	  	SaErrorT 	rv = SA_OK;
		SaHpiVersionT	hpiVer;
		SaHpiSessionIdT sessionid;
		
		
		
	  	pid_t child;
		
		/* for simulator */
		struct oh_handler_state *state = NULL;
		struct oh_event *event = (struct oh_event *)g_malloc0(sizeof(struct oh_event));
		struct oh_event *event2= (struct oh_event *)g_malloc0(sizeof(struct oh_event));
		struct oh_event *event3= (struct oh_event *)g_malloc0(sizeof(struct oh_event));		
		struct oh_event *event4= (struct oh_event *)g_malloc0(sizeof(struct oh_event));
		struct oh_event *event5= (struct oh_event *)g_malloc0(sizeof(struct oh_event));	
		struct oh_event *event6= (struct oh_event *)g_malloc0(sizeof(struct oh_event));	
		struct oh_event *event7= (struct oh_event *)g_malloc0(sizeof(struct oh_event));	
		struct oh_event *event8= (struct oh_event *)g_malloc0(sizeof(struct oh_event));			
							
		SaErrorT rc1;
	  	char OEMString[] = "MY OEM EVENT";
	  	char SWString[] = "MY SW EVENT";			  	
	  	/* change this if you want to be a SNMP master agent */
	  	
	  	debug_register_tokens (AGENT);
                snmp_enable_stderrlog ();
                snmp_set_do_debugging (1);

	  	while ((c = getopt (argc, argv, "fdsCx:h?")) != EOF) {
	    switch (c) {
	   	case 'f':
			do_fork = AGENT_TRUE;
		   	break;
	
	    case 'd':
			debug_register_tokens (AGENT);
			snmp_enable_stderrlog ();
			snmp_set_do_debugging (1);
	      	break;
	
	  	case 's':
			do_syslog = AGENT_FALSE;
	      	break;
	
	   	case 'C':
			netsnmp_ds_set_boolean(NETSNMP_DS_LIBRARY_ID,
				       NETSNMP_DS_LIB_DONT_READ_CONFIGS,
				       1);
	     	break;
	
	  	case 'x':
			netsnmp_ds_set_string(NETSNMP_DS_APPLICATION_ID,
				      NETSNMP_DS_AGENT_X_SOCKET,
				      optarg);
	      	break;
	
	 	case 'h':
	    default:
			usage(argv[0]);
			exit(1);
	      	break;
	    }
	  }
	
	  if (do_syslog == AGENT_TRUE) {
	      snmp_enable_calllog ();
	      snmp_enable_syslog_ident (AGENT, LOG_DAEMON);
	  }
	  snmp_log (LOG_INFO, "Starting %s\n", version);
	  /* we're an agentx subagent? */
	  if (agentx_subagent) {
	      /* make us a agentx client. */
	      rc = netsnmp_ds_set_boolean (NETSNMP_DS_APPLICATION_ID,
					   NETSNMP_DS_AGENT_ROLE, 1);
	  }
	
	  /* initialize the agent library */
	  rc = init_agent (AGENT);
	  if (rc != 0) {
	      snmp_log (LOG_ERR, "Could not initialize connection to SNMP daemon. \n"
			"Perhaps you are running %s as non-root?\n", argv[0]);
	      exit (rc);
	  }

	  /* Read configuration information here, before we initialize */
	
	  snmpd_register_config_handler (TRAPS_TOKEN,
					 hpiSubagent_parse_config_traps,
					 NULL,
					 "hpiSubagent on/off switch for sending events upon startup");
	
	  snmpd_register_config_handler (MAX_EVENT_TOKEN,
					 hpiSubagent_parse_config_max_event,
					 NULL,
					 "hpiSubagent MAX number of rows for Events.");
					 
	init_snmp (AGENT); 	
	
	/* 
	 * Initialize HPI library
	 */
	hpiVer = saHpiVersionGet();
	DEBUGMSGTL ((AGENT, "Hpi Version %d Implemented.\n", hpiVer));   	 

	rv = saHpiSessionOpen( SAHPI_UNSPECIFIED_DOMAIN_ID, &sessionid, NULL );
	if (rv != SA_OK) {
		DEBUGMSGTL ((AGENT, "saHpiSessionOpen Error: returns %s\n",
			oh_lookup_error(rv)));
		exit(-1);
	}
   	DEBUGMSGTL ((AGENT, "saHpiSessionOpen returns with SessionId %d\n", 
   		sessionid));  

        /* store session numbers */
   	store_session_info(sessionid, SAHPI_UNSPECIFIED_DOMAIN_ID);	
   				
	/* subscribe all sessions/events */
        subcsribe_all_sessions();

	/* Resource discovery */
	rv = saHpiDiscover(sessionid);
	
	if (rv != SA_OK) {
		DEBUGMSGTL ((AGENT, "saHpiDiscover Error: returns %s\n",oh_lookup_error(rv)));
		exit(-1);
	}
	DEBUGMSGTL ((AGENT, "saHpiDiscover Success!\n"));	

	/* Initialize subagent tables */		
	init_saHpiDomainInfoTable(); 
	init_saHpiDomainAlarmTable();
	init_saHpiDomainReferenceTable();
	
	init_saHpiResourceTable();
	init_saHpiRdrTable();
	init_saHpiCtrlDigitalTable();
	init_saHpiCtrlDiscreteTable();
	init_saHpiCtrlAnalogTable();
	init_saHpiCtrlStreamTable();
	init_saHpiCtrlTextTable();
	init_saHpiCtrlOemTable();
	init_saHpiSensorTable();
	init_saHpiCurrentSensorStateTable();
	init_saHpiSensorReadingMaxTable();
	init_saHpiSensorReadingMinTable();
	init_saHpiSensorReadingNominalTable();
	init_saHpiSensorReadingNormalMaxTable();
	init_saHpiSensorReadingNormalMinTable();
	init_saHpiSensorThdLowCriticalTable();
	init_saHpiSensorThdLowMajorTable();
	init_saHpiSensorThdLowMinorTable();
	init_saHpiSensorThdUpCriticalTable();
	init_saHpiSensorThdUpMajorTable();
	init_saHpiSensorThdUpMinorTable();
	init_saHpiSensorThdPosHysteresisTable();
	init_saHpiSensorThdNegHysteresisTable();
	init_saHpiInventoryTable();
	init_saHpiWatchdogTable();
	init_saHpiAnnunciatorTable();
	init_saHpiAreaTable();
	init_saHpiFieldTable();

	init_saHpiEventTable();
	init_saHpiResourceEventTable();
	init_saHpiDomainEventTable();
	init_saHpiSensorEventTable();
	init_saHpiOEMEventTable();
	init_saHpiHotSwapEventTable();
	init_saHpiWatchdogEventTable();		
	init_saHpiSoftwareEventTable();
	init_saHpiSensorEnableChangeEventTable();
	init_saHpiUserEventTable();

	init_saHpiEventLogInfoTable();
	init_saHpiEventLogTable();
	init_saHpiResourceEventLogTable();
	init_saHpiSensorEventLogTable();
	
	init_saHpiHotSwapEventLogTable();
	init_saHpiWatchdogEventLogTable();
	init_saHpiSoftwareEventLogTable();
	init_saHpiOEMEventLogTable();
	init_saHpiUserEventLogTable();
	init_saHpiSensorEnableChangeEventLogTable();
	init_saHpiDomainEventLogTable();
	
	init_saHpiHotSwapTable();
	init_saHpiAutoInsertTimeoutTable();
	init_saHpiAnnouncementTable();
/*	init_saHpiAnnouncementEventLogTable();	*/


	if (send_traps_on_startup == AGENT_TRUE)
		send_traps = AGENT_TRUE;
	/* after initialization populate tables */
	populate_saHpiDomainInfoTable(sessionid);

	populate_saHpiDomainAlarmTable(sessionid);

	poplulate_saHpiDomainReferenceTable(sessionid);	

	populate_saHpiResourceTable(sessionid);
	    /* populate_saHpiResourceTable() calls:
	     *     populate_saHpiRdrTable(); calls:
	     *         populate_saHpiCtrlDigitalTable();		
	     *	       populate_saHpiCtrlDiscreteTable();		
	     *	       populate_saHpiCtrlAnalogTable();		
	     *	       populate_saHpiCtrlStreamTable();		
	     *	       populate_saHpiCtrlTextTable();		
	     *	       populate_saHpiCtrlOemTable();		
	     *	       populate_saHpiSensorTable();		
	     *	           populate_saHpiSesnorReadingMaxTable();		
	     *	           populate_saHpiSesnorReadingMinTable();		
	     *	           populate_saHpiSesnorReadingNominalTable();		
	     *	           populate_saHpiSesnorReadingNormalMaxTable();		
	     *	           populate_saHpiSesnorReadingNormalMinTable();		
	     *	           populate_saHpiSensorThdLowCriticalTable();		
	     *	           populate_saHpiSensorThdLowMajorTable();		
	     *	           populate_saHpiSensorThdLowMinorTable();		
	     *	           populate_saHpiSensorThdUpCriticalTable();		
	     *	           populate_saHpiSensorThdUpMajorTable();		
	     *	           populate_saHpiSensorThdUpMinorTable();		
	     *	           populate_saHpiSensorThdPosHysteresisTable();		
	     *	           populate_saHpiSensorThdNegHysteresisTable();		
	     *	       populate_saHpiCurrentSensorStateTable();		
	     *	       populate_saHpiInventoyTable();		
	     *	       populate_saHpiWatchdogTable();		
	     *	       populate_saHpiAnnunciatorTable();		
	     *	       populate_saHpiAreaTable();		
	     *	           populate_saHpiFieldTable();
	     *         populate_saHpiHotSwapTable();
	     */

	populate_saHpiEventTable(sessionid);
            /* populate_saHpiResourceEventTable();
	     * populate_saHpiDomainEventTable();
	     * populate_saHpiSensorEventTable();
	     * populate_saHpiOemEventTable();
	     * populate_saHpiHotSwapEventTable();
	     * populate_saHpiWatchdogEventTable();
	     * populate_saHpiSoftwareEventTable();
	     * populate_saHpiSensorEnableChangeEventTable();
	     * populate_saHpiUserEventTable();
	     */
        populate_saHpiEventLogInfo(sessionid);
        populate_saHpiEventLog (sessionid);
            /*
             * populate_saHpiResourceEventLogTable();
             * populate_saHpiSensorEventLogTable();
	     * populate_saHpiHotSwapEventLogTable();
	     * populate_saHpiWatchdogEventLogTable();
	     * populate_saHpiSoftwareEventLogTable();
	     * populate_saHpiOemEventLogTable();
	     * populate_saHpiUserEventLogTable();
	     * populate_saHpiSensorEnableChangeEventLogTable();
	     * populate_saHpiDomainEventLogTable();	     
             */


        /* Generate Event Here */
		
	DEBUGMSGTL ((AGENT,
        "%%%%%%%% Generating simultor event %%%%%%%%\n"));
	
	state = sim_get_handler_by_name("eventGenerator");
	
	if (!state) {
                DEBUGMSGTL ((AGENT, "%%%%%%%% Couldn't find handler name %%%%%%%%\n"));
	}
	else { // build an event
		
	        event->did = 1; /* domain id for the event */
                event->type = OH_ET_HPI;
                event->u.hpi_event.res = sim_rpt_array[0].rpt;
                event->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event->u.hpi_event.event.EventType = SAHPI_ET_WATCHDOG;
		event->u.hpi_event.event.Timestamp = 0;
		event->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event->u.hpi_event.event.EventDataUnion.WatchdogEvent.WatchdogNum = 1;
		event->u.hpi_event.event.EventDataUnion.WatchdogEvent.WatchdogAction = SAHPI_WAE_RESET;
		event->u.hpi_event.event.EventDataUnion.WatchdogEvent.WatchdogPreTimerAction = SAHPI_WPI_SMI;
		event->u.hpi_event.event.EventDataUnion.WatchdogEvent.WatchdogUse = SAHPI_WTU_BIOS_FRB2;
		
		
		rc1 = sim_inject_event(state, event);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 1: %d %%%%%%%%\n", rc1));
		
	        event2->did = 1; /* domain id for the event */
                event2->type = OH_ET_HPI;
                event2->u.hpi_event.res = sim_rpt_array[0].rpt;
                event2->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event2->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event2->u.hpi_event.event.EventType = SAHPI_ET_HOTSWAP;
		event2->u.hpi_event.event.Timestamp = 0;
		event2->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event2->u.hpi_event.event.EventDataUnion.HotSwapEvent.HotSwapState = SAHPI_HS_STATE_INSERTION_PENDING;
		event2->u.hpi_event.event.EventDataUnion.HotSwapEvent.PreviousHotSwapState = SAHPI_HS_STATE_NOT_PRESENT;				

		rc1 = sim_inject_event(state, event2);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 2: %d %%%%%%%%\n", rc1));
		
	        event3->did = 1; /* domain id for the event */
                event3->type = OH_ET_HPI;
                event3->u.hpi_event.res = sim_rpt_array[0].rpt;
                event3->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event3->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event3->u.hpi_event.event.EventType = SAHPI_ET_SENSOR;
		event3->u.hpi_event.event.Timestamp = 0;
		event3->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.SensorNum = SAHPI_DEFAGSENS_PWR;
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.SensorType = SAHPI_VOLTAGE;	   
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.EventCategory = SAHPI_EC_GENERIC;   
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.Assertion = 1;   
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.EventState = SAHPI_ES_STATE_00;    
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.OptionalDataPresent = SAHPI_SOD_TRIGGER_READING;
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.TriggerReading.IsSupported = 1;
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.TriggerReading.Type = SAHPI_SENSOR_READING_TYPE_UINT64;
		event3->u.hpi_event.event.EventDataUnion.SensorEvent.TriggerReading.Value.SensorUint64 = 0xFEEEEEEEEEEEEEED;
		
		rc1 = sim_inject_event(state, event3);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 3: %d %%%%%%%%\n", rc1));	
		
	        event4->did = 1; /* domain id for the event */
                event4->type = OH_ET_HPI;
                event4->u.hpi_event.res = sim_rpt_array[0].rpt;
                event4->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event4->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event4->u.hpi_event.event.EventType = SAHPI_ET_OEM;
		event4->u.hpi_event.event.Timestamp = 0;
		event4->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event4->u.hpi_event.event.EventDataUnion.OemEvent.MId = SAHPI_MANUFACTURER_ID_UNSPECIFIED;		
		event4->u.hpi_event.event.EventDataUnion.OemEvent.OemEventData.DataType = SAHPI_TL_TYPE_BCDPLUS;
		event4->u.hpi_event.event.EventDataUnion.OemEvent.OemEventData.Language = SAHPI_LANG_ENGLISH;
		event4->u.hpi_event.event.EventDataUnion.OemEvent.OemEventData.DataLength = 12;
		memcpy(event4->u.hpi_event.event.EventDataUnion.OemEvent.OemEventData.Data, &OEMString[0],
		       event4->u.hpi_event.event.EventDataUnion.OemEvent.OemEventData.DataLength);
		
		rc1 = sim_inject_event(state, event4);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 4: %d %%%%%%%%\n", rc1));	
		
	        event5->did = 1; /* domain id for the event */
                event5->type = OH_ET_HPI;
                event5->u.hpi_event.res = sim_rpt_array[0].rpt;
                event5->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event5->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event5->u.hpi_event.event.EventType = SAHPI_ET_HPI_SW;
		event5->u.hpi_event.event.Timestamp = 0;
		event5->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.MId = SAHPI_MANUFACTURER_ID_UNSPECIFIED;
		event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.Type = SAHPI_HPIE_STARTUP;
		event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.EventData.DataType = SAHPI_TL_TYPE_TEXT;
		event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.EventData.Language = SAHPI_LANG_ENGLISH;
		event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.EventData.DataLength = 11;  								     
		memcpy(event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.EventData.Data, &SWString[0],
		       event5->u.hpi_event.event.EventDataUnion.HpiSwEvent.EventData.DataLength);

		rc1 = sim_inject_event(state, event5);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 5: %d %%%%%%%%\n", rc1));	
		
	        event6->did = 1; /* domain id for the event */
                event6->type = OH_ET_HPI;
                event6->u.hpi_event.res = sim_rpt_array[0].rpt;
                event6->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event6->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event6->u.hpi_event.event.EventType = SAHPI_ET_SENSOR_ENABLE_CHANGE;
		event6->u.hpi_event.event.Timestamp = 0;
		event6->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.SensorNum = SAHPI_DEFAGSENS_PWR;
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.SensorType = SAHPI_VOLTAGE;	   
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.EventCategory = SAHPI_EC_GENERIC;   
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.SensorEnable = 1;
                event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.SensorEventEnable = 1;
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.AssertEventMask = SAHPI_ES_STATE_ASSERTED;
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.DeassertEventMask = SAHPI_ES_STATE_DEASSERTED;
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.OptionalDataPresent = SAHPI_SEOD_CURRENT_STATE;  
		event6->u.hpi_event.event.EventDataUnion.SensorEnableChangeEvent.CurrentState = SAHPI_ES_LIMIT_EXCEEDED; 
		
		rc1 = sim_inject_event(state, event6);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 6: %d %%%%%%%%\n", rc1));	
		
	        event7->did = 1; /* domain id for the event */
                event7->type = OH_ET_HPI;
                event7->u.hpi_event.res = sim_rpt_array[0].rpt;
                event7->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event7->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event7->u.hpi_event.event.EventType = SAHPI_ET_DOMAIN;
		event7->u.hpi_event.event.Timestamp = 0;
		event7->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event7->u.hpi_event.event.EventDataUnion.DomainEvent.Type = SAHPI_DOMAIN_REF_ADDED;
		event7->u.hpi_event.event.EventDataUnion.DomainEvent.DomainId = SAHPI_UNSPECIFIED_DOMAIN_ID;
		
		rc1 = sim_inject_event(state, event7);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 7: %d %%%%%%%%\n", rc1));	
		
	        event8->did = 1; /* domain id for the event */
                event8->type = OH_ET_HPI;
                event8->u.hpi_event.res = sim_rpt_array[0].rpt;
                event8->u.hpi_event.rdr.RecordId = 0; // Not sure here
		event8->u.hpi_event.event.Source = sim_rpt_array[0].rpt.ResourceId;
		event8->u.hpi_event.event.EventType = SAHPI_ET_RESOURCE;
		event8->u.hpi_event.event.Timestamp = 0;
		event8->u.hpi_event.event.Severity = SAHPI_CRITICAL;
		event8->u.hpi_event.event.EventDataUnion.ResourceEvent.ResourceEventType = SAHPI_RESE_RESOURCE_FAILURE;								  				       	        	     		
		
		rc1 = sim_inject_event(state, event8);
                DEBUGMSGTL ((AGENT, "%%%%%%%% Return code from inject 8: %d %%%%%%%%\n", rc1));	

	}


        /* start event thread */
        set_run_threaded(TRUE);
        if (start_event_thread(sessionid) != AGENT_ERR_NOERROR) {
                snmp_log (LOG_ERR, "Could not start our internal loop . Exiting\n.");
                rc = -1;
                goto stop;
        }

        send_traps = AGENT_TRUE;
        /* If we're going to be a snmp master agent, initial the ports */

        if (!agentx_subagent)
                init_master_agent ();	/* open the port to listen on (defaults to udp:161) */
                
        if (do_fork == AGENT_TRUE) {
                if ((child = fork ()) < 0) {
                        snmp_log (LOG_ERR, "Could not fork!\n");
                        exit (-1);
                }
                if (child != 0)
                        exit (0);
        }

   
        /* In case we recevie a request to stop (kill -TERM or kill -INT) */
        keep_running = 1;
        signal (SIGTERM, stop_server);
        signal (SIGINT, stop_server);



        /* you're main loop here... */
        while (keep_running) {
                /* if you use select(), see snmp_select_info() in snmp_api(3) */
                /*     --- OR ---  */
                rc = agent_check_and_process (1);	/* 0 == don't block */
        }
stop:
        DEBUGMSGTL ((AGENT,
        "WARNING: closeSaHpiSession: hpiSubagent.c: nolong implemented!"));
        //closeSaHpiSession();
        /* at shutdown time */
        snmp_log (LOG_INFO, "Stopping %s\n", version);
        snmp_shutdown (AGENT);
  
  return rc;
}


/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
#if 0

/*
 * Count of newly added RPT, RDR, Events and SEL entries since last  populate_ call
 * to be global. Reset every time the respective populate_ call is made.
 */
u_long rdr_new_entry_count;
u_long rpt_new_entry_count;
u_long event_new_entry_count;
u_long sel_new_entry_count;

int build_full_oid (oid * prefix, size_t prefix_len,
		oid * column, size_t column_len,
		netsnmp_index * index,
		oid * out_oid, size_t in_len, size_t * out_len)
{

  int register len = prefix_len + column_len;
  int register i = 0;

  if (index)
    len += index->len;

  if (len > in_len)
    return AGENT_ERR_MEMORY_FAULT;

  *out_len = len;
  memcpy (out_oid, prefix, prefix_len * sizeof (oid));

  for (; i < column_len; i++)
    {
      out_oid[prefix_len + i] = column[i];
    }
  len = prefix_len + i;

  if (index)
    {
      for (i = 0; i < index->len; i++)
	{
	  out_oid[len + i] = index->oids[i];
	}
    }
  return AGENT_ERR_NOERROR;
}


netsnmp_variable_list *
build_notification (const netsnmp_index * index,
		    const trap_vars * var, const size_t var_len,
		    const oid * notification_oid,
		    const size_t notification_oid_len,
		    const oid * root_table_oid,
		    const size_t root_table_oid_len,
		    const SaHpiDomainIdT domain_id, const oid * domain_id_oid,
		    const size_t domain_id_oid_len,
		    const SaHpiResourceIdT resource_id,
		    const oid * resource_id_oid,
		    const size_t resource_id_oid_len)
{

  int i, j;
  netsnmp_variable_list *notification_vars = NULL;
  oid snmptrap[] = { snmptrap_oid };
  oid full_oid[MAX_OID_LEN];
  size_t full_oid_len;



  DEBUGMSGTL ((AGENT, "--- build_notification: Entry.\n"));


  if ((root_table_oid_len + 2 + index->len) > MAX_OID_LEN)
    {
      DEBUGMSGTL ((AGENT, "The length of the OID exceeds MAX_OID_LEN!\n"));
      return NULL;
    }

  // First is the Notification_OID
  snmp_varlist_add_variable (&notification_vars,
			     snmptrap, OID_LENGTH (snmptrap),
			     ASN_OBJECT_ID,
			     (const u_char *) (const oid *) notification_oid,
			     notification_oid_len * sizeof (oid));

  // Next the DomainID
  snmp_varlist_add_variable (&notification_vars,
			     domain_id_oid, domain_id_oid_len,
			     ASN_UNSIGNED,
			     (const u_char *) &domain_id,
			     sizeof (SaHpiDomainIdT));
  // The ResourceID
  snmp_varlist_add_variable (&notification_vars,
			     resource_id_oid, resource_id_oid_len,
			     ASN_UNSIGNED,
			     (const u_char *) &resource_id,
			     sizeof (SaHpiResourceIdT));

  // Attach the rest of information
  for (i = 0; i < var_len; i++)
    {

      // Generate the full OID.   
      memcpy (full_oid, root_table_oid, root_table_oid_len * sizeof (oid));
      full_oid_len = root_table_oid_len;
      // Get the column number.
      full_oid[full_oid_len++] = 1;
      full_oid[full_oid_len++] = var[i].column;
      // Put the index value in
      for (j = 0; j < index->len; j++)
	{
	  full_oid[full_oid_len + j] = index->oids[j];
	}
      full_oid_len += index->len;

      snmp_varlist_add_variable (&notification_vars,
				 full_oid,
				 full_oid_len,
				 var[i].type, var[i].value, var[i].value_len);

    }
  DEBUGMSGTL ((AGENT, "--- build_notification: Exit.\n"));
  return notification_vars;

}

long
calculate_hash_value (void *data, int len)
{

  register long hash = 0;
  register int i = 0;

  // WARNING. Can seg fault!
  // Pretty simple. Can also roll-over back to zero.

  //DEBUGMSGTL((AGENT,"HASH DATA:\n"));
  for (; i < len; i++, hash += ((char *) data)[i]);
  //{
  //printf("%X",((char *)data)[i]);
  //}
  //DEBUGMSGTL((AGENT,"HASH END\n"));
  return hash;
}

SaErrorT
rcSaHpi ()
{
  return err;
}

int
closeSaHpiSession ()
{

  DEBUGMSGTL ((AGENT, "--- closeSaHpiSession: Entry. "));
  if (session_avail == AGENT_TRUE)
    {
      err = saHpiUnsubscribe (session_id);
      if (SA_OK != err)
	{
	  snmp_log (LOG_ERR, "saHpiUnsubscirbe error: %s.\n",
                    oh_lookup_error(err));
	  return AGENT_ERR_SESSION_CLOSE;
	}
      err = saHpiFinalize ();
      if (SA_OK != err)
	{
	  snmp_log (LOG_ERR, "saHpiFinalize error: %s\n",
		    oh_lookup_error(err));
	  return AGENT_ERR_SESSION_CLOSE;
	}
      session_avail = AGENT_FALSE;
    }
  DEBUGMSGTL ((AGENT, "--- closeSaHpiSession: Exit. "));

  return AGENT_ERR_NOERROR;
}

int
getSaHpiSession (SaHpiSessionIdT * out)
{

  SaHpiVersionT version;

  DEBUGMSGTL ((AGENT, "--- getSaHpiSession: Entry. "));

  if (session_avail == AGENT_FALSE)
    {
      err = saHpiInitialize (&version);
      if (SA_OK != err)
	{
	  snmp_log (LOG_ERR, "saHpiInitialize error: %s\n",
		    oh_lookup_error(err));
	  return AGENT_ERR_INIT;
	}
      err = saHpiSessionOpen (SAHPI_DEFAULT_DOMAIN_ID, &session_id, NULL);
      if (SA_OK != err)
	{
	  snmp_log (LOG_ERR, "saHpiSessionOpen error: %s\n",
		    oh_lookup_error(err));
	  return AGENT_ERR_SESSION_OPEN;
	}

      err = saHpiSubscribe (session_id, SAHPI_FALSE);
      if (SA_OK != err)
	{
	  snmp_log (LOG_ERR, "saHpiSubscribe failed. error: %s\n",
		    oh_lookup_error(err));
	  return AGENT_ERR_SUBSCRIBE;
	}
      session_avail = AGENT_TRUE;
      //Subscribe to the Events
    }


  rediscover_count--;
  if (rediscover_count <= 0)
    {
      // Re-set the  rediscover_count;
      DEBUGMSGTL ((AGENT, "Calling 'saHpiResourceDiscover()'.\n"));
      rediscover_count = REDISCOVER_COUNT_MAX;
      err = saHpiResourcesDiscover (session_id);
      if (SA_OK != err)
	{
	  snmp_log (LOG_ERR, "saHpiResourcesDiscover error: %s\n",
		    oh_lookup_error(err));
	  return AGENT_ERR_DISCOVER;
	}
    }

  if (out)
    *out = session_id;

  DEBUGMSGTL ((AGENT, "--- getSaHpiSession: Exit\n"));
  return AGENT_ERR_NOERROR;
}

int
didSaHpiChanged (int *answer, SaHpiRptInfoT * info)
{

  int rc = AGENT_ERR_NOERROR;
  SaHpiRptInfoT rpt_info_new;
  SaErrorT err;

  DEBUGMSGTL ((AGENT, "--- didSaHpiChanged: Entry. "));

  if (session_avail == AGENT_FALSE)
    {
      if ((rc = getSaHpiSession (NULL)) != AGENT_ERR_NOERROR)
	{
	  // Something is screwy. Bail out
	  return rc;
	}
    }
  /* 
     err = saHpiResourcesDiscover (session_id);
     if (SA_OK != err)
     {
     snmp_log (LOG_ERR, "saHpiResourcesDiscover error: %s\n",
     oh_lookup_error(err));
     return AGENT_ERR_DISCOVER;
     }
   */
  err = saHpiRptInfoGet (session_id, &rpt_info_new);
  if (SA_OK != err)
    {
      snmp_log (LOG_ERR, "saHpiRptInfoGet error: %s\n",
		oh_lookup_error(err));
      return AGENT_ERR_RPTGET;
    }

  if ((rpt_info_new.UpdateCount != rpt_info.UpdateCount) ||
      (rpt_info_new.UpdateTimestamp != rpt_info.UpdateTimestamp))
    {
      // Something new.
      if (answer)
	{
	  *answer = AGENT_TRUE;
	  DEBUGMSGTL ((AGENT, "New UpdateCount: %d, TimeStamp: %d\n ",
		       rpt_info.UpdateCount, rpt_info.UpdateTimestamp));
	}
      rpt_info = rpt_info_new;
    }
  else
    {
      if (answer)
	*answer = AGENT_FALSE;
    }

  // Change regardless of answer.
  if (info)
    *info = rpt_info;

  DEBUGMSGTL ((AGENT, "--- didSaHpiChanged: Exit.\n"));
  return rc;

}
#endif
