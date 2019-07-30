#pragma once

#include "vec.h"
#include <stddef.h>

typedef struct {
    vec_t **buckets;
    size_t cap;
    size_t mask;
    size_t size;
} map_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

map_t *map_new(size_t cap);
void map_free(map_t *self);

size_t map_size(map_t *self);

int map_set(map_t *self, const char *key, void *val);
void *map_get(map_t *self, const char *key);

#ifdef __cplusplus
}
#endif /* __cplusplus */
