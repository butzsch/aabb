add_executable(collision_test_command main.cxx)

target_link_libraries(collision_test_command gmock gtest)

add_test(NAME collision_test COMMAND collision_test_command)

