#ifndef AABB_BOX_HXX_INC
#define AABB_BOX_HXX_INC

#include <cassert>
#include <cmath>

#include "Vector.hxx"

namespace aabb
{
    template<typename T>
    struct Box
    {
        Vector<T> position;
        Vector<T> size;
    };

    template<typename T>
    constexpr Box<T> box_from_edges(T left, T bottom, T right, T top)
    {
        assert(left < right);
        assert(bottom < top);

        return Box<T> {
            Vector<T> {left, bottom},
            Vector<T> {right - left, top - bottom}
        };
    }

    template<typename T>
    constexpr T get_left(Box<T> const & box)
    {
        return box.position.x + std::min(box.size.y, static_cast<T>(0));
    }

    template<typename T>
    constexpr T get_right(Box<T> const & box)
    {
        return box.position.x + std::max(box.size.x, static_cast<T>(0));
    }

    template<typename T>
    constexpr T get_bottom(Box<T> const & box)
    {
        return box.position.y + std::min(box.size.y, static_cast<T>(0));
    }

    template<typename T>
    constexpr T get_top(Box<T> const & box)
    {
        return box.position.y + std::max(box.size.y, static_cast<T>(0));
    }

    template<typename T>
    constexpr Vector<T> get_top_left(Box<T> const & box)
    {
        return {get_left(box), get_top(box)};
    }

    template<typename T>
    constexpr Vector<T> get_top_right(Box<T> const & box)
    {
        return {get_right(box), get_top(box)};
    }

    template<typename T>
    constexpr Vector<T> get_bottom_left(Box<T> const & box)
    {
        return {get_left(box), get_bottom(box)};
    }

    template<typename T>
    constexpr Vector<T> get_bottom_right(Box<T> const & box)
    {
        return {get_right(box), get_bottom(box)};
    }

    template<typename T>
    constexpr Box<T> plus_position(Box<T> box, Vector<T> const & delta_position)
    {
        box.position += delta_position;

        return box;
    }

    template<typename T>
    constexpr Box<T> minus_position(Box<T> box, Vector<T> const & delta_position)
    {
        box.position -= delta_position;

        return box;
    }

    template<typename T>
    constexpr Box<T> plus_size(Box<T> box, Vector<T> const & delta_size)
    {
        box.size += delta_size;

        return box;
    }

    template<typename T>
    constexpr Box<T> minus_size(Box<T> box, Vector<T> const & delta_size)
    {
        box.size -= delta_size;

        return box;
    }
}

#endif // AABB_BOX_HXX_INC
