/**
 * @file codegen.h
 * Code generator
 */

#pragma once

#include "ooz/ooz.h"
#include <stdio.h>

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

/**
 * Initialize code generator
 */
err_t cg_init(const char *filename);

err_t cg_writefile();

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
