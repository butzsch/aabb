#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

#include <algorithm>
#include <cassert>

#include "Box.hxx"
#include "Vector.hxx"

namespace
{
    template<typename T>
    constexpr bool does_collide_on_axis(T a_low, T a_high, T b_low, T b_high)
    {
        return a_low < b_high && b_low < a_high;
    }

    template<typename T>
    constexpr void assert_positive_size(aabb::Box<T> const & x)
    {
        assert(x.size.x > 0);
        assert(x.size.y > 0);
    }

    template<typename T>
    constexpr T abs(T x)
    {
        return x < 0 ? -x : x;
    }

    template<typename T>
    constexpr aabb::Box<T> get_outer_box(aabb::Box<T> const & start, aabb::Vector<T> const & delta_position)
    {
        assert_positive_size(start);

        auto const outer_position = aabb::Vector<T> {
            start.position.x + std::min(delta_position.x, static_cast<T>(0)),
            start.position.y + std::min(delta_position.y, static_cast<T>(0)),
        };

        return {
            outer_position,
            aabb::Vector<T> {
            start.size.x + abs(delta_position.x),
                start.size.y + abs(delta_position.y)
        }
        };
    }

    enum class Position
    {
        BELOW,
        ABOVE,
        EQUAL
    };

    template<typename T>
    constexpr Position get_position(
        aabb::Vector<T> const & start_point,
        T slope,
        aabb::Vector<T> const & target_point
    )
    {
        auto const result_y = slope * (target_point.x - start_point.x) + start_point.y;
        if(result_y < target_point.y)
            return Position::ABOVE;
        if(result_y > target_point.y)
            return Position::BELOW;

        return Position::EQUAL;
    }

    template<typename T>
    constexpr bool is_above_low_diagonal(
        aabb::Box<T> const & start,
        aabb::Box<T> const & obstacle,
        T slope
    )
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        auto const upwards = slope > 0;
        auto const start_point = upwards ? get_bottom_right(start) : get_bottom_left(start);
        auto const target_point = upwards ? get_top_left(obstacle) : get_top_right(obstacle);

        return get_position(start_point, slope, target_point) == Position::ABOVE;
    }

    template<typename T>
    constexpr bool is_below_high_diagonal(
        aabb::Box<T> const & start,
        aabb::Box<T> const & obstacle,
        T slope
    )
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        auto const upwards = slope > 0;
        auto const start_point = upwards ? get_top_left(start) : get_top_right(start);
        auto const target_point = upwards ? get_bottom_right(obstacle) : get_bottom_left(obstacle);

        return get_position(start_point, slope, target_point) == Position::BELOW;
    }

    template<typename T>
    constexpr bool is_in_limited_area(
        aabb::Box<T> const & start,
        aabb::Vector<T> const & delta_position,
        aabb::Box<T> const & obstacle
    )
    {
        assert(delta_position.x != 0);

        auto const slope = delta_position.y / delta_position.x;
        return is_above_low_diagonal(start, obstacle, slope) && is_below_high_diagonal(start, obstacle, slope);
    }
}

namespace aabb
{
    template<typename T>
    constexpr bool does_collide(Box<T> const & a, Box<T> const & b)
    {
        assert_positive_size(a);
        assert_positive_size(b);

        return does_collide_on_axis(get_left(a), get_right(a), get_left(b), get_right(b))
            && does_collide_on_axis(get_bottom(a), get_top(a), get_bottom(b), get_top(b));
    }

    template<typename T>
    constexpr bool would_collide(
        Box<T> const & start,
        Vector<T> const & delta_position,
        Box<T> const & obstacle
    )
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        auto const outer_box = get_outer_box(start, delta_position);
        return does_collide(obstacle, outer_box)
            && (delta_position.x == 0 || delta_position.y == 0 || is_in_limited_area(start, delta_position, obstacle));
    }

    enum EdgeType
    {
        NONE = 0,
        HORIZONTAL = 1,
        VERTICAL = 2,
        BOTH = HORIZONTAL | VERTICAL
    };

    template<typename T>
    constexpr EdgeType get_colliding_edges(
        Box<T> const & start,
        Vector<T> const & delta_position,
        Box<T> const & obstacle
    )
    {
        assert(!does_collide(start, obstacle));
        if(!would_collide(start, delta_position, obstacle))
            return EdgeType::NONE;

        if(delta_position.x == 0)
            return EdgeType::HORIZONTAL;

        if(delta_position.y == 0)
            return EdgeType::VERTICAL;

        auto const start_point = get_top_right(start);
        auto const target_point = get_bottom_left(obstacle);
        auto const position = get_position(start_point, delta_position.y / delta_position.x, target_point);
        switch(position)
        {
            case Position::BELOW: return EdgeType::VERTICAL;
            case Position::ABOVE: return EdgeType::HORIZONTAL;
            case Position::EQUAL: return EdgeType::BOTH;
        }
    }
}

#endif // AABB_AABB_HXX_INC

