#include <gtest/gtest.h>
#include "../CacheImp.h"
#include <string>

class CacheTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(CacheTest, BasicOps) {
    ClockCache<int, int> c(3);
    c.set(1, 10);
    EXPECT_TRUE(c.contains(1));
    EXPECT_EQ(c.get(1), 10);
    EXPECT_EQ(c.size(), 1);
}

TEST_F(CacheTest, UpdateKey) {
    ClockCache<std::string, int> c(2);
    c.set("test", 1);
    c.set("test", 5);
    EXPECT_EQ(c.get("test"), 5);
    EXPECT_EQ(c.size(), 1);
}

TEST_F(CacheTest, OverflowLogic) {
    ClockCache<int, int> c(2);
    c.set(1, 10);
    c.set(2, 20);
    c.set(3, 30);

    EXPECT_FALSE(c.contains(1));
    EXPECT_TRUE(c.contains(2));
    EXPECT_TRUE(c.contains(3));
}

TEST_F(CacheTest, SecondChance) {
    ClockCache<int, int> c(2);
    c.set(1, 10);
    c.set(2, 20);

    c.set(3, 30);
    EXPECT_FALSE(c.contains(1));

    c.get(2);
    c.set(4, 40);

    EXPECT_FALSE(c.contains(2));
    EXPECT_TRUE(c.contains(3));
    EXPECT_TRUE(c.contains(4));
}

TEST_F(CacheTest, Clear) {
    ClockCache<int, int> c(5);
    c.set(1, 1);
    c.clear();
    EXPECT_EQ(c.size(), 0);
    EXPECT_FALSE(c.contains(1));
}