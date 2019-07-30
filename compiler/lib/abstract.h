/**
 * @file abstract.h
 * Abstract syntax
 */

#pragma once

#include "map.h"
#include "vec.h"
#include <stddef.h>

typedef enum expr_tag {
    ExprLit,
    ExprLam,
} expr_tag_t;

typedef struct {
    int arity;
} lambda_t;

typedef struct {
    expr_tag_t tag;
    union {
        void *lit;
        lambda_t lam;
    } val;
} expr_t;

typedef struct {
    vec_t *exprs;
} def_t;

typedef struct {
    vec_t *defs;
    vec_t *decls;
} stmt_t;

typedef struct {
    char *module_name;
    size_t module_name_len;

    map_t *stmts;
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
