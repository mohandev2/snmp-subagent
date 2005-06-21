/*
 * Note: this file originally auto-generated by mib2c using
 *       : mib2c.array-user.conf,v 5.18.2.2 2004/02/09 18:21:47 rstory Exp $
 *
 * $Id$
 *
 *
 * For help understanding NET-SNMP in general, please check the 
 *     documentation and FAQ at:
 *
 *     http://www.net-snmp.org/
 *
 *
 * For help understanding this code, the agent and how it processes
 *     requests, please check the following references.
 *
 *     http://www.net-snmp.org/tutorial-5/
 *
 *
 * You can also join the #net-snmp channel on irc.freenode.net
 *     and ask for help there.
 *
 *
 * And if all else fails, send a detailed message to the developers
 *     describing the problem you are having to:
 *
 *    net-snmp-coders@lists.sourceforge.net
 *
 *
 * Yes, there is lots of code here that you might not use. But it is much
 * easier to remove code than to add it!
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <net-snmp/library/snmp_assert.h>

#include <SaHpi.h>
#include "saHpiEventTable.h"
#include <hpiSubagent.h>
#include <hpiCheckIndice.h>
#include <saHpiResourceTable.h>
#include <saHpiResourceEventTable.h>
#include <saHpiDomainEventTable.h>
#include <saHpiOEMEventTable.h>
#include <saHpiHotSwapEventTable.h>
#include <saHpiWatchdogEventTable.h>
#include <session_info.h>
#include <oh_utils.h>


static     netsnmp_handler_registration *my_handler = NULL;
static     netsnmp_table_array_callbacks cb;

oid saHpiEventTable_oid[] = { saHpiEventTable_TABLE_OID };
size_t saHpiEventTable_oid_len = OID_LENGTH(saHpiEventTable_oid);

/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
static u_long event_entry_count_total = 0;
static u_long event_entry_count = 0;
static oid saHpiEventEntryCountTotal_oid[] = { 1,3,6,1,4,1,18568,2,1,1,3,1,1 };
static oid saHpiEventEntryCount_oid[] = { 1,3,6,1,4,1,18568,2,1,1,3,1,2 };
int handle_saHpiEventEntryCountTotal(netsnmp_mib_handler *handler,
                                     netsnmp_handler_registration *reginfo,
                                     netsnmp_agent_request_info   *reqinfo,
                                     netsnmp_request_info         *requests);
int handle_saHpiEventEntryCount(netsnmp_mib_handler *handler,
                                netsnmp_handler_registration *reginfo,
                                netsnmp_agent_request_info   *reqinfo,
                                netsnmp_request_info         *requests);
int initialize_table_saHpiEventEntryCountTotal(void);
int initialize_table_saHpiEventEntryCount(void);



SaErrorT populate_saHpiEventTable(SaHpiSessionIdT sessionid)
{
        SaErrorT rv = SA_OK;

        SaHpiEventT          event;         
        SaHpiRdrT            rdr;            
        SaHpiRptEntryT       rpt_entry;       
        SaHpiEvtQueueStatusT event_queue_status;

	oid event_oid[MAX_OID_LEN];
	netsnmp_index event_index;
	saHpiEventTable_context *event_context;

        oid child_oid[MAX_OID_LEN];
        size_t child_oid_len;

        int i;

        DEBUGMSGTL ((AGENT, "populate_saHpiEventTable, called\n"));

        rv = saHpiEventGet (sessionid, 
                            SAHPI_TIMEOUT_IMMEDIATE, 
                            &event, 
                            &rdr, 
                            &rpt_entry, 
                            &event_queue_status);

        while (rv == SA_OK) {

                switch (event.EventType) {
                case SAHPI_ET_RESOURCE:
                        printf("SAHPI_ET_RESOURCE: rv [%d]\n", rv);
                        printf("        Event Type: [%s]\n", 
                        oh_lookup_resourceeventtype(event.EventDataUnion.ResourceEvent.ResourceEventType));
                        printf("        Resource: [%d]\n",event.Source);
                        printf("        Severity: [%s]\n\n",oh_lookup_severity(event.Severity));
                        populate_saHpiResourceEventTable(sessionid, &event,                                           
                                                         child_oid, 
                                                         &child_oid_len);
                        break;
                case SAHPI_ET_DOMAIN:
                        printf("SAHPI_ET_DOMAIN: rv [%d]\n", rv);
                        printf("        Event Type: [%s]\n\n", 
                        oh_lookup_domaineventtype(event.EventDataUnion.DomainEvent.Type));
                        populate_saHpiDomainEventTable(sessionid, &event,                                           
                                                       child_oid, 
                                                       &child_oid_len);
                        break;
                case SAHPI_ET_SENSOR:
                        printf("SAHPI_ET_SENSOR: rv [%d]\n", rv);
                        printf("        Sensor Type: [%s]\n\n",
                        oh_lookup_sensortype(event.EventDataUnion.SensorEvent.SensorType));
                        populate_saHpiSensorEventTable(sessionid, &event,                                           
                                                       child_oid, 
                                                       &child_oid_len);
                        break;
                case SAHPI_ET_SENSOR_ENABLE_CHANGE:
                        printf("SAHPI_ET_SENSOR_ENABLE_CHANGE: rv [%d]\n\n", rv);
                        //populate_saHpiSensorEnableChangeEventTable();
                        goto end;
                        break;
                case SAHPI_ET_HOTSWAP:
                        printf("SAHPI_ET_HOTSWAP: rv [%d]\n\n", rv);
                        populate_saHpiHotSwapEventTable(sessionid, &event,
                                                        child_oid, 
                                                        &child_oid_len);
                        break;
                case SAHPI_ET_WATCHDOG:
                        printf("SAHPI_ET_WATCHDOG: rv [%d]\n\n", rv);
                        populate_saHpiWatchdogEventTable(sessionid, &event,
                                                         child_oid, 
                                                         &child_oid_len);
                        break;
                case SAHPI_ET_HPI_SW:
                        printf("SAHPI_ET_HPI_SW: rv [%d]\n\n", rv);
                        //populate_saHpiSoftwareEventTable();
                        goto end;
                        break;
                case SAHPI_ET_OEM:
                        printf("SAHPI_ET_OEM: rv [%d]\n\n", rv);
                        populate_saHpiOemEventTable(sessionid, &event,                                           
                                                    child_oid, 
                                                    &child_oid_len);
                        break;
                case SAHPI_ET_USER:
                        printf("SAHPI_ET_USER: rv [%d]\n\n", rv);
                        //populate_saHpiUserEventEventTable();
                        goto end;
                        break;
                default:
                        printf("********* unknown event type *********\n");
                        break;        
                }

                event_index.len = child_oid_len;
                for (i=0; i < child_oid_len; i++) 
                        event_oid[i] = child_oid[i];
                event_index.oids = (oid *) & event_oid;
	
                /* See if it exists. */
                event_context = NULL;
                event_context = CONTAINER_FIND (cb.container, &event_index);
		
                if (!event_context) { 
                        // New entry. Add it
                        event_context = 
                                saHpiEventTable_create_row (&event_index);
                }
                if (!event_context) {
                        snmp_log (LOG_ERR, "Not enough memory for a Event row!");
                        return AGENT_ERR_INTERNAL_ERROR;
                }


                /** RowPointer = ASN_OBJECT_ID */
		event_context->saHpiEventRowPointer_len = 
                        child_oid_len * sizeof (oid);
		memcpy (event_context->saHpiEventRowPointer, 
			child_oid, 
			event_context->saHpiEventRowPointer_len);

                /** SaHpiSeverity = ASN_INTEGER */
                event_context->saHpiEventSeverity = event.Severity + 1;

                /** SaHpiTime = ASN_COUNTER64 */
                event_context->saHpiEventSaHpiTime = event.Timestamp;

                /** INTEGER = ASN_INTEGER */
                event_context->saHpiEventType = event.EventType + 1;


                CONTAINER_INSERT (cb.container, event_context);

                event_entry_count = CONTAINER_SIZE (cb.container);
                event_entry_count_total = CONTAINER_SIZE (cb.container);

                /* get next event if available */
                memset(&event, 0, sizeof(event));
                memset(&rdr, 0, sizeof(rdr));
                memset(&rpt_entry, 0, sizeof(rpt_entry));
                memset(&event_queue_status, 0, sizeof(event_queue_status));
