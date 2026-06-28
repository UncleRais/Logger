#include <basic_usage.hpp>

#include <iostream>

int main() {
    logger_tests::logger_time_test();
    logger_tests::logger_cout_test();
    std::cout << "Successfully passed tests : " << passed_tests << std::endl;
    std::cout << "Failed tests : " << failed_tests << std::endl;
    return 0;
}