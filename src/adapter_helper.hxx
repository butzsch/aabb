#ifndef AABB_ADAPTERHELPER_HXX_INC
#define AABB_ADAPTERHELPER_HXX_INC

#include <type_traits>
#include <utility>

#include "../include/aabb/adapter.hxx"

namespace aabb
{
    namespace detail
    {
        template<typename T>
        using lookup_t = std::decay_t<T>;

        template<typename Box>
        using vector_t = typename BoxAdapter<lookup_t<Box>>::vector_t;

        template<typename Box>
        constexpr auto get_position(Box && box)
        {
            return BoxAdapter<lookup_t<Box>>::get_position(std::forward<Box>(box));
        }

        template<typename Box>
        constexpr auto get_size(Box && box)
        {
            return BoxAdapter<lookup_t<Box>>::get_size(std::forward<Box>(box));
        }

        template<typename Vector>
        constexpr auto get_x(Vector && vector)
        {
            return VectorAdapter<lookup_t<Vector>>::get_x(std::forward<Vector>(vector));
        }

        template<typename Vector>
        constexpr auto get_y(Vector && vector)
        {
            return VectorAdapter<lookup_t<Vector>>::get_y(std::forward<Vector>(vector));
        }

        template<typename Vector, typename T>
        constexpr auto create_vector(T && x, T && y)
        {
            return VectorAdapter<lookup_t<Vector>>::create(std::forward<T>(x), std::forward<T>(y));
        }

        template<typename Box, typename Vector>
        constexpr auto create_box(Vector && position, Vector && size)
        {
            return BoxAdapter<lookup_t<Box>>::create(std::forward<Vector>(position), std::forward<Vector>(size));
        }

        template<typename Vector, typename V1, typename V2>
        constexpr auto add_vectors(V1 && a, V2 && b)
        {
            return VectorAdapter<lookup_t<Vector>>::add(std::forward<V1>(a), std::forward<V2>(b));
        }

        template<typename Vector, typename V1, typename V2>
        constexpr auto subtract_vectors(V1 && a, V2 && b)
        {
            return VectorAdapter<lookup_t<Vector>>::subtract(std::forward<V1>(a), std::forward<V2>(b));
        }
    }
}

#endif // AABB_ADAPTERHELPER_HXX_INC
