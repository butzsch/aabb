#ifndef AABB_BOXHELPER_HXX_INC
#define AABB_BOXHELPER_HXX_INC

#include <type_traits>

#include "adapter_helper.hxx"

namespace aabb
{
    namespace detail
    {
        template<typename Box>
        constexpr auto get_position_x(Box const & box)
        {
            auto const position = get_position(box);
            return get_x(position);
        }

        template<typename Box>
        constexpr auto get_position_y(Box const & box)
        {
            auto const position = get_position(box);
            return get_y(position);
        }

        template<typename Box>
        constexpr auto get_size_x(Box const & box)
        {
            auto const size = get_size(box);
            return get_x(size);
        }

        template<typename Box>
        constexpr auto get_size_y(Box const & box)
        {
            auto const size = get_size(box);
            return get_y(size);
        }

        template<typename Box>
        constexpr auto get_left(Box const & box)
        {
            auto const size_x = get_size_x(box);
            auto const position_x = get_position_x(box);

            if (size_x < 0)
                return position_x + size_x;

            return position_x;
        }

        template<typename Box>
        constexpr auto get_right(Box const & box)
        {
            auto const size_x = get_size_x(box);
            auto const position_x = get_position_x(box);

            if (size_x > 0)
                return position_x + size_x;

            return position_x;
        }

        template<typename Box>
        constexpr auto get_bottom(Box const & box)
        {
            auto const size_y = get_size_y(box);
            auto const position_y = get_position_y(box);

            if (size_y < 0)
                return position_y + size_y;

            return position_y;
        }

        template<typename Box>
        constexpr auto get_top(Box const & box)
        {
            auto const size_y = get_size_y(box);
            auto const position_y = get_position_y(box);

            if (size_y > 0)
                return position_y + size_y;

            return position_y;
        }

        template<typename Box>
        constexpr auto get_top_left(Box const & box)
        {
            return create_vector<BoxAdapter<Box>::vector_t>(
                get_left(box),
                get_top(box)
            );
        }

        template<typename Box>
        constexpr auto get_top_right(Box const & box)
        {
            return create_vector<BoxAdapter<Box>::vector_t>(
                get_right(box),
                get_top(box)
            );
        }

        template<typename Box>
        constexpr auto get_bottom_left(Box const & box)
        {
            return create_vector<BoxAdapter<Box>::vector_t>(
                get_left(box),
                get_bottom(box)
            );
        }

        template<typename Box>
        constexpr auto get_bottom_right(Box const & box)
        {
            return create_vector<BoxAdapter<Box>::vector_t>(
                get_right(box),
                get_bottom(box)
            );
        }

        template<typename Box, typename T>
        constexpr Box box_from_edges(T left, T bottom, T right, T top)
        {
            assert(left < right);
            assert(bottom < top);

            return create_box<Box>(
                create_vector<BoxAdapter<Box>::vector_t>(left, bottom),
                create_vector<BoxAdapter<Box>::vector_t>(right - left, top - bottom)
            );
        }

        template<typename Box, typename Vector>
        constexpr auto plus_position(Box box, Vector const & delta_position)
        {
            auto const current_position = get_position(box);
            set_position(box, add_vectors(current_position, delta_position));

            return box;
        }
    }
}

#endif // AABB_BOXHELPER_HXX_INC
