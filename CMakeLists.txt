cmake_minimum_required(VERSION 3.10)
project(TapeSorter)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(TapeSorter main.cpp src/ExternalSort.cpp src/Tape.cpp src/Config.cpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TestExternalSort tests/testExternalSort.cpp src/ExternalSort.cpp src/Tape.cpp src/Config.cpp)
add_executable(TestTape tests/testTape.cpp src/Tape.cpp src/Config.cpp)

target_link_libraries(TestExternalSort gtest gtest_main)
target_link_libraries(TestTape gtest gtest_main)

enable_testing()
add_test(NAME TestExternalSort COMMAND TestExternalSort)
add_test(NAME TestTape COMMAND TestTape)