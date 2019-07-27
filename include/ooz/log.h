/**
 * @file log.h
 * Logging
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define _LOG(prefix, err)                                                      \
    fprintf(stderr, "[%s] %s:%d: errcode: %d\n", prefix, __FILE__, __LINE__,   \
            (int)(err))

#define LOG_FATAL(err)                                                         \
    do {                                                                       \
        _LOG("FATAL", (err));                                                  \
        exit(1);                                                               \
    } while (0)
