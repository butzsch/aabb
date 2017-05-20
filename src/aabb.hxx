#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

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

    struct Rectangle
    {
        Vector position;
        Vector size;
    };

    constexpr bool collide(Rectangle const & a, Rectangle const & b)
    {
        return collide_on_axis(a.position.x, a.size.x, b.position.x, b.size.x)
            && collide_on_axis(a.position.y, a.size.y, b.position.y, b.size.y);
    }
}

#endif // AABB_AABB_HXX_INC

