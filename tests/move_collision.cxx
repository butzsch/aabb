#include <vector>

#include <gtest/gtest.h>

#include "aabb/aabb.hxx"
#include "aabb_testing.hxx"

using namespace aabb;

template<typename T>
class MoveCollisionFunction
    : public testing::Test
{
};

TYPED_TEST_CASE_P(MoveCollisionFunction);

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatIdenticalDestinationAndObstacleCollide)
{
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, Vector<TypeParam> { 1, 1 }};
    static auto constexpr delta_position = Vector<TypeParam> {2, 2};
    static auto constexpr obstacle = Box<TypeParam> {
        start.position + delta_position,
        start.size
    };

    ASSERT_TRUE(would_collide(start, delta_position, obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesOutsideTopRightOuterBoundingBoxDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {2, 2};

    static auto constexpr far_away_obstacle = Box<TypeParam> {start.position + delta_position + Vector<TypeParam> { 5, 5 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, far_away_obstacle));

    static auto constexpr touching_destination_obstacle = Box<TypeParam> {start.position + delta_position + size, size};
    ASSERT_FALSE(would_collide(start, delta_position, touching_destination_obstacle));

    static auto constexpr behind_start_obstacle = Box<TypeParam> {start.position - size, size};
    ASSERT_FALSE(would_collide(start, delta_position, behind_start_obstacle));

    static auto constexpr top_left_obstacle = Box<TypeParam> {start.position - size + Vector<TypeParam> { 0, delta_position.y }, size};
    ASSERT_FALSE(would_collide(start, delta_position, top_left_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesOnTopRightDiagonalCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {2, 2};

    static auto constexpr in_middle_obstacle = Box<TypeParam> {
        delta_position / static_cast<TypeParam>(2),
        size
    };

    ASSERT_TRUE(would_collide(start, delta_position, in_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesOutsideBottomLeftOuterBoundingBoxDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {-2, -2};
    static auto constexpr obstacle = Box<TypeParam> {Vector<TypeParam> { 2, 2 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesBelowTopRightDiagonalAreaDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {3, 3};

    static auto constexpr below_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { 2, 0 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<TypeParam> {
        Vector<TypeParam> { 3, 1 },
        Vector<TypeParam> { 5, 1 }
    };
    ASSERT_FALSE(would_collide(start, delta_position, above_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesAboveTopRightDiagonalAreaDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {3, 3};

    static auto constexpr below_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { 0, 2 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<TypeParam> {
        Vector<TypeParam> { 0, 3 },
        Vector<TypeParam> { 2, 1 }
    };
    ASSERT_FALSE(would_collide(start, delta_position, above_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesBelowBottomLeftDiagonalAreaDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {-3, -3};

    static auto constexpr below_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { -1, -3 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { 0, 1 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, above_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesAboveBottomLeftDiagonalAreaDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {-3, -3};

    static auto constexpr below_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { -3, -1 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { -2, 0 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, above_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesOnBottomRightDiagonalCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {10, -10};

    static auto constexpr in_middle_obstacle = Box<TypeParam> {
        delta_position / static_cast<TypeParam>(2),
        size
    };

    ASSERT_TRUE(would_collide(start, delta_position, in_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesOnTopLeftDiagonalCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {-10, 10};

    static auto constexpr in_middle_obstacle = Box<TypeParam> {
        delta_position / static_cast<TypeParam>(2),
        size
    };

    ASSERT_TRUE(would_collide(start, delta_position, in_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatOverlappingStartAndObstacleCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};

    auto const delta_positions = std::vector<Vector<TypeParam>> {
        Vector<TypeParam> { 1, 1 },
        Vector<TypeParam> { 1, -1 },
        Vector<TypeParam> { -1, -1 },
        Vector<TypeParam> { -1, 1 }
    };

    for(auto const & delta_position : delta_positions)
    {
        auto const obstacle = Box<TypeParam> {
            delta_position / static_cast<TypeParam>(2),
            size
        };
        ASSERT_TRUE(would_collide(start, delta_position, obstacle));
    }
}

TYPED_TEST_P(MoveCollisionFunction, ReturnsThatObstaclesAboveTopLeftDiagonalAreaDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {-3, 3};

    static auto constexpr below_middle_obstacle = Box<TypeParam> {Vector<TypeParam> { 0, 2 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<TypeParam> {
        Vector<TypeParam> { -1, 3 },
        Vector<TypeParam> { 2, 1 }
    };
    ASSERT_FALSE(would_collide(start, delta_position, above_middle_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ProcessesHorizontalMovement)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {10, 0};

    static auto constexpr in_obstacle = Box<TypeParam> {Vector<TypeParam> { 5, 0 }, size};
    ASSERT_TRUE(would_collide(start, delta_position, in_obstacle));

    static auto constexpr up_obstacle = Box<TypeParam> {Vector<TypeParam> { 5, 1 }, size};
    ASSERT_TRUE(would_collide(start, delta_position, up_obstacle));

    static auto constexpr down_obstacle = Box<TypeParam> {Vector<TypeParam> {5, -2 }, Vector<TypeParam> { 1, 10 }};
    ASSERT_TRUE(would_collide(start, delta_position, down_obstacle));

    static auto constexpr above_obstacle = Box<TypeParam> {Vector<TypeParam> { 5, 2 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, above_obstacle));

    static auto constexpr out_obstacle = Box<TypeParam> {Vector<TypeParam> { 15, 0 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, out_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, ProcessesVerticalMovement)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr delta_position = Vector<TypeParam> {0, 10};

    static auto constexpr in_obstacle = Box<TypeParam> {Vector<TypeParam> { 0, 5 }, size};
    ASSERT_TRUE(would_collide(start, delta_position, in_obstacle));

    static auto constexpr out_obstacle = Box<TypeParam> {Vector<TypeParam> { 0, 12 }, size};
    ASSERT_FALSE(would_collide(start, delta_position, out_obstacle));

    static auto constexpr left_obstacle = Box<TypeParam> {Vector<TypeParam> { -10, 5 }, Vector<TypeParam> { 20, 1 }};
    ASSERT_TRUE(would_collide(start, delta_position, left_obstacle));

    static auto constexpr right_obstacle = Box<TypeParam> {Vector<TypeParam> { 1, 5 }, size};
    ASSERT_TRUE(would_collide(start, delta_position, right_obstacle));
}

TYPED_TEST_P(MoveCollisionFunction, WorksWithFlatMovement)
{
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr start = Box<TypeParam> {
        {0, 0},
        size,
    };
    static auto constexpr delta_position = Vector<TypeParam> {-10, -2};
    static auto constexpr obstacle = Box<TypeParam> {
        {-5, -2},
        size,
    };

    ASSERT_TRUE(would_collide(start, delta_position, obstacle));
}

REGISTER_TYPED_TEST_CASE_P(MoveCollisionFunction,
    ReturnsThatIdenticalDestinationAndObstacleCollide,
    ReturnsThatObstaclesOutsideTopRightOuterBoundingBoxDontCollide,
    ReturnsThatObstaclesOnTopRightDiagonalCollide,
    ReturnsThatObstaclesOutsideBottomLeftOuterBoundingBoxDontCollide,
    ReturnsThatObstaclesBelowTopRightDiagonalAreaDontCollide,
    ReturnsThatObstaclesAboveTopRightDiagonalAreaDontCollide,
    ReturnsThatObstaclesBelowBottomLeftDiagonalAreaDontCollide,
    ReturnsThatObstaclesAboveBottomLeftDiagonalAreaDontCollide,
    ReturnsThatObstaclesOnBottomRightDiagonalCollide,
    ReturnsThatObstaclesOnTopLeftDiagonalCollide,
    ReturnsThatOverlappingStartAndObstacleCollide,
    ReturnsThatObstaclesAboveTopLeftDiagonalAreaDontCollide,
    ProcessesHorizontalMovement,
    ProcessesVerticalMovement,
    WorksWithFlatMovement
);

INSTANTIATE_TYPED_TEST_CASE_P(MoveCollsionFunctionTest, MoveCollisionFunction, aabb_testing::types_to_test);
