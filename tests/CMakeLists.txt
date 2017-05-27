add_executable(aabb_test_command_double
    main.cxx
    collision_double.cxx
    move_collision_double.cxx
)

target_include_directories(aabb_test_command_double PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(aabb_test_command_double gmock gtest)

add_test(NAME aabb_test_double COMMAND aabb_test_command_double)

add_executable(aabb_test_command_int
    main.cxx
    collision_int.cxx
    move_collision_int.cxx
)

target_include_directories(aabb_test_command_int PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(aabb_test_command_int gmock gtest)

add_test(NAME aabb_test_int COMMAND aabb_test_command_int)

