#include <gtest/gtest.h>

#include "aabb/aabb.hxx"

using namespace aabb;

TEST(IdenticalRectangles, Collide)
{
    static auto constexpr a = Box<int> { Vector<int> {0, 0}, Vector<int> {1, 1} };
    static auto constexpr b = a;

    ASSERT_TRUE(collide(a, b));
    ASSERT_TRUE(collide(b, a));
}

TEST(HorizontallShiftedRectangles, DontCollide)
{
    static auto constexpr y = 0;
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr a = Box<int>{ Vector<int> { 0, y }, size };
    static auto constexpr b = Box<int>{ Vector<int> { 5, y }, size };

    ASSERT_FALSE(collide(a, b));
    ASSERT_FALSE(collide(b, a));
}

TEST(VerticallyShiftedRectangles, DontCollide)
{
    static auto constexpr x = 0;
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr a = Box<int>{ Vector<int> { x, 0 }, size };
    static auto constexpr b = Box<int>{ Vector<int> { x, 5 }, size };

    ASSERT_FALSE(collide(a, b));
    ASSERT_FALSE(collide(b, a));
}

TEST(HorizontallyOverlappingRectangles, Collide)
{
    static auto constexpr y = 5;
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr a = Box<int>{ Vector<int> { 0, y }, size };
    static auto constexpr b = Box<int>{ Vector<int> { 0, y }, size };

    ASSERT_TRUE(collide(a, b));
    ASSERT_TRUE(collide(b, a));
}

TEST(VerticallyOverlappingRectangles, Collide)
{
    static auto constexpr x = 5;
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr a = Box<int>{ Vector<int> { x, 0 }, size };
    static auto constexpr b = Box<int>{ Vector<int> { x, 0 }, size };

    ASSERT_TRUE(collide(a, b));
    ASSERT_TRUE(collide(b, a));
}

TEST(RectagnlesWithSharedEdges, DontCollide)
{
    static auto constexpr size = Vector<int>{ 1, 1 };
    static auto constexpr a = Box<int>{ Vector<int> { 0, 0 }, size };
    static auto constexpr b = Box<int>{ Vector<int> { 1, 1 }, size };

    ASSERT_FALSE(collide(a, b));
    ASSERT_FALSE(collide(b, a));
}

