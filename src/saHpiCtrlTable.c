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

#include "saHpiCtrlTable.h"
#include "hpiCheckIndice.h"

static     netsnmp_handler_registration *my_handler = NULL;
static     netsnmp_table_array_callbacks cb;

oid saHpiCtrlTable_oid[] = { saHpiCtrlTable_TABLE_OID };
size_t saHpiCtrlTable_oid_len = OID_LENGTH(saHpiCtrlTable_oid);


#ifdef saHpiCtrlTable_IDX2
/************************************************************
 * keep binary tree to find context by name
 */
static int saHpiCtrlTable_cmp( const void *lhs, const void *rhs );

/************************************************************
 * compare two context pointers here. Return -1 if lhs < rhs,
 * 0 if lhs == rhs, and 1 if lhs > rhs.
 */
static int
saHpiCtrlTable_cmp( const void *lhs, const void *rhs )
{
    saHpiCtrlTable_context *context_l =
        (saHpiCtrlTable_context *)lhs;
    saHpiCtrlTable_context *context_r =
        (saHpiCtrlTable_context *)rhs;

    /*
     * check primary key, then secondary. Add your own code if
     * there are more than 2 indexes
     */
    int rc;

    /*
     * TODO: implement compare. Remove this ifdef code and
     * add your own code here.
     */
#ifdef TABLE_CONTAINER_TODO
    snmp_log(LOG_ERR,
             "saHpiCtrlTable_compare not implemented! Container order undefined\n" );
    return 0;
#endif
    
    /*
     * EXAMPLE (assuming you want to sort on a name):
     *   
     * rc = strcmp( context_l->xxName, context_r->xxName );
     *
     * if(rc)
     *   return rc;
     *
     * TODO: fix secondary keys (or delete if there are none)
     *
     * if(context_l->yy < context_r->yy) 
     *   return -1;
     *
     * return (context_l->yy == context_r->yy) ? 0 : 1;
     */
}

/************************************************************
 * search tree
 */
/** TODO: set additional indexes as parameters */
saHpiCtrlTable_context *
saHpiCtrlTable_get( const char *name, int len )
{
    saHpiCtrlTable_context tmp;

    /** we should have a secondary index */
    netsnmp_assert(cb.container->next != NULL);
    
    /*
     * TODO: implement compare. Remove this ifdef code and
     * add your own code here.
     */
#ifdef TABLE_CONTAINER_TODO
    snmp_log(LOG_ERR, "saHpiCtrlTable_get not implemented!\n" );
    return NULL;
#endif

    /*
     * EXAMPLE:
     *
     * if(len > sizeof(tmp.xxName))
     *   return NULL;
     *
     * strncpy( tmp.xxName, name, sizeof(tmp.xxName) );
     * tmp.xxName_len = len;
     *
     * return CONTAINER_FIND(cb.container->next, &tmp);
     */
}
#endif


/************************************************************
 * Initializes the saHpiCtrlTable module
 */
void
init_saHpiCtrlTable(void)
{
    initialize_table_saHpiCtrlTable();

    /*
     * TODO: perform any startup stuff here, such as
     * populating the table with initial data.
     *
     * saHpiCtrlTable_context * new_row = create_row(index);
     * CONTAINER_INSERT(cb.container,new_row);
     */
}

/************************************************************
 * the *_row_copy routine
 */
