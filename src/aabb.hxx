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

    constexpr bool is_above_low_diagonal(
        aabb::Rectangle const & start,
        aabb::Vector const & delta_position,
        aabb::Rectangle const & obstacle
    )
    {
        auto const slope = delta_position.y / delta_position.x;
        if(slope > 0)
        {
            auto const delta_y = slope * (obstacle.position.x - start.position.x - start.size.x);
            return obstacle.position.y + obstacle.size.y > start.position.y + delta_y;
        }

        auto const delta_y = slope * (obstacle.position.x + obstacle.size.x - start.position.x);
        return obstacle.position.y + obstacle.size.y > start.position.y + delta_y;
    }

    constexpr bool is_below_high_diagonal(
        aabb::Rectangle const & start,
        aabb::Vector const & delta_position,
        aabb::Rectangle const & obstacle
    )
    {
        auto const slope = delta_position.y / delta_position.x;
        if(slope > 0)
        {
            auto const delta_y = slope * (obstacle.position.x + obstacle.size.x - start.position.y);
            return obstacle.position.y < start.position.y + start.size.y + delta_y;
        }

        auto const delta_y = slope * (obstacle.position.x - start.position.x - start.size.x);
        return obstacle.position.y < start.position.y + start.size.y + delta_y;
    }

    constexpr bool collide_diagonally(
        aabb::Rectangle const & start,
        aabb::Vector const & delta_position,
        aabb::Rectangle const & obstacle
    )
    {
        return is_above_low_diagonal(start, delta_position, obstacle)
            && is_below_high_diagonal(start, delta_position, obstacle);
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
        return collide(obstacle, outer_box) && collide_diagonally(start, delta_position, obstacle);
    }
}

#endif // AABB_AABB_HXX_INC
