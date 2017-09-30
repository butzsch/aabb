#ifndef AABB_ALGORITHM_HXX_INC
#define AABB_ALGORITHM_HXX_INC

#include "box_helper.hxx"

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
        constexpr T abs(T x)
        {
            return x < 0 ? -x : x;
        }

        template<typename Box, typename Vector>
        constexpr auto get_outer_box(Box const & start, Vector const & delta_position)
        {
            auto const destination = plus_position(start, delta_position);

            auto const outer_left = std::min(get_left(start), get_left(destination));
            auto const outer_right = std::max(get_right(start), get_right(destination));
            auto const outer_top = std::max(get_top(start), get_top(destination));
            auto const outer_bottom = std::min(get_bottom(start), get_bottom(destination));

            return box_from_edges<Box>(outer_left, outer_bottom, outer_right, outer_top);
        }

        enum class Position
        {
            BELOW,
            ABOVE,
            EQUAL
        };

        template<typename Vector>
        constexpr Position get_position_target_to_delta(
            Vector const & start_point,
            Vector const & delta_position,
            Vector const & target_point
        )
        {
            auto const wanted_delta = target_point - start_point;

            auto const a = abs(wanted_delta.x()) * delta_position.y();
            auto const b = wanted_delta.y() * abs(delta_position.x());

            if(a > b)
                return Position::BELOW;

            return (a < b) ? Position::ABOVE : Position::EQUAL;
        }

        template<typename Box, typename Vector>
        constexpr bool is_above_low_diagonal(
            Box const & start,
            Box const & obstacle,
            Vector const & delta_position
        )
        {
            assert(delta_position.x() != 0);
            assert(delta_position.y() != 0);

            auto const upwards = (delta_position.x() > 0) == (delta_position.y() > 0);
            auto const start_point = upwards ? get_bottom_right(start) : get_bottom_left(start);
            auto const target_point = upwards ? get_top_left(obstacle) : get_top_right(obstacle);

            if(delta_position.x() > 0)
            {
                if(target_point.x() < start_point.x())
                    return true;
            }
            else
            {
                if(target_point.x() > start_point.x())
                    return true;
            }

            return get_position_target_to_delta(start_point, delta_position, target_point) == Position::ABOVE;
        }

        template<typename Box, typename Vector>
        constexpr bool is_below_high_diagonal(
            Box const & start,
            Box const & obstacle,
            Vector const & delta_position
        )
        {
            assert(delta_position.x() != 0);
            assert(delta_position.y() != 0);

            auto const upwards = (delta_position.x() > 0) == (delta_position.y() > 0);
            auto const start_point = upwards ? get_top_left(start) : get_top_right(start);
            auto const target_point = upwards ? get_bottom_right(obstacle) : get_bottom_left(obstacle);

            if(delta_position.x() > 0)
            {
                if(target_point.x() < start_point.x())
                    return true;
            }
            else
            {
                if(target_point.x() > start_point.x())
                    return true;
            }

            return get_position_target_to_delta(start_point, delta_position, target_point) == Position::BELOW;
        }

        template<typename Box, typename Vector>
        constexpr bool is_in_limited_area(
            Box const & start,
            Vector const & delta_position,
            Box const & obstacle
        )
        {
            assert(delta_position.x() != 0);
            assert(delta_position.y() != 0);

            return is_above_low_diagonal(start, obstacle, delta_position) && is_below_high_diagonal(start, obstacle, delta_position);
        }

        template<typename Box, typename Vector>
        constexpr auto get_start_point_for_colliding_edges(Box const & start, Vector const & delta_position)
        {
            assert(delta_position.x() != 0);
            assert(delta_position.y() != 0);
            auto const upwards = delta_position.y() > 0;
            if(delta_position.x() > 0)
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

        template<typename Box, typename Vector>
        constexpr auto get_obstacle_point_for_colliding_edges(Box const & obstacle, Vector const & delta_position)
        {
            assert(delta_position.x() != 0);
            assert(delta_position.y() != 0);
            auto const upwards = delta_position.y() > 0;
            if(delta_position.x() > 0)
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
}

#endif // AABB_ALGORITHM_HXX_INC