static int saHpiCtrlTable_row_copy(saHpiCtrlTable_context * dst,
                         saHpiCtrlTable_context * src)
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
    dst->saHpiCtrlNum = src->saHpiCtrlNum;

    dst->saHpiCtrlOutputType = src->saHpiCtrlOutputType;

    dst->saHpiCtrlType = src->saHpiCtrlType;

    dst->saHpiCtrlMode = src->saHpiCtrlMode;

    dst->saHpiCtrlReadOnly = src->saHpiCtrlReadOnly;

    dst->saHpiCtrlWriteOnly = src->saHpiCtrlWriteOnly;

    memcpy( dst->saHpiCtrlState, src->saHpiCtrlState, src->saHpiCtrlState_len );
    dst->saHpiCtrlState_len = src->saHpiCtrlState_len;

    memcpy( dst->saHpiCtrlData, src->saHpiCtrlData, src->saHpiCtrlData_len );
    dst->saHpiCtrlData_len = src->saHpiCtrlData_len;

    dst->saHpiCtrlOem = src->saHpiCtrlOem;

    dst->saHpiCtrlTextType = src->saHpiCtrlTextType;

    dst->saHpiCtrlTextLanguage = src->saHpiCtrlTextLanguage;

    memcpy( dst->saHpiCtrlText, src->saHpiCtrlText, src->saHpiCtrlText_len );
    dst->saHpiCtrlText_len = src->saHpiCtrlText_len;

    memcpy( src->saHpiCtrlRDR, dst->saHpiCtrlRDR, src->saHpiCtrlRDR_len );
    dst->saHpiCtrlRDR_len = src->saHpiCtrlRDR_len;

    return 0;
}

#ifdef saHpiCtrlTable_SET_HANDLING

/**
 * the *_extract_index routine
 *
 * This routine is called when a set request is received for an index
 * that was not found in the table container. Here, we parse the oid
 * in the the individual index components and copy those indexes to the
 * context. Then we make sure the indexes for the new row are valid.
 */
