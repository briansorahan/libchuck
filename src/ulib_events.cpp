/*
 * Extend Chuck's Event type to hold int, float, and string values.
 */

#include <assert.h>

#include <chuck_def.h>
#include <chuck_dl.h>
#include <chuck_instr.h>
#include <chuck_oo.h>
#include <chuck_type.h>

#include "ulib_events.h"
#include "util_events.h"

/*
 * Global Event map.
 */
static Events * g_Events = Events::GetInstance();

/*
 * Offsets and types.
 */
static t_CKUINT intevent_offset_data = 0;
static t_CKUINT floatevent_offset_data = 0;
static t_CKUINT stringevent_offset_data = 0;
static Chuck_Type * type_IntEvent = NULL;
static Chuck_Type * type_FloatEvent = NULL;
static Chuck_Type * type_StringEvent = NULL;

/*
 * Initialization functions.
 * For use in DLL_QUERY.
 */
static t_CKBOOL initialize_IntEvent( Chuck_Env * env ) {
    Chuck_DL_Func * func = NULL;

    if (! type_engine_import_class_begin( env,
                                          "IntEvent",
                                          "Event",
                                          env->global(), 
                                          intevent_ctor,
                                          intevent_dtor)) {
        return FALSE;
    }

    intevent_offset_data = \
        type_engine_import_mvar( env, "int", "@IntEvent_Data", FALSE );
    if (intevent_offset_data == CK_INVALID_OFFSET) goto error;

    // store type value
    type_IntEvent = env->class_def;

    func = make_new_mfun( "int", "val", intevent_ctrl_val );
    func->add_arg( "int", "val" );
    if (! type_engine_import_mfun( env, func )) goto error;

    func = make_new_mfun( "int", "val", intevent_cget_val );
    if (! type_engine_import_mfun( env, func )) goto error;

 error:

    if (! type_engine_import_class_end( env )) return FALSE;

    return TRUE;
}

static t_CKBOOL initialize_FloatEvent( Chuck_Env * env ) {
    Chuck_DL_Func * func = NULL;

    if (! type_engine_import_class_begin( env, "FloatEvent", "Event",
                                          env->global(),
                                          floatevent_ctor,
                                          floatevent_dtor)) {
        return FALSE;
    }

    floatevent_offset_data = \
        type_engine_import_mvar( env, "int", "@FloatEvent_Data", FALSE );
    if (floatevent_offset_data == CK_INVALID_OFFSET) goto error;

    /*
     * store type value
     */
    type_FloatEvent = env->class_def;

    func = make_new_mfun( "float", "val", floatevent_ctrl_val );
    func->add_arg( "float", "val" );
    if (! type_engine_import_mfun( env, func )) goto error;

    func = make_new_mfun( "float", "val", floatevent_cget_val );
    if (! type_engine_import_mfun( env, func )) goto error;

 error:

    if (! type_engine_import_class_end( env )) return FALSE;

    return TRUE;
}

static t_CKBOOL initialize_StringEvent( Chuck_Env * env ) {
    Chuck_DL_Func * func = NULL;

    if (! type_engine_import_class_begin( env, "StringEvent", "Event",
                                          env->global(),
                                          stringevent_ctor,
                                          stringevent_dtor)) {
        return FALSE;
    }

    stringevent_offset_data = \
        type_engine_import_mvar( env, "int", "@StringEvent_Data", FALSE );
    if (stringevent_offset_data == CK_INVALID_OFFSET) goto error;

    /*
     * store type value
     */
    type_StringEvent = env->class_def;

    func = make_new_mfun( "string", "val", stringevent_ctrl_val );
    func->add_arg( "string", "val" );
    if (! type_engine_import_mfun( env, func )) goto error;

    func = make_new_mfun( "string", "val", stringevent_cget_val );
    if (! type_engine_import_mfun( env, func )) goto error;

 error:

    if (! type_engine_import_class_end( env )) return FALSE;

    return TRUE;
}

/*
 * Add types to chuck.
 */
