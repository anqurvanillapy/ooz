/**
 * @file concrete.h
 * Utilities for concrete syntax
 */

#pragma once

#include <stddef.h>

typedef struct {
    int line;
    int col;
} fileloc_t;

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

char *lex_substr(const char *txt, size_t len);

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
