#include <vector>

#include <gtest/gtest.h>

#include "aabb.hxx"

using namespace aabb;

TEST(IdenticalDestinationAndObstacle, Collide)
{
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, Vector<int> { 1, 1 } };
    static auto constexpr delta_position = Vector<int>{ 2, 2 };
    static auto constexpr obstacle = Box<int>{
        start.position + delta_position,
        start.size
    };

    ASSERT_TRUE(move_collide(start, delta_position, obstacle));
}

TEST(ObstaclesOutsideTopRightOuterBoundingBox, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 2, 2 };

    static auto constexpr far_away_obstacle = Box<int>{ start.position + delta_position + Vector<int> { 5, 5 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, far_away_obstacle));

    static auto constexpr touching_destination_obstacle = Box<int>{ start.position + delta_position + size, size };
    ASSERT_FALSE(move_collide(start, delta_position, touching_destination_obstacle));

    static auto constexpr behind_start_obstacle = Box<int>{ start.position - size, size };
    ASSERT_FALSE(move_collide(start, delta_position, behind_start_obstacle));

    static auto constexpr top_left_obstacle = Box<int>{ start.position - size + Vector<int> { 0, delta_position.y }, size};
    ASSERT_FALSE(move_collide(start, delta_position, top_left_obstacle));
}

TEST(ObstaclesOnTopRightDiagonal, Collide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 2, 2 };

    static auto constexpr in_middle_obstacle = Box<int>{
        delta_position / 2,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(ObstacleOutsideBottomLeftOuterBoundingBox, DoesntCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ -2, -2 };
    static auto constexpr obstacle = Box<int>{ Vector<int> { 2, 2 } , size };
    ASSERT_FALSE(move_collide(start, delta_position, obstacle));
}

TEST(ObstaclesBelowTopRightDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 3, 3 };

    static auto constexpr below_middle_obstacle = Box<int>{ Vector<int> { 2, 0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<int>{
        Vector<int> { 3, 1 },
        Vector<int> { 5, 1 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesAboveTopRightDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 3, 3 };

    static auto constexpr below_middle_obstacle = Box<int>{ Vector<int> { 0, 2 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<int>{
        Vector<int> { 0, 3 },
        Vector<int> { 2, 1 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesBelowBottomLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ -3, -3 };

    static auto constexpr below_middle_obstacle = Box<int>{ Vector<int> { -1, -3 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<int>{ Vector<int> { 0, 1 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));
}

TEST(ObstaclesAboveBottomLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ -3, -3 };

    static auto constexpr below_middle_obstacle = Box<int>{ Vector<int> { -3, -1 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<int>{ Vector<int> { -2, 0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesOnBottomRightDiagonal, Collide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 10, -10 };

    static auto constexpr in_middle_obstacle = Box<int>{
        delta_position / 2,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(ObstaclesOnTopLeftDiagonal, Collide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ -10, 10 };

    static auto constexpr in_middle_obstacle = Box<int>{
        delta_position / 2,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(OverlappingStartAndObstacle, Collide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };

    auto const delta_positions = std::vector<Vector<int>> {
        Vector<int> { 1, 1 },
        Vector<int> { 1, -1 },
        Vector<int> { -1, -1 },
        Vector<int> { -1, 1 }
    };

    for(auto const & delta_position : delta_positions)
    {
        auto const obstacle = Box<int> { delta_position / 2, size };
        ASSERT_TRUE(move_collide(start, delta_position, obstacle));
    }
}

TEST(ObstaclesAboveTopLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ -3, 3 };

    static auto constexpr below_middle_obstacle = Box<int>{ Vector<int> { 0, 2 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<int>{
        Vector<int> { -1, 3 },
        Vector<int> { 2, 1 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(HorizontalMovement, WorksCorrectly)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 10, 0 };

    static auto constexpr in_obstacle = Box<int>{ Vector<int> { 5, 0 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, in_obstacle));

    static auto constexpr up_obstacle = Box<int>{ Vector<int> { 5, 0 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, up_obstacle));

    static auto constexpr down_obstacle = Box<int>{ Vector<int> {5, -2 }, Vector<int> { 1, 10 } };
    ASSERT_TRUE(move_collide(start, delta_position, down_obstacle));

    static auto constexpr above_obstacle = Box<int>{ Vector<int> { 5, 1 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, above_obstacle));

    static auto constexpr out_obstacle = Box<int>{ Vector<int> { 15, 0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, out_obstacle));
}

TEST(VerticalMovement, WorksCorrectly)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr start = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr delta_position = Vector<int>{ 0, 10 };

    static auto constexpr in_obstacle = Box<int>{ Vector<int> { 0, 5 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, in_obstacle));

    static auto constexpr out_obstacle = Box<int>{ Vector<int> { 0, 11 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, out_obstacle));

    static auto constexpr left_obstacle = Box<int>{ Vector<int> { -10, 5 }, Vector<int> { 20, 1 } };
    ASSERT_TRUE(move_collide(start, delta_position, left_obstacle));

    static auto constexpr right_obstacle = Box<int>{ Vector<int> { 0, 5 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, right_obstacle));
}

