/**
 * @file rt.h
 * Runtime library
 */

#pragma once

#include "ooz/error.h"
#include <stdint.h>

typedef enum closure_type {
    ClosCtor, /**< Constructor */
    ClosThunk,
} closure_type_t;

typedef enum val_type {
    TypeInt,
    TypeFun,
} val_type_t;

/**
 * Closure entry
 */
typedef void (*entry_t)();

/**
 * Closure info table
 */
typedef struct infotbl {
    val_type_t type;
    entry_t entry;
} infotbl_t;

typedef struct closure {
    closure_type_t type;
    infotbl_t *info_ptr;
    void *payload;
} closure_t;

#define STACK_SIZ 8192

#ifdef __cpluscplus
extern "C" {
#endif /* __cpluscplus */

/**
 * Push a closure to stack
 */
uintptr_t vm_push(uintptr_t *s, closure_t *v);

/**
 * Pop a closure from stack
 */
void vm_pop(uintptr_t *s);

/**
 * Start the VM
 */
err_t vm_start();

#ifdef __cpluscplus
}
#endif /* __cpluscplus */
