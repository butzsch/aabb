add_executable(aabb_test_command_double
    main.cxx
    collision_double.cxx
    move_collision_double.cxx
)

target_include_directories(aabb_test_command_double PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(aabb_test_command_double gmock gtest)

add_test(NAME aabb_test_double COMMAND aabb_test_command_double)

