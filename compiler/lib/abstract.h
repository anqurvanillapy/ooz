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
    fileloc_t loc;
    char *arg;
    struct expr *e;
} lam_t;

typedef struct {
    fileloc_t loc;
    int index;
    char *name;
} var_t;

typedef enum expr_tag {
    ExprLam,
    ExprVar,
} expr_tag_t;

typedef struct expr {
    expr_tag_t tag;
    union {
        lam_t lam;
        var_t var;
    } val;
} expr_t;

typedef struct {
    vec_t *defs;
    vec_t *decls;
} stmt_t;

typedef struct {
    char *module_name;
    size_t module_name_len;

    map_t *stmts;
} abs_t;

void abs_init(const char *name, size_t len);

bool abs_env_lookup(const char *name);

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
