add_executable(aabb_test_command
    main.cxx
    collision.cxx
)

target_include_directories(aabb_test_command PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(aabb_test_command gmock gtest)

add_test(NAME aabb_test COMMAND aabb_test_command)

