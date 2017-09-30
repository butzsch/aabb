#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

#include <algorithm>
#include <cassert>
#include <type_traits>

#include "../../src/algorithm.hxx"
#include "../../src/box_helper.hxx"

namespace aabb
{
    template<typename Box>
    constexpr bool does_collide(Box const & a, Box const & b)
    {
        return detail::does_collide_on_axis(detail::get_left(a), detail::get_right(a), detail::get_left(b), detail::get_right(b))
            && detail::does_collide_on_axis(detail::get_bottom(a), detail::get_top(a), detail::get_bottom(b), detail::get_top(b));
    }

    template<typename Box, typename Vector>
    constexpr bool would_collide(
        Box const & start,
        Vector const & delta_position,
        Box const & obstacle
    )
    {
        if(does_collide(start, obstacle))
            return true;

        auto const outer_box = detail::get_outer_box(start, delta_position);
        if(!does_collide(obstacle, outer_box))
            return false;

        return delta_position.x() == 0 || delta_position.y() == 0 || detail::is_in_limited_area(start, delta_position, obstacle);
    }

    enum EdgeType
    {
        NONE = 0,
        HORIZONTAL = 1,
        VERTICAL = 2,
        BOTH = HORIZONTAL | VERTICAL
    };

    template<typename Box, typename Vector>
    constexpr EdgeType get_colliding_edges(
        Box const & start,
        Vector const & delta_position,
        Box const & obstacle
    )
    {
        assert(!does_collide(start, obstacle));

        if(!would_collide(start, delta_position, obstacle))
            return EdgeType::NONE;

        if(delta_position.x() == 0)
            return EdgeType::HORIZONTAL;
        if(delta_position.y() == 0)
            return EdgeType::VERTICAL;

        auto const start_point = detail::get_start_point_for_colliding_edges(start, delta_position);
        auto const target_point = detail::get_obstacle_point_for_colliding_edges(obstacle, delta_position);

        if(delta_position.x() > 0)
        {
            if(target_point.x() < start_point.x())
                return EdgeType::HORIZONTAL;
        }
        else
        {
            if(target_point.x() > start_point.x())
                return EdgeType::HORIZONTAL;
        }

        auto const position = detail::get_position_target_to_delta(start_point, delta_position, target_point);
        auto const upwards = delta_position.y() > 0;
        if(position == detail::Position::BELOW)
            return upwards ? EdgeType::VERTICAL : EdgeType::HORIZONTAL;
        if(position == detail::Position::ABOVE)
            return upwards ? EdgeType::HORIZONTAL : EdgeType::VERTICAL;
        return EdgeType::BOTH;
    }
}

#endif // AABB_AABB_HXX_INC

