#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "aabb.hxx"

using namespace aabb;
using namespace testing;

TEST(UnlimitedMovement, IsntNarrowed)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr obstacle = Rectangle { Vector { 10.0, 10.0 }, size };
    static auto constexpr delta_position = Vector { 1.0, 1.0 };

    ASSERT_THAT(get_narrowed_movement(start, delta_position, obstacle), Eq(delta_position));
}

TEST(OnEdgeTopRightMovement, IsNarrowedCorrectly)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 10.0, 10.0 };

    {
        static auto constexpr obstacle = Rectangle { Vector { 5.0, 5.0 }, size };
        static auto constexpr expected_movement = Vector { 5.0, 5.0 };
        ASSERT_THAT(get_narrowed_movement(start, delta_position, obstacle), Eq(expected_movement));
    }

    {
        static auto constexpr obstacle = Rectangle { Vector { 2.0, 2.0 }, size };
        static auto constexpr expected_movement = Vector { 2.0, 2.0 };
        ASSERT_THAT(get_narrowed_movement(start, delta_position, obstacle), Eq(expected_movement));
    }
}

TEST(OverlappingObjectMovement, IsZero)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr start = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr delta_position = Vector { 10.0, 10.0 };
    static auto constexpr obstacle = Rectangle { Vector { 0.5, 0.5 }, size };

    ASSERT_THAT(get_narrowed_movement(start, delta_position, obstacle), Eq(Vector { 0.0, 0.0 }));
}
