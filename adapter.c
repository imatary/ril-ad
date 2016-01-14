//
// Created by wangzhiheng on 1/11/16.
//

#include "adapter.h"


// inject


void free_bytes(ByteBuffer *bytes) {
    if (bytes != NULL) {
        if (bytes->buffer != NULL) {
            free(bytes->buffer);
            bytes->buffer = NULL;
        }
        free(bytes);
        bytes = NULL;
    }
}

ByteBuffer *string_to_bytes(const char *text) {
    int i, j;
    int string_length = strlen(text);
    char high, low;

    char text_buffer[CHAR_MAX] = {0};
    ByteBuffer *bytes;

    if (string_length > CHAR_MAX) {
        RLOGD("adapter RILSO string_to_bytes text length is gather than %d\n", CHAR_MAX);
        return NULL;
    }
    if (string_length % 2 != 0) {
        RLOGD("adapter RILSO string_to_bytes text length is odd.\n");
        return NULL;
    }

    strcpy(text_buffer, text);
    for (i = 0; i < string_length; ++i) {
        text_buffer[i] = toupper(text_buffer[i]);
    }
    bytes = (ByteBuffer *) malloc(sizeof(ByteBuffer));
    memset(bytes, 0, sizeof(ByteBuffer));
    bytes->length = string_length / 2;
    bytes->buffer = (Byte *) malloc(sizeof(Byte) * bytes->length);
    memset(bytes->buffer, 0, bytes->length);
    for (i = 0, j = 0; i < string_length; i += 2, j++) {
        high = text_buffer[i];
        low = text_buffer[i + 1];
        if (isalnum(high) == 0 || isalnum(low) == 0) {
            free_bytes(bytes);
            return NULL;
        }
        if (high >= 'A' && high <= 'F') {
            high = high - 'A' + 10;
        } else if (high >= '0' && high <= '9') {
            high = high - '0';
        }

        if (low >= 'A' && low <= 'F') {
            low = low - 'A' + 10;
        } else if (low >= '0' && low <= '9') {
            low = low - '0';
        }
        bytes->buffer[j] = high << 4 | low;
    }
    return bytes;
}

char *bytes_to_string(ByteBuffer *bytes) {
    char *text;
    Byte high, low;


    if (bytes == NULL) {
        RLOGD("adapter RILSO bytes_to_string bytes is NULL\n");
        return NULL;
    }
    text = (char*)malloc(bytes->length * 2 + 1);
    memset(text, 0, bytes->length * 2 + 1);
    for (int i = 0; i < bytes->length; i++) {
        high = bytes->buffer[i] & 0xf0 >> 4;
        low = bytes->buffer[i] & 0x0f;
        if (high >= 0 && high <= 9) {
            high += 0x30;
        } else if (high >= 10 && high <= 15) {
            high = high - 10 + 'A';
        }
        if (low >= 0 && low <= 9) {
            low += 0x30;
        } else if (low >= 10 && low <= 15) {
            low = low - 10 + 'A';
        }
        text[i * 2] = high;
        text[i * 2 + 1] = low;
    }
    return text;
}