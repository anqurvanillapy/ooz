/**
 * @file abstract.h
 * Abstract syntax
 */

#pragma once

#include "concrete.h"
#include "map.h"
#include "vec.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const char *arg;
    struct expr *exp;
} lam_t;

typedef struct {
    int index;
    const char *name;
} var_t;

typedef enum expr_tag {
    ExprLam,
    ExprVar,
} expr_tag_t;

typedef struct expr {
    fileloc_t loc;

    expr_tag_t tag;
    union {
        lam_t lam;
        var_t var;
    } val;

    struct expr *next;
} expr_t;

typedef struct {
    vec_t *defs;
    vec_t *decls;
} stmt_t;

typedef struct {
    const char *filename;
    const char *module_name;
    map_t *ctx;
} abs_t;

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

void abs_init(const char *filename);

void abs_set_module(const char *name);

bool abs_ctx_lookup(const char *name);

void abs_ctx_add(const char *name, expr_t *expr);

expr_t *abs_lam_new(int col, int line);

expr_t *abs_var_new(int col, int line, const char *name);

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
