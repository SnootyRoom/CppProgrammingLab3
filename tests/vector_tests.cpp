#include <container/Vector.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

static_assert(std::random_access_iterator<lab3::Vector<int>::iterator>);
static_assert(std::random_access_iterator<lab3::Vector<int>::const_iterator>);

static_assert(lab3::Numeric<int>);
static_assert(lab3::Numeric<double>);
static_assert(!lab3::Numeric<bool>);
static_assert(!lab3::Numeric<char>);
static_assert(!lab3::Numeric<std::string>);

namespace
{
    lab3::Vector<int> makeVector(std::initializer_list<int> values)
    {
        lab3::Vector<int> v;
        for (int x : values)
            v.push_back(x);
        return v;
    }
}

TEST(VectorTest, DefaultConstructedIsEmpty)
{
    lab3::Vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_EQ(v.begin(), v.end());
}

TEST(VectorTest, PushBackStoresValuesAndGrowsCapacity)
{
    lab3::Vector<int> v;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
        EXPECT_GE(v.capacity(), v.size());
    }
    ASSERT_EQ(v.size(), 100u);
    EXPECT_EQ(v.front(), 0);
    EXPECT_EQ(v.back(), 99);

    lab3::Vector<int> single = makeVector({7});
    single.push_back(single[0]);
    EXPECT_EQ(single[1], 7);
}

TEST(VectorTest, PopBackRemovesLastAndThrowsWhenEmpty)
{
    lab3::Vector<int> v = makeVector({1, 2});
    v.pop_back();
    ASSERT_EQ(v.size(), 1u);
    EXPECT_EQ(v.back(), 1);

    v.pop_back();
    EXPECT_TRUE(v.empty());
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(VectorTest, EraseShiftsElementsLeft)
{
    lab3::Vector<int> v = makeVector({1, 2, 3, 4, 5});
    v.erase(1);
    ASSERT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[3], 5);
    EXPECT_THROW(v.erase(10), std::out_of_range);
}

TEST(VectorTest, ClearRemovesElementsButKeepsCapacity)
{
    lab3::Vector<int> v = makeVector({1, 2, 3, 4, 5});
    std::size_t capacityBefore = v.capacity();
    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.capacity(), capacityBefore);
}

TEST(VectorTest, AtChecksBounds)
{
    lab3::Vector<int> v = makeVector({1, 2, 3});
    EXPECT_EQ(v.at(2), 3);
    EXPECT_THROW(v.at(3), std::out_of_range);

    v[1] = 99;
    EXPECT_EQ(v.at(1), 99);
}

TEST(VectorTest, CopyIsDeep)
{
    lab3::Vector<int> original = makeVector({1, 2, 3});

    lab3::Vector<int> constructed = original;
    constructed[0] = 100;
    EXPECT_EQ(original[0], 1);

    lab3::Vector<int> assigned = makeVector({9});
    assigned = original;
    ASSERT_EQ(assigned.size(), 3u);
    EXPECT_TRUE(std::equal(assigned.begin(), assigned.end(), original.begin()));
}

TEST(VectorTest, MoveTransfersOwnership)
{
    lab3::Vector<int> source = makeVector({1, 2, 3});

    lab3::Vector<int> constructed = std::move(source);
    ASSERT_EQ(constructed.size(), 3u);
    EXPECT_TRUE(source.empty());

    lab3::Vector<int> assigned;
    assigned = std::move(constructed);
    ASSERT_EQ(assigned.size(), 3u);
    EXPECT_EQ(assigned[2], 3);
    EXPECT_TRUE(constructed.empty());
}

TEST(VectorTest, IteratorArithmeticAndIncrement)
{
    lab3::Vector<int> v = makeVector({10, 20, 30, 40});
    auto first = v.begin();
    auto last = v.end();

    EXPECT_EQ(last - first, 4);
    EXPECT_EQ(*(first + 2), 30);
    EXPECT_EQ(first[3], 40);
    EXPECT_LT(first, last);

    auto it = first;
    EXPECT_EQ(*it++, 10);
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*--it, 10);
}

TEST(VectorTest, WorksWithStandardAlgorithms)
{
    lab3::Vector<int> v = makeVector({5, 3, 1, 4, 2});

    std::sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));

    auto found = std::find(v.begin(), v.end(), 4);
    ASSERT_NE(found, v.end());
    EXPECT_EQ(found - v.begin(), 3);
    EXPECT_EQ(std::find(v.begin(), v.end(), 100), v.end());

    int sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
    EXPECT_EQ(sum, 15);
}