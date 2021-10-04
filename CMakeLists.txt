#====================================================================================================
# This CMake Project defines the build for the GA1 AI Lookup Utility
#====================================================================================================

#====================================================================================================
# CMake Version and Policies
#
# Defines the minimum version of CMake for this project and lists the policies that we've commited
# to.
#====================================================================================================
cmake_minimum_required(VERSION 3.18)

project(dmrc_fixed_point)
include(CTest)

add_subdirectory(src)
add_subdirectory(tests)