int
saHpiCtrlTable_extract_index( saHpiCtrlTable_context * ctx, netsnmp_index * hdr )
{
    /*
     * temporary local storage for extracting oid index
     *
     * extract index uses varbinds (netsnmp_variable_list) to parse
     * the index OID into the individual components for each index part.
     */
    /** TODO: add storage for external index(s)! */
    netsnmp_variable_list var_saHpiDomainId;
    netsnmp_variable_list var_saHpiResourceId;
    netsnmp_variable_list var_saHpiCtrlNum;
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
       memset( &var_saHpiDomainId, 0x00, sizeof(var_saHpiDomainId) );
       var_saHpiDomainId.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
       var_saHpiDomainId.next_variable = &var_saHpiResourceId;

       memset( &var_saHpiResourceId, 0x00, sizeof(var_saHpiResourceId) );
       var_saHpiResourceId.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
       var_saHpiResourceId.next_variable = &var_saHpiCtrlNum;

       memset( &var_saHpiCtrlNum, 0x00, sizeof(var_saHpiCtrlNum) );
       var_saHpiCtrlNum.type = ASN_UNSIGNED; /* type hint for parse_oid_indexes */
       var_saHpiCtrlNum.next_variable = NULL;


    /*
     * parse the oid into the individual index components
     */
    err = parse_oid_indexes( hdr->oids, hdr->len, &var_saHpiDomainId );
    if (err == SNMP_ERR_NOERROR) {
       /*
        * copy index components into the context structure
        */
              /** skipping external index saHpiDomainId */
   
              /** skipping external index saHpiResourceId */
   
                ctx->saHpiCtrlNum = *var_saHpiCtrlNum.val.integer;

		if(!err)
			err = saHpiDomainId_check_index(*var_saHpiDomainId.val.integer);

		if (!err) 
			err = saHpiResourceId_check_index(*var_saHpiResourceId.val.integer);

		if(!err) 
			err = saHpiCtrlNum_check_index(*var_saHpiCtrlNum.val.integer);
    }

    /*
     * parsing may have allocated memory. free it.
     */
    snmp_reset_var_buffers( &var_saHpiDomainId );

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
int saHpiCtrlTable_can_activate(saHpiCtrlTable_context *undo_ctx,
                      saHpiCtrlTable_context *row_ctx,
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
int saHpiCtrlTable_can_deactivate(saHpiCtrlTable_context *undo_ctx,
                        saHpiCtrlTable_context *row_ctx,
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
int saHpiCtrlTable_can_delete(saHpiCtrlTable_context *undo_ctx,
                    saHpiCtrlTable_context *row_ctx,
                    netsnmp_request_group * rg)
{
    /*
     * probably shouldn't delete a row that we can't
     * deactivate.
     */
    if(saHpiCtrlTable_can_deactivate(undo_ctx,row_ctx,rg) != 1)
        return 0;
    
    /*
     * TODO: check for other deletion requirements here
     */
    return 1;
}

#ifdef saHpiCtrlTable_ROW_CREATION
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
 * returns a newly allocated saHpiCtrlTable_context
 *   structure if the specified indexes are not illegal
 * returns NULL for errors or illegal index values.
 */
saHpiCtrlTable_context *
saHpiCtrlTable_create_row( netsnmp_index* hdr)
{
    saHpiCtrlTable_context * ctx =
        SNMP_MALLOC_TYPEDEF(saHpiCtrlTable_context);
    if(!ctx)
        return NULL;
        
    /*
     * TODO: check indexes, if necessary.
     */
    if(saHpiCtrlTable_extract_index( ctx, hdr )) {
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
     ctx->saHpiCtrlMode = 0;
     ctx->saHpiCtrlState = 0;
     ctx->saHpiCtrlTextType = 0;
     ctx->saHpiCtrlTextLanguage = 0;
     ctx->saHpiCtrlText = 0;
    */

    return ctx;
}
#endif

/************************************************************
 * the *_duplicate row routine
 */
saHpiCtrlTable_context *
saHpiCtrlTable_duplicate_row( saHpiCtrlTable_context * row_ctx)
{
    saHpiCtrlTable_context * dup;

    if(!row_ctx)
        return NULL;

    dup = SNMP_MALLOC_TYPEDEF(saHpiCtrlTable_context);
    if(!dup)
        return NULL;
        
    if(saHpiCtrlTable_row_copy(dup,row_ctx)) {
        free(dup);
        dup = NULL;
    }

    return dup;
}

/************************************************************
 * the *_delete_row method is called to delete a row.
 */
netsnmp_index * saHpiCtrlTable_delete_row( saHpiCtrlTable_context * ctx )
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
void saHpiCtrlTable_set_reserve1( netsnmp_request_group *rg )
{
    saHpiCtrlTable_context *row_ctx =
            (saHpiCtrlTable_context *)rg->existing_row;
    saHpiCtrlTable_context *undo_ctx =
            (saHpiCtrlTable_context *)rg->undo_info;
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

        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
            rc = netsnmp_check_vb_type_and_size(var, ASN_INTEGER,
                                                sizeof(row_ctx->saHpiCtrlMode));
        break;

        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
            rc = netsnmp_check_vb_type_and_size(var, ASN_OCTET_STR,
                                                sizeof(row_ctx->saHpiCtrlState));
        break;

        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
            rc = netsnmp_check_vb_type_and_size(var, ASN_INTEGER,
                                                sizeof(row_ctx->saHpiCtrlTextType));
        break;

        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
            rc = netsnmp_check_vb_type_and_size(var, ASN_INTEGER,
                                                sizeof(row_ctx->saHpiCtrlTextLanguage));
        break;

        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
            rc = netsnmp_check_vb_type_and_size(var, ASN_OCTET_STR,
                                                sizeof(row_ctx->saHpiCtrlText));
        break;

        default: /** We shouldn't get here */
            rc = SNMP_ERR_GENERR;
            snmp_log(LOG_ERR, "unknown column in "
                     "saHpiCtrlTable_set_reserve1\n");
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

void saHpiCtrlTable_set_reserve2( netsnmp_request_group *rg )
{
    saHpiCtrlTable_context *row_ctx = (saHpiCtrlTable_context *)rg->existing_row;
    saHpiCtrlTable_context *undo_ctx = (saHpiCtrlTable_context *)rg->undo_info;
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

        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
                    /*
                     * TODO: routine to check valid values
                     *
                     * EXAMPLE:
                     *
                    * if ( *var->val.integer != XXX ) {
                *    rc = SNMP_ERR_INCONSISTENTVALUE;
                *    rc = SNMP_ERR_BADVALUE;
                * }
                */
        break;

        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
                    /*
                     * TODO: routine to check valid values
                     *
                     * EXAMPLE:
                     *
                    * if ( XXX_check_value( var->val.string, XXX ) ) {
                *    rc = SNMP_ERR_INCONSISTENTVALUE;
                *    rc = SNMP_ERR_BADVALUE;
                * }
                */
        break;

        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
                    /*
                     * TODO: routine to check valid values
                     *
                     * EXAMPLE:
                     *
                    * if ( *var->val.integer != XXX ) {
                *    rc = SNMP_ERR_INCONSISTENTVALUE;
                *    rc = SNMP_ERR_BADVALUE;
                * }
                */
        break;

        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
                    /*
                     * TODO: routine to check valid values
                     *
                     * EXAMPLE:
                     *
                    * if ( *var->val.integer != XXX ) {
                *    rc = SNMP_ERR_INCONSISTENTVALUE;
                *    rc = SNMP_ERR_BADVALUE;
                * }
                */
        break;

        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
                    /*
                     * TODO: routine to check valid values
                     *
                     * EXAMPLE:
                     *
                    * if ( XXX_check_value( var->val.string, XXX ) ) {
                *    rc = SNMP_ERR_INCONSISTENTVALUE;
                *    rc = SNMP_ERR_BADVALUE;
                * }
                */
        break;

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
void saHpiCtrlTable_set_action( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiCtrlTable_context *row_ctx = (saHpiCtrlTable_context *)rg->existing_row;
    saHpiCtrlTable_context *undo_ctx = (saHpiCtrlTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    int            row_err = 0;

    /*
     * TODO: loop through columns, copy varbind values
     * to context structure for the row.
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
            row_ctx->saHpiCtrlMode = *var->val.integer;
        break;

        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
            memcpy(row_ctx->saHpiCtrlState,var->val.string,var->val_len);
            row_ctx->saHpiCtrlState_len = var->val_len;
        break;

        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
            row_ctx->saHpiCtrlTextType = *var->val.integer;
        break;

        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
            row_ctx->saHpiCtrlTextLanguage = *var->val.integer;
        break;

        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
            memcpy(row_ctx->saHpiCtrlText,var->val.string,var->val_len);
            row_ctx->saHpiCtrlText_len = var->val_len;
        break;

        default: /** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
#if 0 /*TODO DMJ */
#ifndef saHpiCtrlTable_CAN_MODIFY_ACTIVE_ROW
    if( undo_ctx && RS_IS_ACTIVE(undo_ctx->saHpiDomainAlarmDelete) &&
        row_ctx && RS_IS_ACTIVE(row_ctx->saHpiDomainAlarmDelete) ) {
            row_err = 1;
    }
#endif

    /*
     * check activation/deactivation
     */
    row_err = netsnmp_table_array_check_row_status(&cb, rg,
                                  row_ctx ? &row_ctx->saHpiDomainAlarmDelete : NULL,
                                  undo_ctx ? &undo_ctx->saHpiDomainAlarmDelete : NULL);
#endif /*TODO DMJ */
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
void saHpiCtrlTable_set_commit( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiCtrlTable_context *row_ctx = (saHpiCtrlTable_context *)rg->existing_row;
    saHpiCtrlTable_context *undo_ctx = (saHpiCtrlTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
        break;

        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
        break;

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
void saHpiCtrlTable_set_free( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiCtrlTable_context *row_ctx = (saHpiCtrlTable_context *)rg->existing_row;
    saHpiCtrlTable_context *undo_ctx = (saHpiCtrlTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
        break;

        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
        break;

        default: /** We shouldn't get here */
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
void saHpiCtrlTable_set_undo( netsnmp_request_group *rg )
{
    netsnmp_variable_list *var;
    saHpiCtrlTable_context *row_ctx = (saHpiCtrlTable_context *)rg->existing_row;
    saHpiCtrlTable_context *undo_ctx = (saHpiCtrlTable_context *)rg->undo_info;
    netsnmp_request_group_item *current;

    /*
     * loop through columns
     */
    for( current = rg->list; current; current = current->next ) {

        var = current->ri->requestvb;

        switch(current->tri->colnum) {

        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
        break;

        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
        break;

        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
        break;

        default: /** We shouldn't get here */
            netsnmp_assert(0); /** why wasn't this caught in reserve1? */
        }
    }

    /*
     * done with all the columns. Could check row related
     * requirements here.
     */
}

#endif /** saHpiCtrlTable_SET_HANDLING */


/************************************************************
 *
 * Initialize the saHpiCtrlTable table by defining its contents and how it's structured
 */
void
initialize_table_saHpiCtrlTable(void)
{
    netsnmp_table_registration_info *table_info;

    if(my_handler) {
        snmp_log(LOG_ERR, "initialize_table_saHpiCtrlTable_handler called again\n");
        return;
    }

    memset(&cb, 0x00, sizeof(cb));

    /** create the table structure itself */
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);

    /* if your table is read only, it's easiest to change the
       HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY */
    my_handler = netsnmp_create_handler_registration("saHpiCtrlTable",
                                             netsnmp_table_array_helper_handler,
                                             saHpiCtrlTable_oid,
                                             saHpiCtrlTable_oid_len,
                                             HANDLER_CAN_RWRITE);
            
    if (!my_handler || !table_info) {
        snmp_log(LOG_ERR, "malloc failed in "
                 "initialize_table_saHpiCtrlTable_handler\n");
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
        /** index: saHpiDomainId */
        netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
        /** index: saHpiResourceId */
        netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);
        /** index: saHpiCtrlNum */
        netsnmp_table_helper_add_index(table_info, ASN_UNSIGNED);

    table_info->min_column = saHpiCtrlTable_COL_MIN;
    table_info->max_column = saHpiCtrlTable_COL_MAX;

    /***************************************************
     * registering the table with the master agent
     */
    cb.get_value = saHpiCtrlTable_get_value;
    cb.container = netsnmp_container_find("saHpiCtrlTable_primary:"
                                          "saHpiCtrlTable:"
                                          "table_container");
#ifdef saHpiCtrlTable_IDX2
    netsnmp_container_add_index(cb.container,
                                netsnmp_container_find("saHpiCtrlTable_secondary:"
                                                       "saHpiCtrlTable:"
                                                       "table_container"));
    cb.container->next->compare = saHpiCtrlTable_cmp;
#endif
#ifdef saHpiCtrlTable_SET_HANDLING
    cb.can_set = 1;
#ifdef saHpiCtrlTable_ROW_CREATION
    cb.create_row = (UserRowMethod*)saHpiCtrlTable_create_row;
#endif
    cb.duplicate_row = (UserRowMethod*)saHpiCtrlTable_duplicate_row;
    cb.delete_row = (UserRowMethod*)saHpiCtrlTable_delete_row;
    cb.row_copy = (Netsnmp_User_Row_Operation *)saHpiCtrlTable_row_copy;

    cb.can_activate = (Netsnmp_User_Row_Action *)saHpiCtrlTable_can_activate;
    cb.can_deactivate = (Netsnmp_User_Row_Action *)saHpiCtrlTable_can_deactivate;
    cb.can_delete = (Netsnmp_User_Row_Action *)saHpiCtrlTable_can_delete;

    cb.set_reserve1 = saHpiCtrlTable_set_reserve1;
    cb.set_reserve2 = saHpiCtrlTable_set_reserve2;
    cb.set_action = saHpiCtrlTable_set_action;
    cb.set_commit = saHpiCtrlTable_set_commit;
    cb.set_free = saHpiCtrlTable_set_free;
    cb.set_undo = saHpiCtrlTable_set_undo;
#endif
    DEBUGMSGTL(("initialize_table_saHpiCtrlTable",
                "Registering table saHpiCtrlTable "
                "as a table array\n"));
    netsnmp_table_container_register(my_handler, table_info, &cb,
                                     cb.container, 1);
}

/************************************************************
 * saHpiCtrlTable_get_value
 *
 * This routine is called for get requests to copy the data
 * from the context to the varbind for the request. If the
 * context has been properly maintained, you don't need to
 * change in code in this fuction.
 */
int saHpiCtrlTable_get_value(
            netsnmp_request_info *request,
            netsnmp_index *item,
            netsnmp_table_request_info *table_info )
{
    netsnmp_variable_list *var = request->requestvb;
    saHpiCtrlTable_context *context = (saHpiCtrlTable_context *)item;

    switch(table_info->colnum) {

        case COLUMN_SAHPICTRLNUM:
            /** SaHpiInstrumentId = ASN_UNSIGNED */
            snmp_set_var_typed_value(var, ASN_UNSIGNED,
                         (char*)&context->saHpiCtrlNum,
                         sizeof(context->saHpiCtrlNum) );
        break;
    
        case COLUMN_SAHPICTRLOUTPUTTYPE:
            /** INTEGER = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlOutputType,
                         sizeof(context->saHpiCtrlOutputType) );
        break;
    
        case COLUMN_SAHPICTRLTYPE:
            /** INTEGER = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlType,
                         sizeof(context->saHpiCtrlType) );
        break;
    
        case COLUMN_SAHPICTRLMODE:
            /** INTEGER = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlMode,
                         sizeof(context->saHpiCtrlMode) );
        break;
    
        case COLUMN_SAHPICTRLREADONLY:
            /** TruthValue = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlReadOnly,
                         sizeof(context->saHpiCtrlReadOnly) );
        break;
    
        case COLUMN_SAHPICTRLWRITEONLY:
            /** TruthValue = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlWriteOnly,
                         sizeof(context->saHpiCtrlWriteOnly) );
        break;
    
        case COLUMN_SAHPICTRLSTATE:
            /** OCTETSTR = ASN_OCTET_STR */
            snmp_set_var_typed_value(var, ASN_OCTET_STR,
                         (char*)&context->saHpiCtrlState,
                         context->saHpiCtrlState_len );
        break;
    
        case COLUMN_SAHPICTRLDATA:
            /** OCTETSTR = ASN_OCTET_STR */
            snmp_set_var_typed_value(var, ASN_OCTET_STR,
                         (char*)&context->saHpiCtrlData,
                         context->saHpiCtrlData_len );
        break;
    
        case COLUMN_SAHPICTRLOEM:
            /** UNSIGNED32 = ASN_UNSIGNED */
            snmp_set_var_typed_value(var, ASN_UNSIGNED,
                         (char*)&context->saHpiCtrlOem,
                         sizeof(context->saHpiCtrlOem) );
        break;
    
        case COLUMN_SAHPICTRLTEXTTYPE:
            /** SaHpiTextType = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlTextType,
                         sizeof(context->saHpiCtrlTextType) );
        break;
    
        case COLUMN_SAHPICTRLTEXTLANGUAGE:
            /** SaHpiTextLanguage = ASN_INTEGER */
            snmp_set_var_typed_value(var, ASN_INTEGER,
                         (char*)&context->saHpiCtrlTextLanguage,
                         sizeof(context->saHpiCtrlTextLanguage) );
        break;
    
        case COLUMN_SAHPICTRLTEXT:
            /** OCTETSTR = ASN_OCTET_STR */
            snmp_set_var_typed_value(var, ASN_OCTET_STR,
                         (char*)&context->saHpiCtrlText,
                         context->saHpiCtrlText_len );
        break;
    
        case COLUMN_SAHPICTRLRDR:
            /** RowPointer = ASN_OBJECT_ID */
            snmp_set_var_typed_value(var, ASN_OBJECT_ID,
                         (char*)&context->saHpiCtrlRDR,
                         context->saHpiCtrlRDR_len );
        break;
    
    default: /** We shouldn't get here */
        snmp_log(LOG_ERR, "unknown column in "
                 "saHpiCtrlTable_get_value\n");
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

/************************************************************
 * saHpiCtrlTable_get_by_idx
 */
const saHpiCtrlTable_context *
saHpiCtrlTable_get_by_idx(netsnmp_index * hdr)
{
    return (const saHpiCtrlTable_context *)
        CONTAINER_FIND(cb.container, hdr );
}


