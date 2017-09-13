#ifndef AABB_AABB_TESTING_HXX_INC
#define AABB_AABB_TESTING_HXX_INC

#include <gtest/gtest.h>

namespace aabb_testing
{
    using types_to_test = testing::Types<int, double>;

    template<typename T>
    struct Vector
    {
    public:
        constexpr Vector(T const x, T const y)
            : x_ {x}
            , y_ {y}
        {}

        constexpr auto & x()
        {
            return x_;
        }

        constexpr auto const & x() const
        {
            return x_;
        }

        constexpr auto & y()
        {
            return y_;
        }

        constexpr auto const & y() const
        {
            return y_;
        }

    private:
        T x_;
        T y_;
    };

    template<typename T>
    constexpr bool operator == (Vector<T> const & a, Vector<T> const & b)
    {
        return a.x() == b.x() && a.y() == b.y();
    }

    template<typename T>
    constexpr bool operator != (Vector<T> const & a, Vector<T> const & b)
    {
        return !(a == b);
    }

    template<typename T>
    constexpr Vector<T> & operator += (Vector<T> & a, Vector<T> const & b)
    {
        a.x() = a.x() + b.x();
        a.y() = a.y() + b.y();

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
        a.x() = a.x() - b.x();
        a.y() = a.y() - b.y();

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
        a.x() = a.x() * b;
        a.y() = a.y() * b;

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
        a.x() = a.x() / b;
        a.y() = a.y() / b;

        return a;
    }

    template<typename T>
    constexpr Vector<T> operator / (Vector<T> a, T const b)
    {
        return a /= b;
    }
    
    template<typename T>
    class Box
    {
    public:
        constexpr Box(Vector<T> const & position, Vector<T> const & size)
            : position_ {position}
            , size_ {size}
        {}

        constexpr Box(T const x, T const y, T const width, T const height)
            : position_ {x, y}
            , size_ {width, height}
        {}

        constexpr auto & position()
        {
            return position_;
        }

        constexpr auto const & position() const
        {
            return position_;
        }

        constexpr auto & size()
        {
            return size_;
        }

        constexpr auto const & size() const
        {
            return size_;
        }

    private:
        Vector<T> position_;
        Vector<T> size_;
    };
}

#endif // AABB_AABB_TESTING_HXX_INC
