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
    constexpr Vector<T> get_upper_left(Box<T> const & box)
    {
        return {
            box.position.x,
            box.position.y + box.size.y,
        };
    }

    template<typename T>
    constexpr Vector<T> get_upper_right(Box<T> const & box)
    {
        return {
            box.position.x + box.size.x,
            box.position.y + box.size.y,
        };
    }

    template<typename T>
    constexpr Vector<T> get_lower_left(Box<T> const & box)
    {
        return {
            box.position.x,
            box.position.y,
        };
    }

    template<typename T>
    constexpr Vector<T> get_lower_right(Box<T> const & box)
    {
        return {
            box.position.x + box.size.x,
            box.position.y,
        };
    }
}

#endif // AABB_BOX_HXX_INC
