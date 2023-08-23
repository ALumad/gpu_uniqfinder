
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
    
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
    
enable_testing()
    
add_executable(
    ${TEST_NAME}
    gpu_tests.cpp
)
target_link_libraries(
    ${TEST_NAME}
    GTest::gtest_main
    ${LIB_NAME}
)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
