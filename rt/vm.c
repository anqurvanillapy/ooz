#include "rt.h"

uintptr_t
vm_push(uintptr_t *s, closure_t *v)
{
    uintptr_t obj = (uintptr_t)v;
    *(uintptr_t *)*s = obj;
    *s += sizeof(void *);
    return obj;
}

void
vm_pop(uintptr_t *s)
{
    *s -= sizeof(void *);
}

uintptr_t R1;
uintptr_t R2;
uintptr_t R3;
uintptr_t R4;

uintptr_t stk;

err_t
vm_start()
{
    return OK;
}
