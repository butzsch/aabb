#ifndef AABB_BOX_HXX_INC
#define AABB_BOX_HXX_INC

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
    constexpr T get_left(Box<T> const & box)
    {
        return box.position.x;
    }

    template<typename T>
    constexpr T get_right(Box<T> const & box)
    {
        return box.position.x + box.size.x;
    }

    template<typename T>
    constexpr T get_bottom(Box<T> const & box)
    {
        return box.position.y;
    }

    template<typename T>
    constexpr T get_top(Box<T> const & box)
    {
        return box.position.y + box.size.y;
    }

    template<typename T>
    constexpr Vector<T> get_top_left(Box<T> const & box)
    {
        return {
            box.position.x,
            box.position.y + box.size.y,
        };
    }

    template<typename T>
    constexpr Vector<T> get_top_right(Box<T> const & box)
    {
        return {
            box.position.x + box.size.x,
            box.position.y + box.size.y,
        };
    }

    template<typename T>
    constexpr Vector<T> get_bottom_left(Box<T> const & box)
    {
        return {
            box.position.x,
            box.position.y,
        };
    }

    template<typename T>
    constexpr Vector<T> get_bottom_right(Box<T> const & box)
    {
        return {
            box.position.x + box.size.x,
            box.position.y,
        };
    }
}

#endif // AABB_BOX_HXX_INC
