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
}

#endif // AABB_BOX_HXX_INC
