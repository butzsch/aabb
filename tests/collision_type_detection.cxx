#include <gtest/gtest.h>

#include "aabb/aabb.hxx"
#include "aabb_testing.hxx"

using namespace aabb;

template<typename T>
class CollisionTypeFunction
    : public testing::Test
{
};

TYPED_TEST_CASE_P(CollisionTypeFunction);

TYPED_TEST_P(CollisionTypeFunction, AssertsThatObjectsDontAlreadyCollide)
{
    static auto constexpr a = Box<TypeParam> {
        Vector<TypeParam> {0, 0},
        Vector<TypeParam> {1, 1},
    };

    static auto constexpr movement = Vector<TypeParam> {1, 1};

    ASSERT_DEATH(get_colliding_edges(a, movement, a), "");
}

TEST(EdgeTypeBoth, IsBothHorizontalAndVertical)
{
    static auto constexpr both = EdgeType::BOTH;
    ASSERT_TRUE(both & EdgeType::HORIZONTAL);
    ASSERT_TRUE(both & EdgeType::VERTICAL);
}

REGISTER_TYPED_TEST_CASE_P(CollisionTypeFunction,
    AssertsThatObjectsDontAlreadyCollide
);


INSTANTIATE_TYPED_TEST_CASE_P(CollsionTypeFunctionTest, CollisionTypeFunction, aabb_testing::types_to_test);
