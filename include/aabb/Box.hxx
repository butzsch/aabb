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
}

#endif // AABB_BOX_HXX_INC
