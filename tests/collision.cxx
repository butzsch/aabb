#include <gtest/gtest.h>

#include "aabb/aabb.hxx"
#include "aabb_testing.hxx"

using namespace aabb;
using namespace aabb_testing;

template<typename T>
class CollisionFunction
    : public testing::Test
{
};

TYPED_TEST_CASE_P(CollisionFunction);

TYPED_TEST_P(CollisionFunction, ReturnsThatIdenticalRectanglesCollide)
{
    static auto constexpr a = Box<TypeParam> {Vector<TypeParam> {0, 0}, Vector<TypeParam> {1, 1}};
    static auto constexpr b = a;

    ASSERT_TRUE(does_collide(a, b));
    ASSERT_TRUE(does_collide(b, a));
}

TYPED_TEST_P(CollisionFunction, ReturnsThatHorizontallShiftedRectanglesDontCollide)
{
    static auto constexpr y = static_cast<TypeParam>(0);
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr a = Box<TypeParam> {Vector<TypeParam> { 0, y }, size};
    static auto constexpr b = Box<TypeParam> {Vector<TypeParam> { 5, y }, size};

    ASSERT_FALSE(does_collide(a, b));
    ASSERT_FALSE(does_collide(b, a));
}

TYPED_TEST_P(CollisionFunction, ReturnsThatVerticallyShiftedRectanglesDontCollide)
{
    static auto constexpr x = static_cast<TypeParam>(0);
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr a = Box<TypeParam> {Vector<TypeParam> { x, 0 }, size};
    static auto constexpr b = Box<TypeParam> {Vector<TypeParam> { x, 5 }, size};

    ASSERT_FALSE(does_collide(a, b));
    ASSERT_FALSE(does_collide(b, a));
}

TYPED_TEST_P(CollisionFunction, ReturnsThatHorizontallyOverlappingRectanglesCollide)
{
    static auto constexpr y = static_cast<TypeParam>(5);
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr a = Box<TypeParam> {Vector<TypeParam> { 0, y }, size};
    static auto constexpr b = Box<TypeParam> {Vector<TypeParam> { 1, y }, size};

    ASSERT_TRUE(does_collide(a, b));
    ASSERT_TRUE(does_collide(b, a));
}

TYPED_TEST_P(CollisionFunction, ReturnsThatVerticallyOverlappingRectanglesCollide)
{
    static auto constexpr x = static_cast<TypeParam>(5);
    static auto constexpr size = Vector<TypeParam> {2, 2};
    static auto constexpr a = Box<TypeParam> {Vector<TypeParam> { x, 0 }, size};
    static auto constexpr b = Box<TypeParam> {Vector<TypeParam> { x, 1 }, size};

    ASSERT_TRUE(does_collide(a, b));
    ASSERT_TRUE(does_collide(b, a));
}

TYPED_TEST_P(CollisionFunction, ReturnsThatRectagnlesWithSharedEdgesDontCollide)
{
    static auto constexpr size = Vector<TypeParam> {1, 1};
    static auto constexpr a = Box<TypeParam> {Vector<TypeParam> { 0, 0 }, size};
    static auto constexpr b = Box<TypeParam> {Vector<TypeParam> { 1, 1 }, size};

    ASSERT_FALSE(does_collide(a, b));
    ASSERT_FALSE(does_collide(b, a));
}

REGISTER_TYPED_TEST_CASE_P(CollisionFunction,
    ReturnsThatIdenticalRectanglesCollide,
    ReturnsThatHorizontallShiftedRectanglesDontCollide,
    ReturnsThatVerticallyShiftedRectanglesDontCollide,
    ReturnsThatHorizontallyOverlappingRectanglesCollide,
    ReturnsThatVerticallyOverlappingRectanglesCollide,
    ReturnsThatRectagnlesWithSharedEdgesDontCollide
);

INSTANTIATE_TYPED_TEST_CASE_P(CollsionFunctionTest, CollisionFunction, aabb_testing::types_to_test);
