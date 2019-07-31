#include "abstract.h"
#include "concrete.h"
#include "ooz/ooz.h"
#include <stdio.h>
#include <stdlib.h>

#define ERRFMT_Ctx_ValueAlreadyExists "%s:%d:%d: Value '%s' already exists"

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
abs_ctx_lookup(const char *name)
{
    return map_get(ast.ctx, name) != NULL;
}

void
abs_ctx_add(const char *name, expr_t *expr)
{
    if (abs_ctx_lookup(name)) {
        ABS_ERROR(ERRFMT_Ctx_ValueAlreadyExists, ast.filename, expr->loc.line,
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
    expr->env = NULL;
    expr->next_expr = NULL;
    return expr;
}

expr_t *
abs_lam_new(int line, int col)
{
    expr_t *expr = _abs_expr_new(line, col);
    expr->env = vec_new();
    expr->tag = ExprLam;
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
