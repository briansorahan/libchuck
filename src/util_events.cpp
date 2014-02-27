#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <map>
#include <string>
#include <vector>

#include <chuck_def.h>
#include <chuck_dl.h>
#include <chuck_oo.h>
#include <chuck_type.h>
#include <util_events.h>
#include <util_thread.h>

// libchuck
#include <chuck.h>

using std::map;
using std::string;
using std::vector;

using chuck::IntReceiver;
using chuck::FloatReceiver;
using chuck::StringReceiver;

class EventsImpl : public Events {
public:
    EventsImpl() {}

    IntEvent * receiveIntFrom(const char * channel);
    FloatEvent * receiveFloatFrom(const char * channel);
    StringEvent * receiveStringFrom(const char * channel);

    Events & sendTo(const char * channel, t_CKINT intval);
    Events & sendTo(const char * channel, t_CKFLOAT floatval);
    Events & sendTo(const char * channel, const char * stringval);

    void LockIntEvents();
    void LockFloatEvents();
    void LockStringEvents();

    void UnlockIntEvents();
    void UnlockFloatEvents();
    void UnlockStringEvents();

    void LockIntEvs();
    void LockFloatEvs();
    void LockStringEvs();

    void UnlockIntEvs();
    void UnlockFloatEvs();
    void UnlockStringEvs();

    void Clear();

    void RegisterIntListener(const char * channel, IntReceiver * cb);
    void RegisterFloatListener(const char * channel, FloatReceiver * cb);
    void RegisterStringListener(const char * channel, StringReceiver * cb);

private:
    XMutex m_mutex_intevents;
    XMutex m_mutex_floatevents;
    XMutex m_mutex_stringevents;

    map< string, IntEvent * > intevents;
    map< string, FloatEvent * > floatevents;
    map< string, StringEvent * > stringevents;

    // Callbacks and their associated mutexes
    map< string, vector< IntReceiver * > > intevs;
    XMutex intevs_mutex;

    map< string, vector< FloatReceiver * > > floatevs;
    XMutex floatevs_mutex;

    map< string, vector< StringReceiver * > > stringevs;
    XMutex stringevs_mutex;

};

Events * Events::GetInstance() {
    static Events * evs = new EventsImpl;
    return evs;
}

IntEvent * EventsImpl::receiveIntFrom(const char * channel) {
    IntEvent * ev = intevents[channel];

    if (NULL == ev) {
        this->LockIntEvents();
        ev = new IntEvent;
        intevents[channel] = ev;
        this->UnlockIntEvents();
    }

    return ev;
}

FloatEvent * EventsImpl::receiveFloatFrom(const char * channel) {
    FloatEvent * ev = floatevents[channel];

    if (NULL == ev) {
        this->LockFloatEvents();
        ev = new FloatEvent;
        floatevents[channel] = ev;
        this->UnlockFloatEvents();
    }

    return ev;
}

StringEvent * EventsImpl::receiveStringFrom(const char * channel) {
    StringEvent * ev = stringevents[channel];

    if (NULL == ev) {
        this->LockStringEvents();
        ev = new StringEvent;
        stringevents[channel] = ev;
        this->UnlockStringEvents();
    }

    return ev;
}

Events & EventsImpl::sendTo(const char * channel, t_CKINT val) {
    IntEvent * ev = intevents[channel];

    if (NULL != ev) {
        // broadcast the chuck event
        this->LockIntEvents();
        ev->val = val;
        ev->chuckEvent->broadcast();
        this->UnlockIntEvents();
    }

    // copy the vector with the mutex acquired
    this->LockIntEvs();
    vector< IntReceiver * > copy = intevs[channel];
    this->UnlockIntEvs();

    // trigger the callbacks
    for (vector< IntReceiver * >::iterator it = copy.begin();
         it != copy.end(); it++) {
        (*it)->receive(val);
    }

    return *this;
}

Events & EventsImpl::sendTo(const char * channel, t_CKFLOAT val) {
    FloatEvent * ev = floatevents[channel];

    if (NULL != ev) {
        // broadcast the chuck event
        this->LockFloatEvents();
        ev->val = val;
        ev->chuckEvent->broadcast();
        this->UnlockFloatEvents();

    }

    // copy the vector with the mutex acquired
    this->LockFloatEvs();
    vector< FloatReceiver * > copy = floatevs[channel];
    this->UnlockFloatEvs();

    // trigger the callbacks
    for (vector< FloatReceiver * >::iterator it = copy.begin();
         it != copy.end(); it++) {
        (*it)->receive(val);
    }

    return *this;
}

Events & EventsImpl::sendTo(const char * channel, const char * val) {
    StringEvent * ev = stringevents[channel];

    if (NULL != ev) {
        // broadcast the chuck event
        string s(val);
        this->LockStringEvents();
        ev->val = new Chuck_String(s);
        ev->chuckEvent->broadcast();
        this->UnlockStringEvents();
    }

    // copy the vector with the mutex acquired
    this->LockStringEvs();
    vector< StringReceiver * > copy = stringevs[channel];
    this->UnlockStringEvs();

    // trigger the callbacks
    for (vector< StringReceiver * >::iterator it = copy.begin();
         it != copy.end(); it++) {
        (*it)->receive(val);
    }

    return *this;
}

/*
 * events synchronization
 */

void EventsImpl::LockIntEvents() {
    m_mutex_intevents.acquire();
}

void EventsImpl::LockFloatEvents() {
    m_mutex_floatevents.acquire();
}

void EventsImpl::LockStringEvents() {
    m_mutex_stringevents.acquire();
}

void EventsImpl::UnlockIntEvents() {
    m_mutex_intevents.release();
}

void EventsImpl::UnlockFloatEvents() {
    m_mutex_floatevents.release();
}

void EventsImpl::UnlockStringEvents() {
    m_mutex_stringevents.release();
}

/*
 * callbacks synchronization
 */

void EventsImpl::LockIntEvs() {
    intevs_mutex.acquire();
}

void EventsImpl::LockFloatEvs() {
    floatevs_mutex.acquire();
}

void EventsImpl::LockStringEvs() {
    stringevs_mutex.acquire();
}

void EventsImpl::UnlockIntEvs() {
    intevs_mutex.release();
}

void EventsImpl::UnlockFloatEvs() {
    floatevs_mutex.release();
}

void EventsImpl::UnlockStringEvs() {
    stringevs_mutex.release();
}

void EventsImpl::Clear() {
    LockIntEvents();
    intevents.clear();
    UnlockIntEvents();

    LockFloatEvents();
    floatevents.clear();
    UnlockFloatEvents();

    LockStringEvents();
    stringevents.clear();
    UnlockStringEvents();

    LockIntEvs();
    intevs.clear();
    UnlockIntEvs();

    LockFloatEvs();
    floatevs.clear();
    UnlockFloatEvs();

    LockStringEvs();
    stringevs.clear();
    UnlockStringEvs();
}

void EventsImpl::RegisterIntListener(const char * channel, IntReceiver * cb) {
    LockIntEvs();
    intevs[channel].push_back(cb);
    UnlockIntEvs();
}

void EventsImpl::RegisterFloatListener(const char * channel, FloatReceiver * cb) {
    LockFloatEvs();
    floatevs[channel].push_back(cb);
    UnlockFloatEvs();
}

void EventsImpl::RegisterStringListener(const char * channel, StringReceiver * cb) {
    LockStringEvs();
    stringevs[channel].push_back(cb);
    UnlockStringEvs();
}
