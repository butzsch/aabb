#ifndef AABB_ADAPTERHELPER_HXX_INC
#define AABB_ADAPTERHELPER_HXX_INC

#include <type_traits>
#include <utility>

#include "../include/aabb/adapter.hxx"

namespace aabb
{
    namespace detail
    {
        template<typename Box>
        constexpr auto get_position(Box && box)
        {
            return BoxAdapter<std::decay_t<Box>>::get_position(std::forward<Box>(box));
        }

        template<typename Box, typename Vector>
        constexpr void set_position(Box & box, Vector && position)
        {
            BoxAdapter<std::decay_t<Box>>::set_position(box, std::forward<Vector>(position));
        }

        template<typename Box>
        constexpr auto get_size(Box && box)
        {
            return BoxAdapter<std::decay_t<Box>>::get_size(std::forward<Box>(box));
        }

        template<typename Box, typename Vector>
        constexpr void set_size(Box & box, Vector && size)
        {
            BoxAdapter<std::decay_t<Box>>::set_size(box, std::forward<Vector>(size));
        }

        template<typename Vector>
        constexpr auto get_x(Vector && vector)
        {
            return VectorAdapter<std::decay_t<Vector>>::get_x(std::forward<Vector>(vector));
        }

        template<typename Vector>
        constexpr auto get_y(Vector && vector)
        {
            return VectorAdapter<std::decay_t<Vector>>::get_y(std::forward<Vector>(vector));
        }

        template<typename Vector, typename T>
        constexpr auto create_vector(T && x, T && y)
        {
            return VectorAdapter<std::decay_t<Vector>>::create(std::forward<T>(x), std::forward<T>(y));
        }

        template<typename Box, typename Vector>
        constexpr auto create_box(Vector && position, Vector && size)
        {
            return BoxAdapter<std::decay_t<Box>>::create(std::forward<Vector>(position), std::forward<Vector>(size));
        }

        template<typename Vector>
        constexpr auto add_vectors(Vector && a, Vector && b)
        {
            return VectorAdapter<std::decay_t<Vector>>::add(std::forward<Vector>(a), std::forward<Vector>(b));
        }

        template<typename Vector>
        constexpr auto subtract_vectors(Vector && a, Vector && b)
        {
            return VectorAdapter<std::decay_t<Vector>>::subtract(std::forward<Vector>(a), std::forward<Vector>(b));
        }
    }
}

#endif // AABB_ADAPTERHELPER_HXX_INC
