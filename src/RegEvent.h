/*
 * Extend Chuck's builtin Event class to include named events that
 * have 
 */

#ifndef __REGEVENT_H__
#define __REGEVENT_H__

#include <string>

#include <chuck_def.h>
#include <chuck_dl.h>
// #include <chuck_oo.h>

using std::string;

class RegEvent {
public:
    static t_CKUINT our_can_wait;

    RegEvent() {
        m_event = new Chuck_Event;
    }

    ~RegEvent() {
        SAFE_DELETE(m_event);
    }

    void signal();
    void broadcast();
    void wait(Chuck_VM_Shred * shred, Chuck_VM * vm);
    t_CKBOOL remove(Chuck_VM_Shred * shred);
    // internal
    void queue_broadcast(CBufferSimple * event_buffer = NULL);
private:
    Chuck_Event * m_event;
    string name;
    // values
    t_CKINT intval;
    t_CKDOUBLE doubleval;
    Chuck_String strval;
};

// static initialization
t_CKUINT RegEvent::our_can_wait = 0;

CK_DLL_CTOR( regevent_ctor );
CK_DLL_DTOR( regevent_dtor );
CK_DLL_MFUN( regevent_signal );
CK_DLL_MFUN( regevent_broadcast );
CK_DLL_MFUN( regevent_wait );
CK_DLL_MFUN( regevent_can_wait );

#endif // __REGEVENT_H__
