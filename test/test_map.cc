#include "lib/map.h"
#include <gtest/gtest.h>

TEST(test_map, test_new)
{
    map_t *m;

    m = map_new(0);
    EXPECT_EQ(m, nullptr);
    m = map_new(1);
    EXPECT_EQ(m, nullptr);
    m = map_new(4);
    EXPECT_NE(m, nullptr);
    map_free(m);
}

TEST(test_map, test_set_get)
{
    map_t *m;
    int n = 42;
    int ret;

    m = map_new(4);
    EXPECT_NE(m, nullptr);
    ret = map_set(m, "foo", &n);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(map_size(m), 1);
    EXPECT_EQ(*(int *)map_get(m, "foo"), 42);
    map_free(m);
}
