#ifndef AABB_BOXHELPER_HXX_INC
#define AABB_BOXHELPER_HXX_INC

namespace aabb
{
    namespace detail
    {
        template<typename Box>
        constexpr auto get_left(Box const & box)
        {
            auto const width = box.size().x();

            return box.position().x() + std::min(width, static_cast<decltype(width)>(0));
        }

        template<typename Box>
        constexpr auto get_right(Box const & box)
        {
            auto const width = box.size().x();

            return box.position().x() + std::max(width, static_cast<decltype(width)>(0));
        }

        template<typename Box>
        constexpr auto get_bottom(Box const & box)
        {
            auto const height = box.size().y();

            return box.position().y() + std::min(height, static_cast<decltype(height)>(0));
        }

        template<typename Box>
        constexpr auto get_top(Box const & box)
        {
            auto const height = box.size().y();

            return box.position().y() + std::max(height, static_cast<decltype(height)>(0));
        }

        template<typename Box>
        constexpr auto get_top_left(Box const & box) -> std::remove_reference_t<decltype(box.position())>
        {
            return {get_left(box), get_top(box)};
        }

        template<typename Box>
        constexpr auto get_top_right(Box const & box) -> std::remove_reference_t<decltype(box.position())>
        {
            return {get_right(box), get_top(box)};
        }

        template<typename Box>
        constexpr auto get_bottom_left(Box const & box) ->std::remove_reference_t<decltype(box.position())>
        {
            return {get_left(box), get_bottom(box)};
        }

        template<typename Box>
        constexpr auto get_bottom_right(Box const & box) -> std::remove_reference_t<decltype(box.position())>
        {
            return {get_right(box), get_bottom(box)};
        }

        template<typename Box, typename T>
        constexpr Box box_from_edges(T left, T bottom, T right, T top)
        {
            assert(left < right);
            assert(bottom < top);

            return {
                {left, bottom},
                {right - left, top - bottom}
            };
        }

        template<typename Box, typename Vector>
        constexpr auto plus_position(Box box, Vector const & delta_position)
        {
            box.position() += delta_position;

            return box;
        }
    }
}

#endif // AABB_BOXHELPER_HXX_INC
