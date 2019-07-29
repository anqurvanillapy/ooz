/**
 * @file abstract.h
 * Abstract syntax
 */

#pragma once

#include <stddef.h>

typedef struct {
    char *module_name;
    size_t module_name_len;
} ast_t;

/**
 * Set module name
 */
void abs_set_module(const char *name, size_t len);

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
