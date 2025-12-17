#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include "../KwayMerge.h"

class MergeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MergeTest, Empty) {
    std::vector<int> v;
    auto res = KwayMergeSort(v);
    EXPECT_TRUE(res.empty());
}

TEST_F(MergeTest, OneElement) {
    std::vector<int> v = { 100 };
    std::vector<int> expected = { 100 };
    EXPECT_EQ(KwayMergeSort(v), expected);
}

TEST_F(MergeTest, SimpleArray) {
    std::vector<int> v = { 5, 1, 9, 3, 7 };
    std::vector<int> res = KwayMergeSort(v);
    std::sort(v.begin(), v.end());
    EXPECT_EQ(res, v);
}

TEST_F(MergeTest, ReverseOrder) {
    std::vector<int> v = { 5, 4, 3, 2, 1 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(KwayMergeSort(v, 3, 1), expected);
}

TEST_F(MergeTest, Negatives) {
    std::vector<int> v = { -1, -10, 0, 5 };
    std::vector<int> exp = { -10, -1, 0, 5 };
    EXPECT_EQ(KwayMergeSort(v), exp);
}

TEST_F(MergeTest, BigRandom) {
    std::vector<int> v(150);
    for (int i = 0; i < 150; ++i) v[i] = rand() % 500;

    std::vector<int> copy = v;
    std::sort(copy.begin(), copy.end());

    auto res = KwayMergeSort(v, 5, 10);
    EXPECT_EQ(res, copy);
}

TEST_F(MergeTest, StringsCheck) {
    std::vector<std::string> v = { "z", "a", "m" };
    std::vector<std::string> exp = { "a", "m", "z" };
    EXPECT_EQ(KwayMergeSort(v), exp);
}