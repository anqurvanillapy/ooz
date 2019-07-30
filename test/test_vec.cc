#include "lib/vec.h"
#include <gtest/gtest.h>

TEST(test_vec, test_new)
{
    vec_t *v;
    v = vec_new();
    EXPECT_NE(v, nullptr);
    vec_free(v);
}
