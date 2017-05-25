#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

#include <cassert>

namespace
{
    constexpr bool collide_on_axis(double a_pos, double a_size, double b_pos, double b_size)
    {
        return a_pos < b_pos + b_size && b_pos < a_pos + a_size;
    }
}

namespace aabb
{
    struct Vector
    {
        double x;
        double y;
    };

    constexpr Vector & operator += (Vector & a, Vector const & b)
    {
        a.x += b.x;
        a.y += b.y;

        return a;
    }

    constexpr Vector operator + (Vector const & a, Vector const & b)
    {
        auto summand = a;
        return summand += b;
    }

    constexpr Vector & operator -= (Vector & a, Vector const & b)
    {
        a.x -= b.x;
        a.y -= b.y;

        return a;
    }

    constexpr Vector operator - (Vector const & a, Vector const & b)
    {
        auto minuend = a;
        return minuend -= b;
    }

    struct Rectangle
    {
        Vector position;
        Vector size;
    };

    constexpr bool collide(Rectangle const & a, Rectangle const & b)
    {
        assert(a.size.x > 0);
        assert(a.size.y > 0);
        assert(b.size.x > 0);
        assert(b.size.y > 0);

        return collide_on_axis(a.position.x, a.size.x, b.position.x, b.size.x)
            && collide_on_axis(a.position.y, a.size.y, b.position.y, b.size.y);
    }
}

#endif // AABB_AABB_HXX_INC

