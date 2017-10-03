#ifndef AABB_AABB_TESTING_HXX_INC
#define AABB_AABB_TESTING_HXX_INC

#include <utility>

#include <gtest/gtest.h>

#include <aabb/aabb.hxx>

namespace aabb_testing
{
    using types_to_test = testing::Types<int, double>;

    template<typename T>
    struct Vector
    {
        T x;
        T y;
    };

    template<typename T>
    struct Box
    {
        Vector<T> position;
        Vector<T> size;
    };

    template<typename T>
    constexpr bool operator == (Vector<T> const & a, Vector<T> const & b)
    {
        return a.x == b.x
            && a.y == b.y;
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
    constexpr Vector<T> & operator *= (Vector<T> & a, T const b)
    {
        a.x *= b;
        a.y *= b;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator * (Vector<T> a, T const b)
    {
        return a *= b;
    }

    template<typename T>
    constexpr Vector<T> & operator /= (Vector<T> & a, T const b)
    {
        a.x /= b;
        a.y /= b;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator / (Vector<T> a, T const b)
    {
        return a /= b;
    }
}

namespace aabb
{
    template<typename T>
    struct VectorAdapter<aabb_testing::Vector<T>>
    {
        static constexpr aabb_testing::Vector<T> create(T const x, T const y)
        {
            return {x, y};
        }

        static constexpr T get_x(aabb_testing::Vector<T> const & vector)
        {
            return vector.x;
        }

        static constexpr T get_y(aabb_testing::Vector<T> const & vector)
        {
            return vector.y;
        }

        static constexpr aabb_testing::Vector<T> add(aabb_testing::Vector<T> const & a, aabb_testing::Vector<T> const & b)
        {
            return {a.x + b.x, a.y + b.y};
        }

        static constexpr aabb_testing::Vector<T> subtract(aabb_testing::Vector<T> const & a, aabb_testing::Vector<T> const & b)
        {
            return {a.x - b.x, a.y - b.y};
        }
    };

    template<typename T>
    struct BoxAdapter<aabb_testing::Box<T>>
    {
        using vector_t = aabb_testing::Vector<T>;

        static constexpr aabb_testing::Box<T> create(vector_t && position, vector_t && size)
        {
            return {std::forward<vector_t>(position), std::forward<vector_t>(size)};
        }

        static constexpr vector_t get_position(aabb_testing::Box<T> const & box)
        {
            return box.position;
        }

        static constexpr void set_position(aabb_testing::Box<T> & box, vector_t const & position)
        {
            box.position = position;
        }

        static constexpr vector_t get_size(aabb_testing::Box<T> const & box)
        {
            return box.size;
        }

        static constexpr void set_size(aabb_testing::Box<T> & box, vector_t const & size)
        {
            box.size = size;
        }
    };
}

#endif // AABB_AABB_TESTING_HXX_INC
