#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

#include <algorithm>
#include <cassert>

#include "Box.hxx"
#include "Vector.hxx"

namespace aabb
{
    namespace detail
    {
        template<typename T>
        constexpr bool does_collide_on_axis(T a_low, T a_high, T b_low, T b_high)
        {
            return a_low < b_high && b_low < a_high;
        }

        template<typename T>
        constexpr void assert_positive_size(Box<T> const & x)
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
        constexpr Box<T> get_outer_box(Box<T> const & start, Vector<T> const & delta_position)
        {
            assert_positive_size(start);

            auto const outer_position = Vector<T> {
                start.position.x + std::min(delta_position.x, static_cast<T>(0)),
                start.position.y + std::min(delta_position.y, static_cast<T>(0)),
            };
            auto const outer_size = Vector<T> {
                start.size.x + abs(delta_position.x),
                start.size.y + abs(delta_position.y),
            };

            return {outer_position, outer_size};
        }

        enum class Position
        {
            BELOW,
            ABOVE,
            EQUAL
        };

        template<typename T>
        constexpr Position get_position_target_to_delta(
            Vector<T> const & start_point,
            Vector<T> const & delta_position,
            Vector<T> const & target_point
        )
        {
            auto const wanted_delta = target_point - start_point;

            auto const a = abs(wanted_delta.x) * delta_position.y;
            auto const b = wanted_delta.y * abs(delta_position.x);

            if(a > b)
                return Position::BELOW;

            return (a < b) ? Position::ABOVE : Position::EQUAL;
        }

        template<typename T>
        constexpr bool is_above_low_diagonal(
            Box<T> const & start,
            Box<T> const & obstacle,
            Vector<T> const & delta_position
        )
        {
            assert(delta_position.x != 0);
            assert(delta_position.y != 0);
            assert_positive_size(start);
            assert_positive_size(obstacle);

            auto const upwards = (delta_position.x > 0) == (delta_position.y > 0);
            auto const start_point = upwards ? get_bottom_right(start) : get_bottom_left(start);
            auto const target_point = upwards ? get_top_left(obstacle) : get_top_right(obstacle);

            if(delta_position.x > 0)
            {
                if(target_point.x < start_point.x)
                    return true;
            }
            else
            {
                if(target_point.x > start_point.x)
                    return true;
            }

            return get_position_target_to_delta(start_point, delta_position, target_point) == Position::ABOVE;
        }

        template<typename T>
        constexpr bool is_below_high_diagonal(
            Box<T> const & start,
            Box<T> const & obstacle,
            Vector<T> const & delta_position
        )
        {
            assert(delta_position.x != 0);
            assert(delta_position.y != 0);
            assert_positive_size(start);
            assert_positive_size(obstacle);

            auto const upwards = (delta_position.x > 0) == (delta_position.y > 0);
            auto const start_point = upwards ? get_top_left(start) : get_top_right(start);
            auto const target_point = upwards ? get_bottom_right(obstacle) : get_bottom_left(obstacle);

            if(delta_position.x > 0)
            {
                if(target_point.x < start_point.x)
                    return true;
            }
            else
            {
                if(target_point.x > start_point.x)
                    return true;
            }

            return get_position_target_to_delta(start_point, delta_position, target_point) == Position::BELOW;
        }

        template<typename T>
        constexpr bool is_in_limited_area(
            Box<T> const & start,
            Vector<T> const & delta_position,
            Box<T> const & obstacle
        )
        {
            assert(delta_position.x != 0);
            assert(delta_position.y != 0);
            assert_positive_size(start);
            assert_positive_size(obstacle);

            return is_above_low_diagonal(start, obstacle, delta_position) && is_below_high_diagonal(start, obstacle, delta_position);
        }

        template<typename T>
        constexpr Vector<T> get_start_point_for_colliding_edges(Box<T> const & start, Vector<T> const & delta_position)
        {
            assert(delta_position.x != 0);
            assert(delta_position.y != 0);
            auto const upwards = delta_position.y > 0;
            if(delta_position.x > 0)
            {
                if(upwards)
                    return get_top_right(start);

                return get_bottom_right(start);
            }
            else if(upwards)
            {
                return get_top_left(start);
            }

            return get_bottom_left(start);
        }

        template<typename T>
        constexpr Vector<T> get_obstacle_point_for_colliding_edges(Box<T> const & obstacle, Vector<T> const & delta_position)
        {
            assert(delta_position.x != 0);
            assert(delta_position.y != 0);
            auto const upwards = delta_position.y > 0;
            if(delta_position.x > 0)
            {
                if(upwards)
                    return get_bottom_left(obstacle);

                return get_top_left(obstacle);
            }
            else if(upwards)
            {
                return get_bottom_right(obstacle);
            }

            return get_top_right(obstacle);
        }
    }

    template<typename T>
    constexpr bool does_collide(Box<T> const & a, Box<T> const & b)
    {
        detail::assert_positive_size(a);
        detail::assert_positive_size(b);

        return detail::does_collide_on_axis(get_left(a), get_right(a), get_left(b), get_right(b))
            && detail::does_collide_on_axis(get_bottom(a), get_top(a), get_bottom(b), get_top(b));
    }

    template<typename T>
    constexpr bool would_collide(
        Box<T> const & start,
        Vector<T> const & delta_position,
        Box<T> const & obstacle
    )
    {
        detail::assert_positive_size(start);
        detail::assert_positive_size(obstacle);

        if(does_collide(start, obstacle))
            return true;

        auto const outer_box = detail::get_outer_box(start, delta_position);
        if(!does_collide(obstacle, outer_box))
            return false;

        return delta_position.x == 0 || delta_position.y == 0 || detail::is_in_limited_area(start, delta_position, obstacle);
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

        auto const start_point = detail::get_start_point_for_colliding_edges(start, delta_position);
        auto const target_point = detail::get_obstacle_point_for_colliding_edges(obstacle, delta_position);

        if(delta_position.x > 0)
        {
            if(target_point.x < start_point.x)
                return EdgeType::HORIZONTAL;
        }
        else
        {
            if(target_point.x > start_point.x)
                return EdgeType::HORIZONTAL;
        }


        auto const position = detail::get_position_target_to_delta(start_point, delta_position, target_point);
        auto const upwards = delta_position.y > 0;
        if(position == detail::Position::BELOW)
            return upwards ? EdgeType::VERTICAL : EdgeType::HORIZONTAL;
        if(position == detail::Position::ABOVE)
            return upwards ? EdgeType::HORIZONTAL : EdgeType::VERTICAL;
        return EdgeType::BOTH;
    }
}

#endif // AABB_AABB_HXX_INC

