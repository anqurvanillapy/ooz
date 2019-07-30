#include "map.h"
#include "ooz/ooz.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    void *val;
} kvpair_t;

static inline uint32_t
fmix(uint32_t h)
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

static inline uint32_t
rotl32(uint32_t x, int8_t r)
{
    return (x << r) | (x >> (32 - r));
}

/**
 * Murmurhash3
 */
static size_t
hash(const char *key, size_t len)
{
    size_t i;
    uint32_t k1, k2;
    const size_t nblocks = len / 4;

    uint32_t h1 = 0xc062fb4a;
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;

    const uint32_t *blocks = (const uint32_t *)(key + nblocks * 4);

    for (i = -nblocks; i; i++) {
        k1 = blocks[i];
        k1 *= c1;
        k1 = rotl32(h1, 13);
        h1 = h1 * 5 + 0xe6546b64;
    }

    const uint8_t *tail = (const uint8_t *)(key + nblocks * 4);
    k2 = 0;

    switch (len & 3) {
    case 3:
        k2 ^= (uint32_t)tail[2] << 16;
        // fallthrough
    case 2:
        k2 ^= (uint32_t)tail[1] << 8;
        // fallthrough
    case 1:
        k2 ^= tail[0];
        // fallthrough
    }

    k2 *= c1;
    k2 = rotl32(k2, 15);
    k2 *= c2;
    h1 ^= k2;

    h1 ^= (uint32_t)len;
    h1 = fmix(h1);
    return h1;
}

static int
map_find_from_bucket(vec_t *v, const char *key, size_t *pos)
{
    if (!v) {
        return -1;
    }

    size_t i;
    void **data = vec_data(v);

    for (i = 0; i < vec_size(v); ++i) {
        kvpair_t *p = data[i];
        if (strcmp(key, p->key) == 0) {
            *pos = i;
            return 0;
        }
    }
    return -1;
}

map_t *
map_new(size_t cap)
{
    if (!cap || cap < 4 || (cap & (cap - 1)) != 0) {
        return NULL;
    }

    map_t *m = (map_t *)malloc(sizeof(map_t));
    if (!m) {
        LOG_FATAL(ErrNoMem);
    }

    m->cap = cap;
    m->mask = cap - 1;
    m->size = 0;
    m->buckets = (vec_t **)malloc(sizeof(vec_t *) * cap);
    if (!m->buckets) {
        LOG_FATAL(ErrNoMem);
    }
    memset(m->buckets, 0, sizeof(vec_t *) * cap);

    return m;
}

size_t
map_size(map_t *self)
{
    if (!self) {
        return 0;
    }
    return self->size;
}

int
map_set(map_t *self, const char *key, void *val)
{
    if (!self || !key) {
        return -1;
    }

    size_t len = strlen(key);
    if (!len) {
        return -1;
    }

    size_t h = hash(key, len);
    vec_t *v = self->buckets[h & self->mask];

    if (!v) {
        v = vec_new();
        self->buckets[h & self->mask] = v;
    } else {
        size_t pos;
        int ret = map_find_from_bucket(v, key, &pos);
        if (ret == 0) {
            kvpair_t *p = vec_get(v, pos);
            p->val = val;
            return -1;
        }
    }

    kvpair_t *p = (kvpair_t *)malloc(sizeof(kvpair_t));
    if (!p) {
        LOG_FATAL(ErrNoMem);
    }

    p->key = key;
    p->val = val;
    self->size++;

    return vec_add(v, p);
}

void *
map_get(map_t *self, const char *key)
{
    if (!self) {
        return NULL;
    }

    size_t len = strlen(key);
    if (!len) {
        return NULL;
    }

    size_t h = hash(key, len);
    vec_t *v = self->buckets[h & self->mask];

    if (!v) {
        return NULL;
    }

    size_t pos;
    int ret = map_find_from_bucket(v, key, &pos);
    if (ret != 0) {
        return NULL;
    }
    kvpair_t *p = vec_get(v, pos);
    return p->val;
}

void
map_free(map_t *self)
{
    if (!self) {
        return;
    }

    if (self->buckets) {
        size_t i, j;
        for (i = 0; i < self->cap; ++i) {
            vec_t *v = self->buckets[i];
            if (v) {
                void **data = vec_data(v);
                for (j = 0; j < vec_size(v); ++j) {
                    kvpair_t *el = data[j];
                    if (el) {
                        free(el);
                    }
                }
                vec_free(v);
            }
        }
        free(self->buckets);
    }

    free(self);
}
