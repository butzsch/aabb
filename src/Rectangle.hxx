#ifndef AABB_RECTANGLE_HXX_INC
#define AABB_RECTANGLE_HXX_INC

#include "Vector.hxx"

namespace aabb
{
    struct Rectangle
    {
        Vector position;
        Vector size;
    };
}

#endif // AABB_RECTANGLE_HXX_INC
