#include "vec.h"
#include "ooz/ooz.h"
#include <string.h>

vec_t *
vec_new()
{
    vec_t *p = (vec_t *)malloc(sizeof(vec_t));
    if (!p) {
        LOG_FATAL(ErrNoMem);
    }
    p->data = NULL;
    p->cap = 0;
    p->size = 0;
    return p;
}

size_t
vec_size(vec_t *self)
{
    if (!self) {
        return 0;
    }
    return self->size;
}

void **
vec_data(vec_t *self)
{
    if (!self) {
        return NULL;
    }
    return self->data;
}

int
vec_add(vec_t *self, void *el)
{
    static const size_t initial_cap = 8;
    void **new_data = NULL;

    if (!self) {
        return -1;
    }

    if (!self->cap) {
        self->data = malloc(sizeof(void *) * initial_cap);
        if (!self->data) {
            LOG_FATAL(ErrNoMem);
        }
        self->cap = initial_cap;
    }

    if (self->cap == self->size) {
        new_data = realloc(self->data, sizeof(void *) * (self->cap * 2));
        if (!new_data) {
            LOG_FATAL(ErrNoMem);
        }
        self->data = new_data;
        self->cap *= 2;
    }

    self->data[self->size] = el;
    self->size++;

    return 0;
}

void *
vec_get(vec_t *self, size_t pos)
{
    if (pos >= self->size) {
        return NULL;
    }
    return self->data[pos];
}

int
vec_set(vec_t *self, size_t pos, void *el)
{
    if (pos >= self->size) {
        return -1;
    }
    self->data[pos] = el;
    return 0;
}

int
vec_del(vec_t *self, size_t pos)
{
    size_t i, j;
    size_t new_cap = self->cap;
    void **new_data = NULL;

    if (pos >= self->size) {
        return -1;
    }

    if (self->cap / (self->size - 1) > 3) {
        new_cap = self->cap / 2;
    }
    new_data = (void **)malloc(sizeof(void *) * new_cap);
    if (!new_data) {
        LOG_FATAL(ErrNoMem);
    }

    for (i = 0, j = 0; i < self->size; ++i) {
        if (i != pos) {
            new_data[j] = self->data[i];
            j++;
        }
    }
    free(self->data);
    self->data = new_data;
    self->size--;

    return 0;
}

void
vec_free(vec_t *self)
{
    if (!self) {
        return;
    }
    free(self->data);
    free(self);
}
