#ifndef UGEN_CLIP_H
#define UGEN_CLIP_H

#include "chuck_dl.h"

DLL_QUERY
clip_query( Chuck_DL_Query * QUERY );

CK_DLL_CTOR( clip_ctor );
CK_DLL_DTOR( clip_dtor );

CK_DLL_TICK( clip_tick );

CK_DLL_CTRL( clip_ctrl_max );
CK_DLL_CGET( clip_cget_max );

CK_DLL_CTRL( clip_ctrl_min );
CK_DLL_CGET( clip_cget_min );

#endif
