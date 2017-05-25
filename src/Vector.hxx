#ifndef AABB_VECTOR_HXX_INC
#define AABB_VECTOR_HXX_INC

namespace aabb
{
    struct Vector
    {
        double x;
        double y;
    };

    constexpr Vector & operator += (Vector & a, Vector const & b)
    {
        a.x += b.x;
        a.y += b.y;

        return a;
    }

    constexpr Vector operator + (Vector const & a, Vector const & b)
    {
        auto summand = a;
        return summand += b;
    }

    constexpr Vector & operator -= (Vector & a, Vector const & b)
    {
        a.x -= b.x;
        a.y -= b.y;

        return a;
    }

    constexpr Vector operator - (Vector const & a, Vector const & b)
    {
        auto minuend = a;
        return minuend -= b;
    }

    constexpr Vector operator /= (Vector & a, double b)
    {
        a.x /= b;
        a.y /= b;

        return a;
    }

    constexpr Vector operator / (Vector const & a, double b)
    {
        auto dividend = a;
        return dividend /= b;
    }
}

#endif // AABB_VECTOR_HXX_INC
