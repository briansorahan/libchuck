#include "ugen_clip.h"
#include "chuck_type.h"
#include "chuck_ugen.h"
#include "chuck_vm.h"
#include "chuck_globals.h"

static t_CKUINT clip_offset_data = 0;

struct ClipData {
    SAMPLE min;
    SAMPLE max;
    ClipData() { max = 1.0f; min = -1.0f; }
};

DLL_QUERY
clip_query( Chuck_DL_Query * QUERY ) {
    Chuck_Env * env = Chuck_Env::instance();
    Chuck_DL_Func * func = NULL;

    if (! type_engine_import_ugen_begin(env, "Clip", "UGen", env->global(),
                                        clip_ctor, clip_dtor, clip_tick, NULL)) {
        return FALSE;
    }

    // add member variable
    clip_offset_data = type_engine_import_mvar( env, "int", "@clip_data", FALSE );
    if ( clip_offset_data == CK_INVALID_OFFSET ) {
        goto error;
    }

    // add ctrl:max
    func = make_new_mfun( "float", "max", clip_ctrl_max );
    func->add_arg( "float", "max" );
    if (! type_engine_import_mfun(env, func)) {
        goto error;
    }

    // add cget:max
    func = make_new_mfun( "float", "max", clip_cget_max );
    if (! type_engine_import_mfun(env, func)) {
        goto error;
    }

    // add ctrl:min
    func = make_new_mfun( "float", "min", clip_ctrl_min );
    func->add_arg( "float", "min" );
    if (! type_engine_import_mfun(env, func)) {
        goto error;
    }

    // add cget:min
    func = make_new_mfun( "float", "min", clip_cget_min );
    if (! type_engine_import_mfun(env, func)) {
        goto error;
    }

    // end import
    if (! type_engine_import_class_end(env)) {
        return FALSE;
    }

    return TRUE;

 error:
    // end import
    if (! type_engine_import_class_end(env)) {
        return FALSE;
    }

    return FALSE;
}

CK_DLL_CTOR( clip_ctor ) {
    // return data to be used later
    OBJ_MEMBER_UINT( SELF, clip_offset_data ) = (t_CKUINT) new ClipData;
}

CK_DLL_DTOR( clip_dtor ) {
    delete (ClipData *) OBJ_MEMBER_UINT( SELF, clip_offset_data );
    OBJ_MEMBER_UINT( SELF, clip_offset_data ) = 0;
}

CK_DLL_TICK( clip_tick ) {
    ClipData * d = (ClipData *) OBJ_MEMBER_UINT( SELF, clip_offset_data );
    *out = in > d->max ? d->max : (in < d->min ? d->min : in);
    return TRUE;
}

CK_DLL_CTRL( clip_ctrl_max ) {
    ClipData * d = (ClipData *) OBJ_MEMBER_UINT( SELF, clip_offset_data );
    d->max = (SAMPLE) GET_CK_FLOAT(ARGS);
    RETURN->v_float = (t_CKFLOAT)(d->max);
}

CK_DLL_CGET( clip_cget_max ) {
    ClipData * d = (ClipData *) OBJ_MEMBER_UINT( SELF, clip_offset_data );
    RETURN->v_float = (t_CKFLOAT)(d->max);
}

CK_DLL_CTRL( clip_ctrl_min ) {
    ClipData * d = (ClipData *) OBJ_MEMBER_UINT( SELF, clip_offset_data );
    d->min = (SAMPLE) GET_CK_FLOAT(ARGS);
    RETURN->v_float = (t_CKFLOAT)(d->min);
}

CK_DLL_CGET( clip_cget_min ) {
    ClipData * d = (ClipData *) OBJ_MEMBER_UINT( SELF, clip_offset_data );
    RETURN->v_float = (t_CKFLOAT)(d->min);
}
