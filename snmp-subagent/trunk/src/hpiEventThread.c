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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <signal.h>

#include <SaHpi.h>
#include <oh_utils.h>
#include <session_info.h>
#include <hpiSubagent.h>
#include <hpiEventThread.h>
#include <saHpiEventTable.h>


GThread *event_thread = NULL;
GMutex *thread_mutex = NULL;
GError *event_thread_error = NULL;
static gboolean run_threaded;

static gpointer event_thread_loop(gpointer data);

gboolean get_run_threaded(void)
{
        return run_threaded;
}

void set_run_threaded(gboolean val)
{
        run_threaded = val;
}

static gpointer event_thread_loop(gpointer data)
{
        SaErrorT rv;
        SaHpiEventT          event;
        SaHpiRdrT            rdr;
        SaHpiRptEntryT       rpt_entry;
        SaHpiEvtQueueStatusT event_queue_status;

        SaHpiSessionIdT sessionid = *(SaHpiSessionIdT *)data;

        while(get_run_threaded()) {
                DEBUGMSGTL ((AGENT, "event_thread_loop started ---- sessionid [%d]\n", sessionid));
                rv = saHpiEventGet (get_session_id(SAHPI_UNSPECIFIED_DOMAIN_ID),
                                    SAHPI_TIMEOUT_BLOCK,
                                    &event,
                                    &rdr,
                                    &rpt_entry,
                                    &event_queue_status);

                DEBUGMSGTL ((AGENT, "rv [%s]\n", oh_lookup_error(rv)));
                DEBUGMSGTL ((AGENT, "Event Type [%s]\n", 
                             oh_lookup_eventtype(event.EventType)));
                oh_print_event(&event, 0);

                /* serialize access */
                g_mutex_lock(thread_mutex);

                switch (event.EventType) {
                case SAHPI_ET_RESOURCE:

                        if (event.EventDataUnion.ResourceEvent.ResourceEventType == 
                            SAHPI_RESE_RESOURCE_ADDED) {
                                DEBUGMSGTL ((AGENT, "SAHPI_RESE_RESOURCE_ADDED\n"));
                        } else if (event.EventDataUnion.ResourceEvent.ResourceEventType == 
                                   SAHPI_RESE_RESOURCE_FAILURE) {
                                DEBUGMSGTL ((AGENT, "SAHPI_RESE_RESOURCE_FAILURE\n"));
                        } else if (event.EventDataUnion.ResourceEvent.ResourceEventType == 
                                   SAHPI_RESE_RESOURCE_RESTORED) {
                                DEBUGMSGTL ((AGENT, "SAHPI_RESE_RESOURCE_RESTORED\n"));
                        }

                       rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);

                        break;
                case SAHPI_ET_DOMAIN:

                        if (event.EventDataUnion.DomainEvent.Type == 
                            SAHPI_DOMAIN_REF_ADDED) {
                                DEBUGMSGTL ((AGENT, "SAHPI_DOMAIN_REF_ADDED\n"));
                        } else if (event.EventDataUnion.DomainEvent.Type == 
                                   SAHPI_DOMAIN_REF_REMOVED) {
                                DEBUGMSGTL ((AGENT, "SAHPI_DOMAIN_REF_REMOVED\n"));
                        }

                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);

                        break;
                case SAHPI_ET_SENSOR:              
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                case SAHPI_ET_SENSOR_ENABLE_CHANGE:
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                case SAHPI_ET_HOTSWAP:
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                case SAHPI_ET_WATCHDOG:            
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                case SAHPI_ET_HPI_SW:            
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                case SAHPI_ET_OEM:              
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                case SAHPI_ET_USER: 
                        rv = async_event_add(sessionid, &event, &rdr, &rpt_entry);
                        break;
                default:
                        break;
                }

                /* serialize access */
                g_mutex_unlock(thread_mutex);

        }
        g_thread_exit(0);
        return data;
}


int start_event_thread(SaHpiSessionIdT *sessionid)
{
        DEBUGMSGTL ((AGENT, "Attempting to init event"));
        if (!g_thread_supported()) {
                DEBUGMSGTL ((AGENT, "Initializing thread support"));
                g_thread_init(NULL);
        } else {
                DEBUGMSGTL ((AGENT, "Already supporting threads"));
        }

        thread_mutex = g_mutex_new();
        event_thread = g_thread_create(event_thread_loop,
                                       (gpointer)sessionid, 
                                       FALSE, 
                                       &event_thread_error);
        if (event_thread == NULL) {
                return AGENT_ERR_INIT;
        } 

        return AGENT_ERR_NOERROR;
}





