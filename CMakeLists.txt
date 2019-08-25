cmake_minimum_required(VERSION 3.10)
project(cpp_itt)

set(CMAKE_CXX_STANDARD 17)

find_path(ITT_INCLUDE_DIR
        NAMES ittnotify.h
        HINTS "/opt/intel/vtune_amplifier/include/")
find_library(ITT_LIBRARY
        NAMES libittnotify.a
        HINTS "/opt/intel/vtune_amplifier/lib64/")

set(cpp_itt_FOUND yes)
set(cpp_itt_INCLUDES ${PROJECT_SOURCE_DIR}/include)
add_library(cpp_itt include/cpp_itt.h src/cpp_itt.cpp)
target_include_directories(cpp_itt PUBLIC include)

if(ITT_LIBRARY)
    target_compile_definitions(cpp_itt PUBLIC VTUNE_FOUND)
    target_include_directories(cpp_itt PUBLIC ${ITT_INCLUDE_DIR})
    target_link_libraries(cpp_itt ${ITT_LIBRARY})
endif()

find_package(Threads REQUIRED)
add_executable(cpp_itt_example examples/multi_thread_example.cpp)
target_link_libraries(cpp_itt_example cpp_itt ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})