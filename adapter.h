//
// Created by wangzhiheng on 12/18/15.
//

#ifndef RADIOADAPTER_ADAPTER_H
#define RADIOADAPTER_ADAPTER_H

#include <limits.h>
#include <log/log.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

//#define LOCAL_TRACE

#ifdef LOCAL_TRACE
#define LOGT(...)                           \
    do {                                    \
        RLOGD(__VA_ARGS__);                 \
    } while(0)
#else
#define LOGT(...)
#endif


typedef struct {
    Byte *buffer;
    int length;
} ByteBuffer;

typedef struct {
    char key[256];
    char value[32];
} KEY_VALUE_PAIR;

typedef struct {
    int index;
    char message[64];
} MESSAGE_ITEM;


void free_bytes(ByteBuffer *bytes);

ByteBuffer *string_to_bytes(const char *text);

char *bytes_to_string(ByteBuffer *bytes);

#endif //RADIOADAPTER_ADAPTER_H

