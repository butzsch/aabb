# aabb

[![Build Status](https://travis-ci.org/butzsch/aabb.svg?branch=master)](https://travis-ci.org/butzsch/aabb)
[![Build status](https://ci.appveyor.com/api/projects/status/ghavo0qdlefr0vx3?svg=true)](https://ci.appveyor.com/project/butzsch/aabb)

## Collision detection for axis-aligned rectangles

This library is header-only. To use it simply `#include <aabb/aabb.hxx>`.

aabb provides three simple functions for 2D collision detection:

```c++
template<typename Box>
constexpr bool does_collide(
    Box const & a,
    Box const & b
)
```
**does_collide** is the simplest of the provided functions, it merely checks for intersection in the bounds of the two given boxes.

---

```c++
template<typename Box, typename Vector>
constexpr bool would_collide(
    Box const & start,
    Vector const & delta_position,
    Box const & obstacle
)
```
**would_collide** checks if the boundaries of start will collide with obstacle at any point during start's movement by delta_position.

---

```c++
enum EdgeType
{
    NONE = 0,
    HORIZONTAL = 1,
    VERTICAL = 2,
    BOTH = HORIZONTAL | VERTICAL
};

template<typename Box, typename Vector>
constexpr EdgeType get_colliding_edges(
    Box const & start,
    Vector const & delta_position,
    Box const & obstacle
)
```
**get_colliding_edges** can be used to tell with which edges start and obstacle will collide first during start's movement by delta_position.

Note that get_colliding_edges asserts that `!does_collide(start, obstacle)`.

---

This library uses the concept of vectors and boxes in its interface. A vector descripes a point or directed size in a two-dimensional coordinate system. A box is a 2D rectangular area represented by a position vector and a size vector.
To use this library with your own vector and box types simply specialize `template<typename Vector> struct VectorAdapter` and `template<typename Box> struct BoxAdapter` in the namespace `aabb`. The following code example shows which functions and typedefs your specialized template structs have to provide:

```c++
    #include <aabb/adapter.hxx>

    struct Vector
    {
        int x;
        int y;
    };

    struct Box
    {
        Vector position;
        Vector size;
    };
    
    namespace aabb
    {
        template<>
        struct VectorAdapter<Vector>
        {
            static Vector create(int const x, int const y)
            {
                return Vector {x, y};
            }

            static int get_x(Vector const & vector)
            {
                return vector.x;
            }

            static int get_y(Vector const & vector)
            {
                return vector.y;
            }

            static Vector add(Vector const & a, Vector const & b)
            {
                return Vector {a.x + b.x, a.y + b.y};
            }

            static Vector subtract(Vector const & a, Vector const & b)
            {
                return Vector {a.x - b.x, a.y - b.y};
            }
        };

        template<>
        struct BoxAdapter<Box>
        {
            using vector_t = Vector;

            static Box create(Vector const & position, Vector const & size)
            {
                return Box {position, size};
            }

            static Vector get_position(Box const & box)
            {
                return box.position;
            }

            static Vector get_size(Box const & box)
            {
                return box.size;
            }
        };
    }
```
