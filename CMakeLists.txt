cmake_minimum_required(VERSION 3.14)
project(university-db)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCES
)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -std=c++20)

enable_testing()
add_executable(
    ${PROJECT_NAME}-ut
    ${SOURCES}
    src/tests.cpp
)
target_include_directories(${PROJECT_NAME}-ut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(
    ${PROJECT_NAME}-ut
    GTest::gtest_main
)
target_compile_options(${PROJECT_NAME}-ut PRIVATE -Werror -std=c++20)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
