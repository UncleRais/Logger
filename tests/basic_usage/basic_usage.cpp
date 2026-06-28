#include "basic_usage.hpp"

#include <logger.hpp>

namespace logger_tests {

void logger_time_test() {
    using namespace logger;
    using namespace std::string_literals;
    auto& log = Logger::get(MODE::INFO, true, std::make_unique<cout_stream>());
    //log(MODE::INFO)    << "Calculation is started\n";
    // Some computations and routine
    //log(MODE::INFO)    << "Calculation is finished\n";
}

void logger_cout_test() {
    using namespace logger;
    using namespace std::string_literals;
    std::stringstream ss;
    auto& log = Logger::get(MODE::WARNING, false, std::make_unique<cout_stream>());
    auto old_buf = log.get_buffer();
    log.set_buffer(ss.rdbuf());
    log(MODE::DEBUG)   << "I will not be displayed\n";
    log(MODE::WARNING) << "I will be displayed\n";
    log(MODE::INFO)    << "I will be displayed\n";
    log(MODE::ERROR)   << "I will be displayed\n";
    log.set_buffer(old_buf);
    //const std::string debug_log    = "\033[37m >> \033[33m DEBUG: \033[37mI will not be displayed\n"s;
    const std::string warning_log  = "\033[37m >> \033[35m WARNING: \033[37mI will be displayed\n"s;
    const std::string info_log     = "\033[37m >> \033[34m INFO: \033[37mI will be displayed\n"s;
    const std::string error_log    = "\033[37m >> \033[31m ERROR: \033[37mI will be displayed\n"s;
    IS_TRUE(ss.str() == warning_log + info_log + error_log);
}

};