end:            
                rv = saHpiEventGet (sessionid, 
                                    SAHPI_TIMEOUT_IMMEDIATE, 
                                    &event, 
                                    &rdr, 
                                    &rpt_entry, 
                                    &event_queue_status);
        }

        return rv;
}



int handle_saHpiEventEntryCountTotal(netsnmp_mib_handler *handler,
                                     netsnmp_handler_registration *reginfo,
                                     netsnmp_agent_request_info   *reqinfo,
                                     netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

        DEBUGMSGTL ((AGENT, "handle_saHpiEventEntryCountTotal, called\n"));
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
                                     (u_char *) &event_entry_count_total,
                                     sizeof(event_entry_count_total));
            break;


        default:
            /* we should never get here, so this is a really bad error */
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int initialize_table_saHpiEventEntryCountTotal(void)
{
        DEBUGMSGTL ((AGENT, "initialize_table_saHpiEventEntryCountTotal, called\n"));

        netsnmp_register_scalar(
                netsnmp_create_handler_registration(
                        "saHpiEventEntryCountTotal", 
                        handle_saHpiEventEntryCountTotal,
                        saHpiEventEntryCountTotal_oid, 
                        OID_LENGTH(saHpiEventEntryCountTotal_oid),
                        HANDLER_CAN_RONLY ));

    return 0;
}

