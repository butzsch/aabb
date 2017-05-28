#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "aabb/aabb.hxx"
#include "aabb_testing.hxx"

using namespace aabb;
using namespace testing;

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

TYPED_TEST_P(CollisionTypeFunction, DetectsTopRightOnEdgeCollisionAsBoth)
{
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        {1, 1},
    };
    static auto constexpr delta_position = Vector<TypeParam> {10, 10};
    static auto constexpr obstacle = Box<TypeParam> {
        {1, 1},
        {1, 1},
    };

    ASSERT_THAT(get_colliding_edges(start, delta_position, obstacle), Eq(EdgeType::BOTH));
}

TYPED_TEST_P(CollisionTypeFunction, DetectsTopRightObstaclesMissingAreaAsNone)
{
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        {1, 1},
    };
    static auto constexpr delta_position = Vector<TypeParam> {10, 10};

    static auto constexpr barely_too_far_obstacle = Box<TypeParam> {
        {11, 11},
        {1, 1},
    };

    ASSERT_THAT(get_colliding_edges(start, delta_position, barely_too_far_obstacle), Eq(EdgeType::NONE));
}

TYPED_TEST_P(CollisionTypeFunction, DetectsTopRightHorizontalCollision)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        size,
    };
    static auto constexpr delta_position = Vector<TypeParam> {10, 10};

    static auto constexpr obstacle = Box<TypeParam> {
        {5, 6},
        size,
    };

    ASSERT_THAT(get_colliding_edges(start, delta_position, obstacle), Eq(EdgeType::HORIZONTAL));
}

TYPED_TEST_P(CollisionTypeFunction, DetectsTopRightVerticallCollision)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        size,
    };
    static auto constexpr delta_position = Vector<TypeParam> {10, 10};

    static auto constexpr obstacle = Box<TypeParam> {
        {6, 5},
        size,
    };

    ASSERT_THAT(get_colliding_edges(start, delta_position, obstacle), Eq(EdgeType::VERTICAL));
}

TYPED_TEST_P(CollisionTypeFunction, DetectsVerticalCollisionOnHorizontalMovement)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        size,
    };
    static auto constexpr positive_delta_position = Vector<TypeParam> {10, 0};
    static auto constexpr positive_direction_obstacle = Box<TypeParam> {
        {5, 0},
        size,
    };
    ASSERT_THAT(get_colliding_edges(start, positive_delta_position, positive_direction_obstacle), Eq(EdgeType::VERTICAL));

    static auto constexpr negative_delta_position = Vector<TypeParam> {-10, 0};
    static auto constexpr negative_direction_obstacle = Box<TypeParam> {
        {-5, 0},
        size,
    };
    ASSERT_THAT(get_colliding_edges(start, negative_delta_position, negative_direction_obstacle), Eq(EdgeType::VERTICAL));
}

TYPED_TEST_P(CollisionTypeFunction, DetectsHorizontalCollisionOnVerticalMovement)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        size,
    };
    static auto constexpr positive_delta_position = Vector<TypeParam> {0, 10};
    static auto constexpr positive_direction_obstacle = Box<TypeParam> {
        {0, 5},
        size,
    };
    ASSERT_THAT(get_colliding_edges(start, positive_delta_position, positive_direction_obstacle), Eq(EdgeType::HORIZONTAL));

    static auto constexpr negative_delta_position = Vector<TypeParam> {0, -10};
    static auto constexpr negative_direction_obstacle = Box<TypeParam> {
        {0, -5},
        size,
    };
    ASSERT_THAT(get_colliding_edges(start, negative_delta_position, negative_direction_obstacle), Eq(EdgeType::HORIZONTAL));
}

REGISTER_TYPED_TEST_CASE_P(CollisionTypeFunction,
    AssertsThatObjectsDontAlreadyCollide,
    DetectsTopRightOnEdgeCollisionAsBoth,
    DetectsTopRightObstaclesMissingAreaAsNone,
    DetectsTopRightHorizontalCollision,
    DetectsTopRightVerticallCollision,
    DetectsVerticalCollisionOnHorizontalMovement,
    DetectsHorizontalCollisionOnVerticalMovement
);


INSTANTIATE_TYPED_TEST_CASE_P(CollsionTypeFunctionTest, CollisionTypeFunction, aabb_testing::types_to_test);
