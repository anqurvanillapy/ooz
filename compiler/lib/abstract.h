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
    struct expr *body;
} lam_t;

typedef struct {
    int index;
    const char *name;
    struct expr *def;
} var_t;

typedef struct {
    struct expr *lhs;
    struct expr *rhs;
} app_t;

typedef enum expr_tag {
    ExprLam,
    ExprVar,
    ExprApp,
} expr_tag_t;

typedef struct expr {
    fileloc_t loc;

    expr_tag_t tag;
    union {
        lam_t lam;
        var_t var;
        app_t app;
    } val;

    // FIXME
    int depth;
} expr_t;

typedef struct {
    const char *filename;
    const char *module_name;
    map_t *ctx;
    vec_t *defs;
    vec_t *decls;
} abs_t;

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

void abs_init(const char *filename);

void abs_set_module(const char *name);

void abs_ctx_add(const char *name, expr_t *expr);

expr_t *abs_lam_new(int line, int col, const char *arg, expr_t *body);

expr_t *abs_var_new(int col, int line, const char *name);

expr_t *abs_app_new(int line, int col, expr_t *lhs, expr_t *rhs);

void abs_check_boundfree();

void abs_walk_expr(expr_t *expr);

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
