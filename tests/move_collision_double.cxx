#include <vector>

#include <gtest/gtest.h>

#include "aabb/aabb.hxx"

using namespace aabb;

TEST(IdenticalDestinationAndObstacle, Collide)
{
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, Vector<double> { 1.0, 1.0 } };
    static auto constexpr delta_position = Vector<double>{ 2.0, 2.0 };
    static auto constexpr obstacle = Box<double>{
        start.position + delta_position,
        start.size
    };

    ASSERT_TRUE(move_collide(start, delta_position, obstacle));
}

TEST(ObstaclesOutsideTopRightOuterBoundingBox, DontCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 2.0, 2.0 };

    static auto constexpr far_away_obstacle = Box<double>{ start.position + delta_position + Vector<double> { 5.0, 5.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, far_away_obstacle));

    static auto constexpr touching_destination_obstacle = Box<double>{ start.position + delta_position + size, size };
    ASSERT_FALSE(move_collide(start, delta_position, touching_destination_obstacle));

    static auto constexpr behind_start_obstacle = Box<double>{ start.position - size, size };
    ASSERT_FALSE(move_collide(start, delta_position, behind_start_obstacle));

    static auto constexpr top_left_obstacle = Box<double>{ start.position - size + Vector<double> { 0.0, delta_position.y }, size};
    ASSERT_FALSE(move_collide(start, delta_position, top_left_obstacle));
}

TEST(ObstaclesOnTopRightDiagonal, Collide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 2.0, 2.0 };

    static auto constexpr in_middle_obstacle = Box<double>{
        delta_position / 2.0,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(ObstacleOutsideBottomLeftOuterBoundingBox, DoesntCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ -2.0, -2.0 };
    static auto constexpr obstacle = Box<double>{ Vector<double> { 2.0, 2.0 } , size };
    ASSERT_FALSE(move_collide(start, delta_position, obstacle));
}

TEST(ObstaclesBelowTopRightDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 3.0, 3.0 };

    static auto constexpr below_middle_obstacle = Box<double>{ Vector<double> { 2.0, 0.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<double>{
        Vector<double> { 3.0, 1.0 },
        Vector<double> { 5.0, 1.0 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesAboveTopRightDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 3.0, 3.0 };

    static auto constexpr below_middle_obstacle = Box<double>{ Vector<double> { 0.0, 2.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<double>{
        Vector<double> { 0.0, 3.0 },
        Vector<double> { 2.0, 1.0 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesBelowBottomLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ -3.0, -3.0 };

    static auto constexpr below_middle_obstacle = Box<double>{ Vector<double> { -1.0, -3.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<double>{ Vector<double> { 0.0, 1.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));
}

TEST(ObstaclesAboveBottomLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ -3.0, -3.0 };

    static auto constexpr below_middle_obstacle = Box<double>{ Vector<double> { -3.0, -1.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<double>{ Vector<double> { -2.0, 0.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(ObstaclesOnBottomRightDiagonal, Collide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 10.0, -10.0 };

    static auto constexpr in_middle_obstacle = Box<double>{
        delta_position / 2.0,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(ObstaclesOnTopLeftDiagonal, Collide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ -10.0, 10.0 };

    static auto constexpr in_middle_obstacle = Box<double>{
        delta_position / 2.0,
        size
    };

    ASSERT_TRUE(move_collide(start, delta_position, in_middle_obstacle));
}

TEST(OverlappingStartAndObstacle, Collide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };

    auto const delta_positions = std::vector<Vector<double>> {
        Vector<double> { 1.0, 1.0 },
        Vector<double> { 1.0, -1.0 },
        Vector<double> { -1.0, -1.0 },
        Vector<double> { -1.0, 1.0 }
    };

    for(auto const & delta_position : delta_positions)
    {
        auto const obstacle = Box<double> { delta_position / 2.0, size };
        ASSERT_TRUE(move_collide(start, delta_position, obstacle));
    }
}

TEST(ObstaclesAboveTopLeftDiagonalArea, DontCollide)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ -3.0, 3.0 };

    static auto constexpr below_middle_obstacle = Box<double>{ Vector<double> { 0.0, 2.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, below_middle_obstacle));

    static auto constexpr above_middle_obstacle = Box<double>{
        Vector<double> { -1.0, 3.0 },
        Vector<double> { 2.0, 1.0 }
    };
    ASSERT_FALSE(move_collide(start, delta_position, above_middle_obstacle));
}

TEST(HorizontalMovement, WorksCorrectly)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 10.0, 0.0 };

    static auto constexpr in_obstacle = Box<double>{ Vector<double> { 5.0, 0.0 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, in_obstacle));

    static auto constexpr up_obstacle = Box<double>{ Vector<double> { 5.0, 0.5 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, up_obstacle));

    static auto constexpr down_obstacle = Box<double>{ Vector<double> {5.0, -2.0 }, Vector<double> { 1.0, 10.0 } };
    ASSERT_TRUE(move_collide(start, delta_position, down_obstacle));

    static auto constexpr above_obstacle = Box<double>{ Vector<double> { 5.0, 1.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, above_obstacle));

    static auto constexpr out_obstacle = Box<double>{ Vector<double> { 15.0, 0.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, out_obstacle));
}

TEST(VerticalMovement, WorksCorrectly)
{
    static auto constexpr size = Vector<double>{ 1.0, 1.0 };
    static auto constexpr start = Box<double>{ Vector<double> { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector<double>{ 0.0, 10.0 };

    static auto constexpr in_obstacle = Box<double>{ Vector<double> { 0.0, 5.0 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, in_obstacle));

    static auto constexpr out_obstacle = Box<double>{ Vector<double> { 0.0, 11.0 }, size };
    ASSERT_FALSE(move_collide(start, delta_position, out_obstacle));

    static auto constexpr left_obstacle = Box<double>{ Vector<double> { -10.0, 5.0 }, Vector<double> { 20.0, 1.0 } };
    ASSERT_TRUE(move_collide(start, delta_position, left_obstacle));

    static auto constexpr right_obstacle = Box<double>{ Vector<double> { 0.5, 5.0 }, size };
    ASSERT_TRUE(move_collide(start, delta_position, right_obstacle));
}