int handle_saHpiEventEntryCount(netsnmp_mib_handler *handler,
                                netsnmp_handler_registration *reginfo,
                                netsnmp_agent_request_info   *reqinfo,
                                netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

        DEBUGMSGTL ((AGENT, "handle_saHpiEventEntryCount, called\n"));

        event_entry_count = CONTAINER_SIZE (cb.container);
    
    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
                                     (u_char *) &event_entry_count,
                                     sizeof(event_entry_count));
            break;


        default:
            /* we should never get here, so this is a really bad error */
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}

int initialize_table_saHpiEventEntryCount(void)
{
        DEBUGMSGTL ((AGENT, "initialize_table_saHpiEventEntryCount, called\n"));

        netsnmp_register_scalar(
                netsnmp_create_handler_registration(
                        "saHpiEventEntryCount", 
                        handle_saHpiEventEntryCount,
                        saHpiEventEntryCount_oid, 
                        OID_LENGTH(saHpiEventEntryCount_oid),
                        HANDLER_CAN_RONLY ));

        return 0;
}

/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/

/************************************************************
 * keep binary tree to find context by name
 */
static int saHpiEventTable_cmp( const void *lhs, const void *rhs );

/************************************************************
 * compare two context pointers here. Return -1 if lhs < rhs,
 * 0 if lhs == rhs, and 1 if lhs > rhs.
 */
static int
saHpiEventTable_cmp( const void *lhs, const void *rhs )
{
    saHpiEventTable_context *context_l =
        (saHpiEventTable_context *)lhs;
    saHpiEventTable_context *context_r =
        (saHpiEventTable_context *)rhs;

    /*
     * check primary key, then secondary. Add your own code if
     * there are more than 2 indexes
     */
    DEBUGMSGTL ((AGENT, "saHpiEventTable_cmp, called\n"));

    /* check for NULL pointers */
    if (lhs == NULL || rhs == NULL ) {
            DEBUGMSGTL((AGENT,"saHpiEventTable_cmp() NULL pointer ERROR\n" ));
            return 0;
    }
    /* CHECK FIRST INDEX,  saHpiEventRowPointer */
    if ( context_l->index.oids[0] < context_r->index.oids[0])
            return -1;

    if ( context_l->index.oids[0] > context_r->index.oids[0])
            return 1;

    if ( context_l->index.oids[0] == context_r->index.oids[0])
            return 0;

    return 0;
}

