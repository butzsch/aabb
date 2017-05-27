#ifndef AABB_RECTANGLE_HXX_INC
#define AABB_RECTANGLE_HXX_INC

#include "Vector.hxx"

namespace aabb
{
	template<typename T>
    struct Rectangle
    {
        Vector<T> position;
        Vector<T> size;
    };
}

#endif // AABB_RECTANGLE_HXX_INC
