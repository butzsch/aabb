cmake_minimum_required(VERSION 3.8.0)
project(aabb)

option(BUILD_AABB_TESTS "Build the tests for the aabb library as well as the gtest/gmock dependency" FALSE)

if(BUILD_AABB_TESTS)
    set(CMAKE_CXX_STANDARD 14)
    
    enable_testing()
    
    add_subdirectory(dependencies)
    add_subdirectory(tests)
endif(BUILD_AABB_TESTS)

