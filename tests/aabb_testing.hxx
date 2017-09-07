#ifndef AABB_AABB_TESTING_HXX_INC
#define AABB_AABB_TESTING_HXX_INC

#include <gtest/gtest.h>

namespace aabb_testing
{
    using types_to_test = testing::Types<int, double>;

    template<typename T>
    struct Vector
    {
        T x = 0;
        T y = 0;
    };

    template<typename T>
    constexpr bool operator == (Vector<T> const & a, Vector<T> const & b)
    {
        return a.x == b.x && a.y == b.y;
    }

    template<typename T>
    constexpr bool operator != (Vector<T> const & a, Vector<T> const & b)
    {
        return !(a == b);
    }

    template<typename T>
    constexpr Vector<T> & operator += (Vector<T> & a, Vector<T> const & b)
    {
        a.x += b.x;
        a.y += b.y;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator + (Vector<T> a, Vector<T> const & b)
    {
        return a += b;
    }

    template<typename T>
    constexpr Vector<T> & operator -= (Vector<T> & a, Vector<T> const & b)
    {
        a.x -= b.x;
        a.y -= b.y;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator - (Vector<T> a, Vector<T> const & b)
    {
        return a -= b;
    }

    template<typename T>
    constexpr Vector<T> & operator *= (Vector<T> & a, T b)
    {
        a.x *= b;
        a.y *= b;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator * (Vector<T> a, T b)
    {
        return a *= b;
    }

    template<typename T>
    constexpr Vector<T> operator /= (Vector<T> & a, T b)
    {
        a.x /= b;
        a.y /= b;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator / (Vector<T> a, T b)
    {
        return a /= b;
    }
    
    template<typename T>
    struct Box
    {
        Vector<T> position;
        Vector<T> size;
    };
}

#endif // AABB_AABB_TESTING_HXX_INC