/************************************************************
 * Initializes the saHpiEventTable module
 */
void
init_saHpiEventTable(void)
{
        DEBUGMSGTL ((AGENT, "init_saHpiEventTable, called\n"));

    initialize_table_saHpiEventTable();

    initialize_table_saHpiEventEntryCountTotal();

    initialize_table_saHpiEventEntryCount();
}

/************************************************************
 * the *_row_copy routine
 */
static int saHpiEventTable_row_copy(saHpiEventTable_context * dst,
                         saHpiEventTable_context * src)
{
    if(!dst||!src)
        return 1;
        
    /*
     * copy index, if provided
     */
    if(dst->index.oids)
        free(dst->index.oids);
    if(snmp_clone_mem( (void*)&dst->index.oids, src->index.oids,
                           src->index.len * sizeof(oid) )) {
        dst->index.oids = NULL;
        return 1;
    }
    dst->index.len = src->index.len;
    

    /*
     * copy components into the context structure
     */
    /** TODO: add code for external index(s)! */
    memcpy( dst->saHpiEventRowPointer, 
            src->saHpiEventRowPointer,  
            src->saHpiEventRowPointer_len );
    dst->saHpiEventRowPointer_len = src->saHpiEventRowPointer_len;

    dst->saHpiEventSeverity = src->saHpiEventSeverity;

    dst->saHpiEventSaHpiTime = src->saHpiEventSaHpiTime;

    dst->saHpiEventType = src->saHpiEventType;

    return 0;
}

/**
 * the *_extract_index routine
 *
 * This routine is called when a set request is received for an index
 * that was not found in the table container. Here, we parse the oid
 * in the the individual index components and copy those indexes to the
 * context. Then we make sure the indexes for the new row are valid.
 */
int
saHpiEventTable_extract_index( saHpiEventTable_context * ctx, netsnmp_index * hdr )
{
    /*
     * temporary local storage for extracting oid index
     *
     * extract index uses varbinds (netsnmp_variable_list) to parse
     * the index OID into the individual components for each index part.
     */
    /** TODO: add storage for external index(s)! */
    netsnmp_variable_list var_saHpiEventRowPointer;
    int err;

    /*
     * copy index, if provided
     */
    if(hdr) {
        netsnmp_assert(ctx->index.oids == NULL);
        if(snmp_clone_mem( (void*)&ctx->index.oids, hdr->oids,
                           hdr->len * sizeof(oid) )) {
            return -1;
        }
        ctx->index.len = hdr->len;
    }

    /*
     * initialize variable that will hold each component of the index.
     * If there are multiple indexes for the table, the variable_lists
     * need to be linked together, in order.
     */
       /** TODO: add code for external index(s)! */
       memset( &var_saHpiEventRowPointer, 0x00, sizeof(var_saHpiEventRowPointer) );
       var_saHpiEventRowPointer.type = ASN_OBJECT_ID; /* type hint for parse_oid_indexes */
       /** TODO: link this index to the next, or NULL for the last one */
       var_saHpiEventRowPointer.next_variable = NULL;

       memcpy(ctx->saHpiEventRowPointer, hdr->oids, hdr->len * sizeof(oid));
       ctx->saHpiEventRowPointer_len = hdr->len;
       err = SNMP_ERR_NOERROR;
    
    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_saHpiEventRowPointer );

    return err;
}

