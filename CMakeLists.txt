cmake_minimum_required(VERSION 3.14)
project(cpp_itt)

set(CMAKE_CXX_STANDARD 14)

find_path(ITT_INCLUDE_DIR
        NAMES ittnotify.h
        HINTS "/opt/intel/vtune_amplifier/include/")
find_library(ITT_LIBRARY
        NAMES libittnotify.a
        HINTS "/opt/intel/vtune_amplifier/lib64/")
message("PATH: ${ITT_LIBRARY}")
message("INCLUDES: ${ITT_INCLUDE_DIR}")
set(cpp_itt_FOUND yes)
set(cpp_itt_INCLUDES ${PROJECT_SOURCE_DIR}/include)
add_library(cpp_itt include/cpp_itt.h src/cpp_itt.cpp)
target_include_directories(cpp_itt PUBLIC include ${ITT_INCLUDE_DIR})
target_link_libraries(cpp_itt ${ITT_LIBRARY})
