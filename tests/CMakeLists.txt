add_executable(aabb_test
	collision.cxx
	move_collision.cxx
	collision_type_detection.cxx
)

set_target_properties(aabb_test PROPERTIES CXX_STANDARD 14)

if(MSVC)
    target_compile_options(aabb_test PRIVATE /W4)
else()
    target_compile_options(aabb_test PRIVATE -Wall)
    target_compile_options(aabb_test PRIVATE -Wextra)
endif()

target_include_directories(aabb_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(aabb_test gmock_main gtest)

add_test(NAME aabb_test COMMAND aabb_test)

