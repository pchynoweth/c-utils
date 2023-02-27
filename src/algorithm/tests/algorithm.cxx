#include "algorithm.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

static int compare_less_than(void const* a, void const* b) {
    auto l = *(int *)a;
    auto r = *(int *)b;
    return l < r ? -1 : l > r ? 1 : 0;
}

class AlgorithmTest :
    public testing::TestWithParam<std::vector<int>> 
{};

TEST_P(AlgorithmTest, LowerBound) {
    auto& c = GetParam();
    for (auto v : c) {
        auto it = std::lower_bound(c.begin(), c.end(), v);
        EXPECT_EQ(*it, v);
        auto ptr = cutils_lower_bound(const_cast<int*>(c.data()), c.size(), sizeof(int), compare_less_than, &v);
        EXPECT_EQ(*(int*)ptr, v);
        EXPECT_EQ((void*)&(*it), ptr);
    }
}

TEST_P(AlgorithmTest, UpperBound) {
    auto& c = GetParam();
    for (auto v : c) {
        auto it = std::upper_bound(c.begin(), c.end(), v);
        auto ptr = cutils_upper_bound(const_cast<int*>(c.data()), c.size(), sizeof(int), compare_less_than, &v);
        EXPECT_EQ((void*)&(*it), ptr);
    }
}

TEST_P(AlgorithmTest, EqualRange) {
    auto& c = GetParam();
    for (auto v : c) {
        auto [first, last] = std::equal_range(c.begin(), c.end(), v);
        auto r = cutils_equal_range(const_cast<int*>(c.data()), c.size(), sizeof(int), compare_less_than, &v);
        EXPECT_EQ((void*)&(*first), r.begin);
        EXPECT_EQ((void*)&(*last), r.end);
    }
}

static const std::vector<std::vector<int>> params = {
    {},
    { 1 },
    { -1 },
    { std::numeric_limits<int>::min() },
    { std::numeric_limits<int>::max() },
    { std::numeric_limits<int>::min(), std::numeric_limits<int>::max() },
    { std::numeric_limits<int>::min(), -1, -1, 0, 0, 0, 1, 2, 3, 4, 4, 4, 4, std::numeric_limits<int>::max() }
};

INSTANTIATE_TEST_SUITE_P(AlgorithmTest,
                         AlgorithmTest,
                         testing::ValuesIn(params));

TEST(AlgorithmTest, Swap) {
    int a = 1;
    int b = 2;
    cutils_swap(&a, &b, sizeof(int));
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);
}

TEST(AlgorithmTest, Reverse) {
    int a[] = { 1, 2, 3, 4, 5 };
    cutils_reverse(a, 5, sizeof(int));
    EXPECT_THAT(a, testing::ElementsAre(5, 4, 3, 2, 1));
}

TEST(AlgorithmTest, NextPermutation) {
    int values[][3] = {
        { 1, 3, 2 },
        { 2, 1, 3 },
        { 2, 3, 1 },
        { 3, 1, 2 },
        { 3, 2, 1 }
    };

    int a[] = { 1, 2, 3 };

    for (size_t i = 0; i < sizeof(values) / sizeof(*values); ++i) {
        EXPECT_TRUE(cutils_next_permutation(a, 3, sizeof(int), compare_less_than));
        ASSERT_THAT(a, testing::ElementsAreArray(values[i]));
    }
    EXPECT_FALSE(cutils_next_permutation(a, 3, sizeof(int), compare_less_than));
}

TEST(AlgorithmTest, NextPermutation2) {

    int control[] = { 1, 2, 3, 4, 5 };
    int a[] = { 1, 2, 3, 4, 5 };

    while (std::next_permutation(control, control + 5)) {
        EXPECT_TRUE(cutils_next_permutation(a, 5, sizeof(int), compare_less_than));
        ASSERT_THAT(a, testing::ElementsAreArray(control));
    }
    EXPECT_FALSE(cutils_next_permutation(a, 5, sizeof(int), compare_less_than));
}