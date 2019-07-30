#include "abstract.h"
#include "ooz/ooz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ast_t ast;

void
abs_set_module(const char *name, size_t len)
{
    if (!name) {
        ast.module_name = NULL;
        ast.module_name_len = 0;
    }

    ast.module_name = (char *)malloc(sizeof(char) * (len + 1));
    if (!ast.module_name) {
        LOG_FATAL(ErrNoMem);
    }

    strncpy(ast.module_name, name, len + 1);
    ast.module_name[len] = '\0';
    ast.module_name_len = len;
}
