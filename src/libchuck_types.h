/*
 * libchuck
 * Brian Sorahan 2014
 */
#ifndef LIBCHUCK_TYPES_H
#define LIBCHUCK_TYPES_H

#include <chuck_def.h>

// libchuck channel types
typedef enum {
    LIBCHUCK_INT_CHANNEL,
    LIBCHUCK_FLOAT_CHANNEL,
    LIBCHUCK_STRING_CHANNEL,
} libchuck_channel_t;

typedef union {
    t_CKINT intval;
    t_CKFLOAT floatval;
    char * strval;
} libchuck_channel_val_t;

typedef struct _libchuck_channel_data {
    const char * name;
    libchuck_channel_t type;
    libchuck_channel_val_t value;
} libchuck_channel_data;

#endif // LIBCHUCK_TYPES_H
