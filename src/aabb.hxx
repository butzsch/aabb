#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

#include <algorithm>
#include <cassert>
#include <cmath>

#include "Rectangle.hxx"
#include "Vector.hxx"

namespace
{
    constexpr bool collide_on_axis(double a_pos, double a_size, double b_pos, double b_size)
    {
        return a_pos < b_pos + b_size && b_pos < a_pos + a_size;
    }

    constexpr aabb::Rectangle get_outer_box(aabb::Rectangle const & start, aabb::Vector const & delta_position)
    {
        auto const outer_position = aabb::Vector {
            start.position.x + std::min(delta_position.x, 0.0),
            start.position.y + std::min(delta_position.y, 0.0)
        };

        return {
            outer_position,
            aabb::Vector {
                start.size.x + std::abs(delta_position.x),
                start.size.y + std::abs(delta_position.y)
            }
        };
    }
}

namespace aabb
{
    constexpr bool collide(Rectangle const & a, Rectangle const & b)
    {
        assert(a.size.x > 0);
        assert(a.size.y > 0);
        assert(b.size.x > 0);
        assert(b.size.y > 0);

        return collide_on_axis(a.position.x, a.size.x, b.position.x, b.size.x)
            && collide_on_axis(a.position.y, a.size.y, b.position.y, b.size.y);
    }

    constexpr bool move_collide(
        Rectangle const & start,
        Vector const & delta_position,
        Rectangle const & obstacle
    )
    {
        auto const outer_box = get_outer_box(start, delta_position);
        return collide(obstacle, outer_box);
    }
}

#endif // AABB_AABB_HXX_INC

