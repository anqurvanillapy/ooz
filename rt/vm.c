#include "ooz/ooz.h"

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

uintptr_t r1;
uintptr_t r2;
uintptr_t r3;
uintptr_t r4;
uintptr_t r5;
uintptr_t r6;
uintptr_t r7;
uintptr_t r8;

uintptr_t stk;

err_t
vm_start()
{
    return OK;
}
