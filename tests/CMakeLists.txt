add_executable(aabb_collision_test_command
    main.cxx
    collision.cxx
)

target_include_directories(aabb_collision_test_command PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(aabb_collision_test_command gmock gtest)

add_test(NAME aabb_collision_test COMMAND aabb_collision_test_command)

add_executable(aabb_move_collision_test_command
    main.cxx
    move_collision.cxx
)

target_include_directories(aabb_move_collision_test_command PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(aabb_move_collision_test_command gmock gtest)

add_test(NAME aabb_move_collision_test COMMAND aabb_move_collision_test_command)