/************************************************************
 * the *_can_activate routine is called
 * when a row is changed to determine if all the values
 * set are consistent with the row's rules for a row status
 * of ACTIVE.
 *
 * return 1 if the row could be ACTIVE
 * return 0 if the row is not ready for the ACTIVE state
 */
int saHpiEventTable_can_activate(saHpiEventTable_context *undo_ctx,
                      saHpiEventTable_context *row_ctx,
                      netsnmp_request_group * rg)
{
    /*
     * TODO: check for activation requirements here
     */


    /*
     * be optimistic.
     */
    return 1;
}

/************************************************************
 * the *_can_deactivate routine is called when a row that is
 * currently ACTIVE is set to a state other than ACTIVE. If
 * there are conditions in which a row should not be allowed
 * to transition out of the ACTIVE state (such as the row being
 * referred to by another row or table), check for them here.
 *
 * return 1 if the row can be set to a non-ACTIVE state
 * return 0 if the row must remain in the ACTIVE state
 */
int saHpiEventTable_can_deactivate(saHpiEventTable_context *undo_ctx,
                        saHpiEventTable_context *row_ctx,
                        netsnmp_request_group * rg)
{
    /*
     * TODO: check for deactivation requirements here
     */
    return 1;
}

/************************************************************
 * the *_can_delete routine is called to determine if a row
 * can be deleted.
 *
 * return 1 if the row can be deleted
 * return 0 if the row cannot be deleted
 */
int saHpiEventTable_can_delete(saHpiEventTable_context *undo_ctx,
                    saHpiEventTable_context *row_ctx,
                    netsnmp_request_group * rg)
{
    /*
     * probably shouldn't delete a row that we can't
     * deactivate.
     */
    if(saHpiEventTable_can_deactivate(undo_ctx,row_ctx,rg) != 1)
        return 0;
    
    /*
     * TODO: check for other deletion requirements here
     */
    return 1;
}

/************************************************************
 * the *_create_row routine is called by the table handler
 * to create a new row for a given index. If you need more
 * information (such as column values) to make a decision
 * on creating rows, you must create an initial row here
 * (to hold the column values), and you can examine the
 * situation in more detail in the *_set_reserve1 or later
 * states of set processing. Simple check for a NULL undo_ctx
 * in those states and do detailed creation checking there.
 *
 * returns a newly allocated saHpiEventTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiEventTable_context *
saHpiEventTable_create_row( netsnmp_index* hdr)
{
    saHpiEventTable_context * ctx =
        SNMP_MALLOC_TYPEDEF(saHpiEventTable_context);
    if(!ctx)
        return NULL;

    event_entry_count_total++;
        
    /*
     * TODO: check indexes, if necessary.
     */
    if(saHpiEventTable_extract_index( ctx, hdr )) {
        free(ctx->index.oids);
        free(ctx);
        return NULL;
    }

    /* netsnmp_mutex_init(ctx->lock);
       netsnmp_mutex_lock(ctx->lock); */

    /*
     * TODO: initialize any default values here. This is also
     * first place you really should allocate any memory for
     * yourself to use.  If you allocated memory earlier,
     * make sure you free it for earlier error cases!
     */
    /**
     ctx->saHpiEventSeverity = 0;
    */

    return ctx;
}

/************************************************************
 * the *_duplicate row routine
 */
