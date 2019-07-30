#pragma once

#include <stdlib.h>

typedef struct {
    void **data;
    size_t cap;
    size_t size;
} vec_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

vec_t *vec_new();
void vec_free(vec_t *self);

size_t vec_size(vec_t *self);
void **vec_data(vec_t *self);

int vec_add(vec_t *self, void *el);
void *vec_get(vec_t *self, size_t pos);
int vec_set(vec_t *self, size_t pos, void *el);
int vec_del(vec_t *self, size_t pos);

#ifdef __cplusplus
}
#endif /* __cplusplus */
