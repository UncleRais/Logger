cmake_minimum_required(VERSION 3.16)

project(logger_tests)

add_subdirectory(basic_usage)

add_executable(unit_tests logger_tests.cpp)
target_include_directories(unit_tests PUBLIC ".")

target_link_libraries(unit_tests
    PUBLIC
    logger_basic_usage_lib
)