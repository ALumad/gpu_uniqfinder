project(gpu_uniqfinder)
cmake_minimum_required(VERSION 3.14)
add_compile_definitions(_DEVICE_TYPE_=CL_DEVICE_TYPE_CPU)
set(CMAKE_CXX_STANDARD 17)

set(LIB_NAME libgpu)
set(TEST_NAME test_libgpu)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/uniqfind.cl
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
