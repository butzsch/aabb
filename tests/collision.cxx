#include <gtest/gtest.h>

#include "aabb.hxx"

using namespace aabb;

TEST(IdenticalRectangles, Collide)
{
    static auto constexpr a = Rectangle { Vector {0.0, 0.0}, Vector {1.0, 1.0} };
    static auto constexpr b = a;

    ASSERT_TRUE(collide(a, b));
    ASSERT_TRUE(collide(b, a));
}

TEST(HorizontallShiftedRectangles, DontCollide)
{
    static auto constexpr y = 0.0;
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr a = Rectangle { Vector { 0.0, y }, size };
    static auto constexpr b = Rectangle { Vector { 5.0, y }, size };

    ASSERT_FALSE(collide(a, b));
    ASSERT_FALSE(collide(b, a));
}

TEST(VerticallyShiftedRectangles, DontCollide)
{
    static auto constexpr x = 0.0;
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr a = Rectangle { Vector { x, 0.0 }, size };
    static auto constexpr b = Rectangle { Vector { x, 5.0 }, size };

    ASSERT_FALSE(collide(a, b));
    ASSERT_FALSE(collide(b, a));
}

TEST(HorizontallyOverlappingRectangles, Collide)
{
    static auto constexpr y = 5.0;
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr a = Rectangle { Vector { 0.0, y }, size };
    static auto constexpr b = Rectangle { Vector { 0.5, y }, size };

    ASSERT_TRUE(collide(a, b));
    ASSERT_TRUE(collide(b, a));
}

TEST(VerticallyOverlappingRectangles, Collide)
{
    static auto constexpr x = 5.0;
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr a = Rectangle { Vector { x, 0.0 }, size };
    static auto constexpr b = Rectangle { Vector { x, 0.5 }, size };

    ASSERT_TRUE(collide(a, b));
    ASSERT_TRUE(collide(b, a));
}

TEST(RectagnlesWithSharedEdges, DontCollide)
{
    static auto constexpr size = Vector { 1.0, 1.0 };
    static auto constexpr a = Rectangle { Vector { 0.0, 0.0 }, size };
    static auto constexpr b = Rectangle { Vector { 1.0, 1.0 }, size };

    ASSERT_FALSE(collide(a, b));
    ASSERT_FALSE(collide(b, a));
}