saHpiEventTable_context *
saHpiEventTable_duplicate_row( saHpiEventTable_context * row_ctx)
{
    saHpiEventTable_context * dup;

    if(!row_ctx)
        return NULL;

    dup = SNMP_MALLOC_TYPEDEF(saHpiEventTable_context);
    if(!dup)
        return NULL;
        
    if(saHpiEventTable_row_copy(dup,row_ctx)) {
        free(dup);
        dup = NULL;
    }

    return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index * saHpiEventTable_delete_row( saHpiEventTable_context * ctx )
{
  /* netsnmp_mutex_destroy(ctx->lock); */

    if(ctx->index.oids)
        free(ctx->index.oids);

    /*
     * TODO: release any memory you allocated here...
     */

    /*
     * release header
     */
    free( ctx );

    return NULL;
}


/************************************************************
 * RESERVE is used to check the syntax of all the variables
 * provided, that the values being set are sensible and consistent,
 * and to allocate any resources required for performing the SET.
 * After this stage, the expectation is that the set ought to
 * succeed, though this is not guaranteed. (In fact, with the UCD
 * agent, this is done in two passes - RESERVE1, and
 * RESERVE2, to allow for dependancies between variables).
 *
 * BEFORE calling this routine, the agent will call duplicate_row
 * to create a copy of the row (unless this is a new row; i.e.
 * row_created == 1).
 *
 * next state -> SET_RESERVE2 || SET_FREE
 */
void saHpiEventTable_set_reserve1( netsnmp_request_group *rg )
{
    saHpiEventTable_context *row_ctx =
            (saHpiEventTable_context *)rg->existing_row;
    saHpiEventTable_context *undo_ctx =
            (saHpiEventTable_context *)rg->undo_info;
    netsnmp_variable_list *var;
    netsnmp_request_group_item *current;
    int rc;


    /*
     * TODO: loop through columns, check syntax and lengths. For
     * columns which have no dependencies, you could also move
     * the value/range checking here to attempt to catch error
     * cases as early as possible.
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;
        rc = SNMP_ERR_NOERROR;

        switch(current->tri->colnum) {

        default: /** We shouldn't get here */
            rc = SNMP_ERR_GENERR;
            snmp_log(LOG_ERR, "unknown column in "
                     "saHpiEventTable_set_reserve1\n");
        }

        if (rc)
           netsnmp_set_mode_request_error(MODE_SET_BEGIN, current->ri, rc );
        rg->status = SNMP_MAX( rg->status, current->ri->status );
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

void saHpiEventTable_set_reserve2( netsnmp_request_group *rg )
{
    saHpiEventTable_context *row_ctx = (saHpiEventTable_context *)rg->existing_row;
    saHpiEventTable_context *undo_ctx = (saHpiEventTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;
    netsnmp_variable_list *var;
    int rc;

    rg->rg_void = rg->list->ri;

    /*
     * TODO: loop through columns, check for valid
     * values and any range constraints.
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;
        rc = SNMP_ERR_NOERROR;

        switch(current->tri->colnum) {

        default: /** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }

        if (rc)
           netsnmp_set_mode_request_error(MODE_SET_BEGIN, current->ri, rc);
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

/************************************************************
 * Assuming that the RESERVE phases were successful, the next
 * stage is indicated by the action value ACTION. This is used
 * to actually implement the set operation. However, this must
 * either be done into temporary (persistent) storage, or the
 * previous value stored similarly, in case any of the subsequent
 * ACTION calls fail.
 *
 * In your case, changes should be made to row_ctx. A copy of
 * the original row is in undo_ctx.
 */
void saHpiEventTable_set_action( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiEventTable_context *row_ctx = (saHpiEventTable_context *)rg->existing_row;
    saHpiEventTable_context *undo_ctx = (saHpiEventTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    int            row_err = 0;

    /*
     * TODO: loop through columns, copy varbind values
     * to context structure for the row.
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        default: /** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

#if 0
    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
#ifndef saHpiEventTable_CAN_MODIFY_ACTIVE_ROW
    if( undo_ctx && RS_IS_ACTIVE(undo_ctx->saHpiDomainAlarmRowStatus) &&
        row_ctx && RS_IS_ACTIVE(row_ctx->saHpiDomainAlarmRowStatus) ) {
            row_err = 1;
    }
#endif

    /*
     * check activation/deactivation
     */
    row_err = netsnmp_table_array_check_row_status(&cb, rg,
                                  row_ctx ? &row_ctx->saHpiDomainAlarmRowStatus : NULL,
                                  undo_ctx ? &undo_ctx->saHpiDomainAlarmRowStatus : NULL);
#endif

    if(row_err) {
        netsnmp_set_mode_request_error(MODE_SET_BEGIN,
                                       (netsnmp_request_info*)rg->rg_void,
                                       row_err);
        return;
    }

    /*
     * TODO: if you have dependencies on other tables, this would be
     * a good place to check those, too.
     */
}

/************************************************************
 * Only once the ACTION phase has completed successfully, can
 * the final COMMIT phase be run. This is used to complete any
 * writes that were done into temporary storage, and then release
 * any allocated resources. Note that all the code in this phase
 * should be "safe" code that cannot possibly fail (cue
 * hysterical laughter). The whole intent of the ACTION/COMMIT
 * division is that all of the fallible code should be done in
 * the ACTION phase, so that it can be backed out if necessary.
 *
 * BEFORE calling this routine, the agent will update the
 * container (inserting a row if row_created == 1, or removing
 * the row if row_deleted == 1).
 *
 * AFTER calling this routine, the agent will delete the
 * undo_info.
 */
void saHpiEventTable_set_commit( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiEventTable_context *row_ctx = (saHpiEventTable_context *)rg->existing_row;
    saHpiEventTable_context *undo_ctx = (saHpiEventTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        default: /** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

/************************************************************
 * If either of the RESERVE calls fail, the write routines
 * are called again with the FREE action, to release any resources
 * that have been allocated. The agent will then return a failure
 * response to the requesting application.
 *
 * AFTER calling this routine, the agent will delete undo_info.
 */
void saHpiEventTable_set_free( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiEventTable_context *row_ctx = (saHpiEventTable_context *)rg->existing_row;
    saHpiEventTable_context *undo_ctx = (saHpiEventTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        default: 
                break;
                /** We shouldn't get here */
                /** should have been logged in reserve1 */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

/************************************************************
 * If the ACTION phase does fail (for example due to an apparently
 * valid, but unacceptable value, or an unforeseen problem), then
 * the list of write routines are called again, with the UNDO
 * action. This requires the routine to reset the value that was
 * changed to its previous value (assuming it was actually changed),
 * and then to release any resources that had been allocated. As
 * with the FREE phase, the agent will then return an indication
 * of the error to the requesting application.
 *
 * BEFORE calling this routine, the agent will update the container
 * (remove any newly inserted row, re-insert any removed row).
 *
 * AFTER calling this routing, the agent will call row_copy
 * to restore the data in existing_row from the date in undo_info.
 * Then undo_info will be deleted (or existing row, if row_created
 * == 1).
 */
void saHpiEventTable_set_undo( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiEventTable_context *row_ctx = (saHpiEventTable_context *)rg->existing_row;
    saHpiEventTable_context *undo_ctx = (saHpiEventTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        default: /** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}


/************************************************************
 *
 * Initialize the saHpiEventTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiEventTable(void)
{
    netsnmp_table_registration_info *table_info;

    if(my_handler) {
        snmp_log(LOG_ERR, "initialize_table_saHpiEventTable_handler called again\n");
        return;
    }

    memset(&cb, 0x00, sizeof(cb));

    /** create the table structure itself */
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

    /* if your table is read only, it's easiest to change the
       HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY */
    my_handler = netsnmp_create_handler_registration("saHpiEventTable",
                                             netsnmp_table_array_helper_handler,
                                             saHpiEventTable_oid,
                                             saHpiEventTable_oid_len,
                                             HANDLER_CAN_RWRITE);
            
    if (!my_handler || !table_info) {
        snmp_log(LOG_ERR, "malloc failed in "
                 "initialize_table_saHpiEventTable_handler\n");
        return; /** mallocs failed */
    }

    /***************************************************
     * Setting up the table's definition
     */
    /*
     * TODO: add any external indexes here.
     */
        /** TODO: add code for external index(s)! */

    /*
     * internal indexes
     */
        /** index: saHpiEventRowPointer */
        netsnmp_table_helper_add_index(table_info, ASN_OBJECT_ID);

    table_info->min_column = saHpiEventTable_COL_MIN;
    table_info->max_column = saHpiEventTable_COL_MAX;

    /***************************************************
     * registering the table with the master agent
     */
    cb.get_value = saHpiEventTable_get_value;
    cb.container = netsnmp_container_find("saHpiEventTable_primary:"
                                          "saHpiEventTable:"
                                          "table_container");

    netsnmp_container_add_index(cb.container,
                                netsnmp_container_find("saHpiEventTable_secondary:"
                                                       "saHpiEventTable:"
                                                       "table_container"));
    cb.container->next->compare = saHpiEventTable_cmp;


    cb.can_set = 1;

    cb.create_row = (UserRowMethod*)saHpiEventTable_create_row;

    cb.duplicate_row = (UserRowMethod*)saHpiEventTable_duplicate_row;
    cb.delete_row = (UserRowMethod*)saHpiEventTable_delete_row;
    cb.row_copy = (Netsnmp_User_Row_Operation *)saHpiEventTable_row_copy;

    cb.can_activate = (Netsnmp_User_Row_Action *)saHpiEventTable_can_activate;
    cb.can_deactivate = (Netsnmp_User_Row_Action *)saHpiEventTable_can_deactivate;
    cb.can_delete = (Netsnmp_User_Row_Action *)saHpiEventTable_can_delete;

    cb.set_reserve1 = saHpiEventTable_set_reserve1;
    cb.set_reserve2 = saHpiEventTable_set_reserve2;
    cb.set_action = saHpiEventTable_set_action;
    cb.set_commit = saHpiEventTable_set_commit;
    cb.set_free = saHpiEventTable_set_free;
    cb.set_undo = saHpiEventTable_set_undo;

    DEBUGMSGTL(("initialize_table_saHpiEventTable",
                "Registering table saHpiEventTable "
                "as a table array\n"));
    netsnmp_table_container_register(my_handler, table_info, &cb,
                                     cb.container, 1);
}

/************************************************************
 * saHpiEventTable_get_value
 *
 * This routine is called for get requests to copy the data
 * from the context to the varbind for the request. If the
 * context has been properly maintained, you don't need to
 * change in code in this fuction.
 */
int saHpiEventTable_get_value(
            netsnmp_request_info *request,
            netsnmp_index *item,
            netsnmp_table_request_info *table_info )
{
    netsnmp_variable_list *var = request->requestvb;
    saHpiEventTable_context *context = (saHpiEventTable_context *)item;

    switch(table_info->colnum) {

        case COLUMN_SAHPIEVENTROWPOINTER:
            /** RowPointer = ASN_OBJECT_ID */
            snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                         (char*)&context->saHpiEventRowPointer,
                         context->saHpiEventRowPointer_len );
        break;
    
        case COLUMN_SAHPIEVENTSEVERITY:
            /** SaHpiSeverity = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiEventSeverity,
                         sizeof(context->saHpiEventSeverity) );
        break;
    
        case COLUMN_SAHPIEVENTSAHPITIME:
            /** SaHpiTime = ASN_COUNTER64 */
            snmp_set_var_typed_value(var, ASN_COUNTER64,
                         (char*)&context->saHpiEventSaHpiTime,
                         sizeof(context->saHpiEventSaHpiTime) );
        break;
    
        case COLUMN_SAHPIEVENTTYPE:
            /** INTEGER = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiEventType,
                         sizeof(context->saHpiEventType) );
        break;
    
    default: /** We shouldn't get here */
        snmp_log(LOG_ERR, "unknown column in "
                 "saHpiEventTable_get_value\n");
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

/************************************************************
 * saHpiEventTable_get_by_idx
 */
const saHpiEventTable_context *
saHpiEventTable_get_by_idx(netsnmp_index * hdr)
{
    return (const saHpiEventTable_context *)
        CONTAINER_FIND(cb.container, hdr );
}


