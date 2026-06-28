cmake_minimum_required(VERSION 3.16)

project(basic_usage_tests)

add_library(logger_basic_usage_lib STATIC 
    basic_usage.cpp
)
target_include_directories(logger_basic_usage_lib PUBLIC ".")

target_link_libraries(logger_basic_usage_lib
    PRIVATE
    logger_lib
)