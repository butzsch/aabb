cmake_minimum_required(VERSION 3.6.0)
project(aabb)

option(AABB_BUILD_TESTS "Build the tests for the aabb library as well as the gtest/gmock dependency" FALSE)

if(AABB_BUILD_TESTS)
    enable_testing()
    
    add_subdirectory(dependencies)
    add_subdirectory(tests)
endif(AABB_BUILD_TESTS)
