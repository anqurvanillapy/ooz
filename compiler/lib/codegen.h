#pragma once

#include "ooz/error.h"
#include <stdio.h>

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

/**
 * Initialize code generator
 */
err_t cg_init(const char *outfile);

err_t cg_writefile();

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
