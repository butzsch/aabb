#include <gtest/gtest.h>

#include "aabb.hxx"

using namespace aabb;

TEST(IdenticalDestinationAndObstacle, Collide)
{
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, Vector { 1.0, 1.0 } };
    static auto constexpr delta_position = Vector { 2.0, 2.0 };
    static auto constexpr obstacle = Rectangle {
        start.position + delta_position,
        start.size
    };

    ASSERT_TRUE(move_collide(start, delta_position, obstacle));
}

TEST(ObstaclesOutsideTopRightOuterBoundingBox, DontCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 2.0, 2.0 };

    static auto constexpr far_away_obstacle = Rectangle { start.position + delta_position + Vector { 5.0, 5.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, far_away_obstacle));

    static auto constexpr touching_destination_obstacle = Rectangle { start.position + delta_position + size, size };
    ASSERT_FALSE(move_collide(start, delta_position, touching_destination_obstacle));

    static auto constexpr behind_start_obstacle = Rectangle { start.position - size, size };
    ASSERT_FALSE(move_collide(start, delta_position, behind_start_obstacle));

    static auto constexpr top_left_obstacle = Rectangle { start.position - size + Vector { 0.0, delta_position.y }, size};
    ASSERT_FALSE(move_collide(start, delta_position, top_left_obstacle));
}

TEST(ObstaclesOnTopRightDiagonal, Collide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 2.0, 2.0 };

    static auto constexpr in_middle_obstacle = Rectangle {
        delta_position / 2,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(ObstacleOutsideBottomLeftOuterBoundingBox, DoesntCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { -2.0, -2.0 };
    static auto constexpr obstacle = Rectangle { Vector { 2.0, 2.0 } , size };
    ASSERT_FALSE(move_collide(start, delta_position, obstacle));
}

TEST(ObstaclesBelowTopRightDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 3.0, 3.0 };

    static auto constexpr below_middle_obstacle = Rectangle { Vector { 2.0, 0.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Rectangle {
        Vector { 3.0, 1.0 },
        Vector { 5.0, 1.0 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesAboveTopRightDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 3.0, 3.0 };

    static auto constexpr below_middle_obstacle = Rectangle { Vector { 0.0, 2.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Rectangle {
        Vector { 0.0, 3.0 },
        Vector { 2.0, 1.0 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));
}

TEST(ObstaclesBelowBottomLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { -3.0, -3.0 };

    static auto constexpr below_middle_obstacle = Rectangle { Vector { -1.0, -3.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Rectangle { Vector { 0.0, 1.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));
}

TEST(ObstaclesAboveBottomLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { -3.0, -3.0 };

    static auto constexpr below_middle_obstacle = Rectangle { Vector { -3.0, -1.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Rectangle { Vector { -2.0, 0.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesOnBottomRightDiagonal, Collide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 10.0, -10.0 };

    static auto constexpr in_middle_obstacle = Rectangle {
        delta_position / 2,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

