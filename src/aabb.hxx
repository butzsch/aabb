#ifndef AABB_AABB_HXX_INC
#define AABB_AABB_HXX_INC

#include <algorithm>
#include <cassert>

#include "Rectangle.hxx"
#include "Vector.hxx"

namespace
{
	template<typename T>
	constexpr T abs(T x)
	{
		return x < 0 ? -x : x;
	}

	template<typename T>
    constexpr bool collide_on_axis(T a_pos, T a_size, T b_pos, T b_size)
    {
        return a_pos < b_pos + b_size && b_pos < a_pos + a_size;
    }

	template<typename T>
    constexpr void assert_positive_size(aabb::Rectangle<T> const & x)
    {
        assert(x.size.x > 0);
        assert(x.size.y > 0);
    }

	template<typename T>
    constexpr aabb::Rectangle<T> get_outer_box(aabb::Rectangle<T> const & start, aabb::Vector<T> const & delta_position)
    {
        assert_positive_size(start);

        auto const outer_position = aabb::Vector<T> {
            start.position.x + std::min(delta_position.x, static_cast<T>(0)),
            start.position.y + std::min(delta_position.y, static_cast<T>(0))
        };

        return {
            outer_position,
            aabb::Vector<T> {
                start.size.x + abs(delta_position.x),
                start.size.y + abs(delta_position.y)
            }
        };
    }

	template<typename T>
    constexpr double get_short_delta_x(aabb::Rectangle<T> const & start, aabb::Rectangle<T> const & obstacle)
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        return obstacle.position.x - start.position.x - start.size.x;
    }

	template<typename T>
    constexpr double get_long_delta_x(aabb::Rectangle<T> const & start, aabb::Rectangle<T> const & obstacle)
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        return obstacle.position.x + obstacle.size.x - start.position.x;
    }

	template<typename T>
    constexpr bool is_above_low_diagonal(
        aabb::Rectangle<T> const & start,
        aabb::Rectangle<T> const & obstacle,
        double slope
    )
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        auto const delta_x = slope > 0 ? get_short_delta_x(start, obstacle) : get_long_delta_x(start, obstacle);
        auto const delta_y = slope * delta_x;
        return obstacle.position.y + obstacle.size.y > start.position.y + delta_y;
    }

	template<typename T>
    constexpr bool is_below_high_diagonal(
        aabb::Rectangle<T> const & start,
        aabb::Rectangle<T> const & obstacle,
        double slope
    )
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        auto const delta_x = slope > 0 ? get_long_delta_x(start, obstacle) : get_short_delta_x(start, obstacle);
        auto const delta_y = slope * delta_x;
        return obstacle.position.y < start.position.y + start.size.y + delta_y;
    }

	template<typename T>
    constexpr bool collide_diagonally(
        aabb::Rectangle<T> const & start,
        aabb::Vector<T> const & delta_position,
        aabb::Rectangle<T> const & obstacle
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
    constexpr bool collide(Rectangle<T> const & a, Rectangle<T> const & b)
    {
        assert_positive_size(a);
        assert_positive_size(b);

        return collide_on_axis(a.position.x, a.size.x, b.position.x, b.size.x)
            && collide_on_axis(a.position.y, a.size.y, b.position.y, b.size.y);
    }

	template<typename T>
    constexpr bool move_collide(
        Rectangle<T> const & start,
        Vector<T> const & delta_position,
        Rectangle<T> const & obstacle
    )
    {
        assert_positive_size(start);
        assert_positive_size(obstacle);

        auto const outer_box = get_outer_box(start, delta_position);
        return collide(obstacle, outer_box)
            && (delta_position.x == 0 || collide_diagonally(start, delta_position, obstacle));
    }
}

#endif // AABB_AABB_HXX_INC

