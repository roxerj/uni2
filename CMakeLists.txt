cmake_minimum_required(VERSION 3.14)
project(testavimas)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the additional source files here
set(SOURCES
  unitTests.cc
  funkcijos.cpp
  # Add more files as needed
)

add_executable(
  hello_test
  ${SOURCES}
)
target_link_libraries(
  hello_test    
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)