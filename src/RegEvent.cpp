#include <assert.h>

#include <chuck_def.h>
#include <chuck_dl.h>
#include <chuck_oo.h>

#include "RegEvent.h"

void RegEvent::signal() {
    m_event->signal();
}

void RegEvent::broadcast() {
    m_event->broadcast();
}

void RegEvent::wait(Chuck_VM_Shred * shred, Chuck_VM * vm) {
    m_event->wait(shred, vm);
}

t_CKBOOL RegEvent::remove(Chuck_VM_Shred * shred) {
    return m_event->remove(shred);
}

void RegEvent::queue_broadcast(CBufferSimple * event_buffer) {
    m_event->queue_broadcast(event_buffer);
}

static t_CKUINT regevent_offset_data = 0;

CK_DLL_CTOR( regevent_ctor ) {
    OBJ_MEMBER_UINT(SELF, regevent_offset_data) = (t_CKUINT) new RegEvent;
}

CK_DLL_DTOR( regevent_dtor ) {
    delete (RegEvent *) OBJ_MEMBER_UINT(SELF, regevent_offset_data);
    OBJ_MEMBER_UINT(SELF, regevent_offset_data) = 0;
}

CK_DLL_MFUN( regevent_signal ) {
    RegEvent * re = (RegEvent *) OBJ_MEMBER_UINT(SELF, regevent_offset_data);
    re->signal();
}

CK_DLL_MFUN( regevent_broadcast ) {
    RegEvent * re = (RegEvent *) OBJ_MEMBER_UINT(SELF, regevent_offset_data);
    re->broadcast();
}

CK_DLL_MFUN( regevent_wait ) {
    // RegEvent * re = (RegEvent *) OBJ_MEMBER_UINT(SELF, regevent_offset_data);
    // re->wait(shred???, vm???);
    assert(FALSE);
}

CK_DLL_MFUN( regevent_can_wait ) {
    RETURN->v_int = TRUE;
}

