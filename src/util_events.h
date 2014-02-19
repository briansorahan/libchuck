/*
 * Extend Chuck's builtin Event class to include named events that
 * have int, float, and string vals.
 */

#ifndef __UTIL_EVENTS_H__
#define __UTIL_EVENTS_H__

#include <chuck_def.h>
#include <chuck_oo.h>
#include <chuck.h>

using chuck::IntReceiver;
using chuck::FloatReceiver;
using chuck::StringReceiver;

class IntEvent : public Chuck_Event {
public:
    IntEvent() : SELF(NULL), chuckEvent(NULL), val(0) {}
    virtual ~IntEvent() {}

    Chuck_Object * SELF;
    Chuck_Event * chuckEvent;
    t_CKINT val;
};

class FloatEvent : public Chuck_Event {
public:
    FloatEvent() : SELF(NULL), chuckEvent(NULL), val(0.0) {}
    virtual ~FloatEvent() {}

    Chuck_Object * SELF;
    Chuck_Event * chuckEvent;
    t_CKFLOAT val;
};

class StringEvent : public Chuck_Event {
public:
    StringEvent() : SELF(NULL), chuckEvent(NULL), val(NULL) {}
    virtual ~StringEvent() {}

    Chuck_Object * SELF;
    Chuck_Event * chuckEvent;
    Chuck_String * val;
};

/*
 * Global Event map which makes it easy to send
 * int, float, and string values between shreds using named
 * channels.
 */
class Events {
public:

    virtual IntEvent * receiveIntFrom(const char * channel) = 0;
    virtual FloatEvent * receiveFloatFrom(const char * channel) = 0;
    virtual StringEvent * receiveStringFrom(const char * channel) = 0;

    virtual Events & sendTo(const char * channel, t_CKINT intval) = 0;
    virtual Events & sendTo(const char * channel, t_CKFLOAT floatval) = 0;
    virtual Events & sendTo(const char * channel, const char * stringval) = 0;

    virtual void RegisterIntListener(const char * channel, IntReceiver * rec) = 0;
    virtual void RegisterFloatListener(const char * channel, FloatReceiver * rec) = 0;
    virtual void RegisterStringListener(const char * channel, StringReceiver * rec) = 0;

    virtual void Clear() = 0;

public:
    static Events * GetInstance();

};

#endif // __UTIL_EVENTS_H__
