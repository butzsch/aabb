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

add_executable(aabb_collision_type_detection_test_command
	main.cxx
	collision_type_detection.cxx
)

target_include_directories(aabb_collision_type_detection_test_command PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(aabb_collision_type_detection_test_command gmock gtest)

add_test(NAME aabb_collision_type_detection_test COMMAND aabb_collision_type_detection_test_command)

foreach(test_target aabb_move_collision aabb_move_collision aabb_collision_type_detection)
    set(target_command "${test_target}_test_command")
    if(MSVC)
        target_compile_options(${target_command} PRIVATE "/W4")
    else()
        target_compile_options(${target_command} PRIVATE "-Wall")
        target_compile_options(${target_command} PRIVATE "-Wextra")
    endif()
endforeach(test_target)

