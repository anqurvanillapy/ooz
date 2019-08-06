#include "abstract.h"
#include "concrete.h"
#include "ooz/ooz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRFMT_PREFIX "%s:%d:%d: "

#define ERRFMT_Ctx_VariablelreadyExists                                        \
    ERRFMT_PREFIX "Varaible '%s' already exists\n"
#define ERRFMT_Ctx_UnboundVariable ERRFMT_PREFIX "Unbound variable '%s'\n"

#define ABS_ERROR(fmt, ...)                                                    \
    do {                                                                       \
        fprintf(stderr, fmt, __VA_ARGS__);                                     \
        exit(1);                                                               \
    } while (0)

static abs_t ast;

void
abs_init(const char *filename)
{
    ast.filename = filename;
    abs_set_module(NULL);
    ast.ctx = map_new(64);
}

void
abs_set_module(const char *name)
{
    if (!name) {
        ast.module_name = NULL;
        return;
    }
    ast.module_name = name;
}

bool
abs_ctx_has(const char *name)
{
    return !!map_get(ast.ctx, name);
}

void
abs_ctx_add(const char *name, expr_t *expr)
{
    if (abs_ctx_has(name)) {
        ABS_ERROR(ERRFMT_Ctx_VariablelreadyExists, ast.filename, expr->loc.line,
                  expr->loc.col, name);
    }

    if (map_set(ast.ctx, name, expr) != 0) {
        LOG_FATAL(ErrInternal);
    }
}

static expr_t *
_abs_expr_new(int line, int col)
{
    expr_t *expr = (expr_t *)malloc(sizeof(expr_t));
    if (!expr) {
        LOG_FATAL(ErrNoMem);
    }
    expr->loc.line = line;
    expr->loc.col = col;
    expr->next = NULL;
    return expr;
}

static int
_abs_env_lookup(vec_t *env, const char *name)
{
    int i;
    const char **data = (const char **)vec_data(env);
    int size = (int)vec_size(env);
    for (i = size - 1; i >= 0; --i) {
        if (strcmp(name, data[i]) == 0) {
            return size - i;
        }
    }
    return 0;
}

static void
_abs_lam_set_dbi(expr_t *lam)
{
    vec_t *env = vec_new();
    vec_t *items = vec_new();

    vec_add(env, (void *)lam->val.lam.arg);
    vec_add(items, lam->val.lam.body);

    while (vec_size(items) != 0) {
        size_t nitem = vec_size(items);
        expr_t *item = vec_get(items, nitem - 1);
        vec_del(items, nitem - 1);

        if (item->next) {
            vec_add(items, item->next);
        }

        if (item->tag == ExprLam) {
            vec_add(env, (void *)item->val.lam.arg);
            vec_add(items, item->val.lam.body);
            continue;
        }

        if (item->val.var.index != 0) {
            if (!item->next) {
                vec_del(env, vec_size(env) - 1);
            }
            continue;
        }

        int index = _abs_env_lookup(env, item->val.var.name);
        item->val.var.index = index;
        printf("%d:%d: variable '%s' index: %d\n", item->loc.line,
               item->loc.col, item->val.var.name, index);

        if (!item->next) {
            vec_del(env, vec_size(env) - 1);
        }
    }

    vec_free(env);
    vec_free(items);
}

expr_t *
abs_lam_new(int line, int col, const char *arg, expr_t *body)
{
    if (!arg || !body) {
        LOG_FATAL(ErrInternal);
    }

    expr_t *expr = _abs_expr_new(line, col);
    expr->tag = ExprLam;
    expr->val.lam.arg = arg;
    expr->val.lam.body = body;

    _abs_lam_set_dbi(expr);

    return expr;
}

expr_t *
abs_var_new(int line, int col, const char *name)
{
    expr_t *expr = _abs_expr_new(line, col);
    expr->tag = ExprVar;
    expr->val.var.name = name;
    return expr;
}

void
abs_def_check_boundfree(const char *this, expr_t *expr)
{
    vec_t *items = vec_new();
    vec_add(items, expr);

    while (vec_size(items) != 0) {
        size_t nitem = vec_size(items);
        expr_t *item = vec_get(items, nitem - 1);
        vec_del(items, nitem - 1);

        if (item->next) {
            vec_add(items, item->next);
        }

        if (item->tag == ExprLam) {
            vec_add(items, item->val.lam.body);
            continue;
        }

        if (item->val.var.index > 0) {
            continue;
        }

        const char *name = item->val.var.name;
        if (strcmp(this, name) != 0 && !map_get(ast.ctx, name)) {
            ABS_ERROR(ERRFMT_Ctx_UnboundVariable, ast.filename, item->loc.line,
                      item->loc.col, name);
        }
    }

    vec_free(items);
}
