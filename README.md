# aabb

[![Build Status](https://travis-ci.org/butzsch/aabb.svg?branch=master)](https://travis-ci.org/butzsch/aabb)
[![Build status](https://ci.appveyor.com/api/projects/status/ghavo0qdlefr0vx3?svg=true)](https://ci.appveyor.com/project/butzsch/aabb)

## Collision detection for axis-aligned rectangles

This header-only library provides three simple functions for 2D collision detection:

```c++
#include <aabb/aabb.hxx>

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
**get_colliding** can be used to tell with which edges start and obstacle will collide first during start's movement by delta_position.

Note that get_colliding_edges asserts that `!does_collide(start, obstacle)`.

---

Any class that provides a member function `T x()` and a member function `T y()` can be used as a Vector. Similarly, any class with member functions `Vector position()` and `Vector size()` can be used as a Box.