DLL_QUERY events_query( Chuck_DL_Query * QUERY ) {
    Chuck_Env * env = Chuck_Env::instance();

    if (! initialize_IntEvent( env )) return FALSE;
    if (! initialize_FloatEvent( env )) return FALSE;
    if (! initialize_StringEvent( env )) return FALSE;

    QUERY->begin_class( QUERY, "Events", "Object" );
    QUERY->setname( QUERY, "Events" );

    /*
     * Static receive functions.
     */
    QUERY->add_sfun( QUERY,
                     receiveIntFrom_impl,  // implementation
                     "IntEvent",           // return type
                     "receiveIntFrom" );   // name
    QUERY->add_arg( QUERY, "string", "channel" );


    QUERY->add_sfun( QUERY,
                     receiveFloatFrom_impl,  // implementation
                     "FloatEvent",           // return type
                     "receiveFloatFrom" );   // name
    QUERY->add_arg( QUERY, "string", "channel" );


    QUERY->add_sfun( QUERY,
                     receiveStringFrom_impl,  // implementation
                     "StringEvent",           // return type
                     "receiveStringFrom" );   // name
    QUERY->add_arg( QUERY, "string", "channel" );

    /*
     * Static send functions.
     */
    QUERY->add_sfun( QUERY,
                     sendIntTo_impl,    // implementation
                     "void",            // return type
                     "sendIntTo" );     // name
    QUERY->add_arg( QUERY, "string", "channel" );
    QUERY->add_arg( QUERY, "int", "val" );


    QUERY->add_sfun( QUERY,
                     sendFloatTo_impl,  // implementation
                     "void",            // return type
                     "sendFloatTo" );   // name
    QUERY->add_arg( QUERY, "string", "channel" );
    QUERY->add_arg( QUERY, "float", "val" );


    QUERY->add_sfun( QUERY,
                     sendStringTo_impl,  // implementation
                     "void",             // return type
                     "sendStringTo" );   // name
    QUERY->add_arg( QUERY, "string", "channel" );
    QUERY->add_arg( QUERY, "string", "val" );

    QUERY->end_class( QUERY );
}

/*
 * Ctor's, Dtor's, and member functions.
 */
CK_DLL_CTOR( intevent_ctor ) {
    IntEvent * iev = new IntEvent;
    iev->SELF = SELF;
    OBJ_MEMBER_UINT(SELF, intevent_offset_data) = (t_CKUINT) iev;
}

CK_DLL_DTOR( intevent_dtor ) {
    delete (IntEvent *) OBJ_MEMBER_UINT(SELF, intevent_offset_data);
    OBJ_MEMBER_UINT(SELF, intevent_offset_data) = 0;
}

CK_DLL_CTRL( intevent_ctrl_val ) {
    IntEvent * ev = (IntEvent *) OBJ_MEMBER_UINT(SELF, intevent_offset_data);
    t_CKINT val = GET_CK_INT(ARGS);
    RETURN->v_int = ev->val = val;
}

CK_DLL_CGET( intevent_cget_val ) {
    IntEvent * ev = (IntEvent *) OBJ_MEMBER_UINT(SELF, intevent_offset_data);
    RETURN->v_int = ev->val;
}

CK_DLL_CTOR( floatevent_ctor ) {
    OBJ_MEMBER_UINT(SELF, intevent_offset_data) = (t_CKUINT) new FloatEvent;
}

CK_DLL_DTOR( floatevent_dtor ) {
    delete (FloatEvent *) OBJ_MEMBER_UINT(SELF, floatevent_offset_data);
    OBJ_MEMBER_UINT(SELF, floatevent_offset_data) = 0;
}

CK_DLL_CTRL( floatevent_ctrl_val ) {
    FloatEvent * ev = (FloatEvent *) OBJ_MEMBER_UINT(SELF, floatevent_offset_data);
    t_CKFLOAT val = GET_CK_FLOAT(ARGS);
    RETURN->v_float = ev->val = val;
}

CK_DLL_CGET( floatevent_cget_val ) {
    FloatEvent * ev = (FloatEvent *) OBJ_MEMBER_UINT(SELF, floatevent_offset_data);
    RETURN->v_float = ev->val;
}

