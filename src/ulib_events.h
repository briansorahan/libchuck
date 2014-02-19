/*
 * Send and receive events.
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <map>
#include <string>

#include <chuck_def.h>
#include <chuck_dl.h>
#include <chuck_type.h>

#include "util_events.h"

DLL_QUERY events_query( Chuck_DL_Query * query );

CK_DLL_CTOR( intevent_ctor );
CK_DLL_DTOR( intevent_dtor );
CK_DLL_CTRL( intevent_ctrl_val );
CK_DLL_CGET( intevent_cget_val );

CK_DLL_CTOR( floatevent_ctor );
CK_DLL_DTOR( floatevent_dtor );
CK_DLL_CTRL( floatevent_ctrl_val );
CK_DLL_CGET( floatevent_cget_val );

CK_DLL_CTOR( stringevent_ctor );
CK_DLL_DTOR( stringevent_dtor );
CK_DLL_CTRL( stringevent_ctrl_val );
CK_DLL_CGET( stringevent_cget_val );

CK_DLL_SFUN( receiveIntFrom_impl );
CK_DLL_SFUN( receiveFloatFrom_impl );
CK_DLL_SFUN( receiveStringFrom_impl );

CK_DLL_SFUN( sendIntTo_impl );
CK_DLL_SFUN( sendFloatTo_impl );
CK_DLL_SFUN( sendStringTo_impl );

#endif // __EVENTS_H__
