cmake_minimum_required(VERSION 3.20)

project(pigskinjelly)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build_support/cmake" ${CMAKE_MODULE_PATH})
include(CTest)
include(findLLVMTools)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
if(NOT DEFINED WITH_IN_SOURCE_BUILD)
message(FATAL_ERROR
"CMake generation for pigskinjelly is not allowed within the source directory!"
"\n Remove \"${CMAKE_SOURCE_DIR}/CMakeCache.txt\" and try again from another folder, e.g.:"
"\n "
"\n rm -rf CMakeCache.txt CMakeFiles"
"\n cd .."
"\n mkdir cmake-make"
"\n cd cmake-make"
"\n cmake ../pigskinjelly"
"\n "
"\n Alternately define WITH_IN_SOURCE_BUILD to force this option (not recommended!)"
)
endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(TEST_SOURCES_PATTERN "${PROJECT_SOURCE_DIR}/src/*/*test.cc")

add_subdirectory(third_party)
include(LCOV)
add_subdirectory(src)
enable_testing()