CK_DLL_CTOR( stringevent_ctor ) {
    OBJ_MEMBER_UINT(SELF, stringevent_offset_data) = (t_CKUINT) new StringEvent;
}

CK_DLL_DTOR( stringevent_dtor ) {
    delete (StringEvent *) OBJ_MEMBER_UINT(SELF, stringevent_offset_data);
    OBJ_MEMBER_UINT(SELF, stringevent_offset_data) = 0;
}

CK_DLL_CTRL( stringevent_ctrl_val ) {
    StringEvent * ev = (StringEvent *) OBJ_MEMBER_UINT(SELF, stringevent_offset_data);
    Chuck_String * val = GET_CK_STRING(ARGS);
    RETURN->v_string = ev->val = val;
}

CK_DLL_CGET( stringevent_cget_val ) {
    StringEvent * ev = (StringEvent *) OBJ_MEMBER_UINT(SELF, stringevent_offset_data);
    RETURN->v_string = ev->val;
}

/*
 * Static receive functions.
 */
CK_DLL_SFUN( receiveIntFrom_impl ) {
    Chuck_String * ck_channel_name = GET_CK_STRING(ARGS);
    const char * channel = ck_channel_name->str.c_str();

    IntEvent * iev = g_Events->receiveIntFrom(channel);
    Chuck_Event * new_event_obj = new Chuck_Event;

    initialize_object( new_event_obj, type_IntEvent );
    iev->SELF = new_event_obj;
    iev->chuckEvent = new_event_obj;
    OBJ_MEMBER_UINT( new_event_obj, intevent_offset_data ) = (t_CKUINT) iev;

    RETURN->v_object = new_event_obj;
}

CK_DLL_SFUN( receiveFloatFrom_impl ) {
    Chuck_String * ck_channel_name = GET_CK_STRING(ARGS);
    const char * channel = ck_channel_name->str.c_str();

    FloatEvent * fev = g_Events->receiveFloatFrom(channel);
    Chuck_Event * new_event_obj = new Chuck_Event;

    initialize_object( new_event_obj, type_FloatEvent );
    fev->SELF = new_event_obj;
    fev->chuckEvent = new_event_obj;
    OBJ_MEMBER_UINT( new_event_obj, floatevent_offset_data ) = (t_CKUINT) fev;

    RETURN->v_object = new_event_obj;
}

CK_DLL_SFUN( receiveStringFrom_impl ) {
    Chuck_String * ck_channel_name = GET_CK_STRING(ARGS);
    const char * channel = ck_channel_name->str.c_str();

    StringEvent * sev = g_Events->receiveStringFrom(channel);
    Chuck_Event * new_event_obj = new Chuck_Event;

    initialize_object( new_event_obj, type_StringEvent );
    sev->SELF = new_event_obj;
    sev->chuckEvent = new_event_obj;
    OBJ_MEMBER_UINT( new_event_obj, stringevent_offset_data ) = (t_CKUINT) sev;

    RETURN->v_object = new_event_obj;
}

/*
 * Static send functions.
 */
CK_DLL_SFUN( sendIntTo_impl ) {
    Chuck_String * ck_channel_name = GET_NEXT_STRING(ARGS);
    t_CKINT val = GET_NEXT_INT(ARGS);

    const char * channel = ck_channel_name->str.c_str();
    g_Events->sendTo(channel, val);
}

CK_DLL_SFUN( sendFloatTo_impl ) {
    Chuck_String * ck_channel_name = GET_NEXT_STRING(ARGS);
    t_CKFLOAT val = GET_NEXT_FLOAT(ARGS);

    const char * channel = ck_channel_name->str.c_str();
    g_Events->sendTo(channel, val);
}

CK_DLL_SFUN( sendStringTo_impl ) {
    Chuck_String * ck_channel_name = GET_NEXT_STRING(ARGS);
    Chuck_String * val = GET_NEXT_STRING(ARGS);

    const char * channel = ck_channel_name->str.c_str();
    g_Events->sendTo(channel, val->str.c_str());
}

