#include "logger.h"

int main(int argc, char* argv) {

    Logger::get(DEBUG, std::make_unique<file_stream>("logger.txt"));
    Logger::get().log(TRACE) << "I'am here" << std::endl;
    Logger::get().log(INFO) << "I'am here" << std::endl;
    Logger::get().log(DEBUG) << "I'am here" << std::endl;
    Logger::get().log(WARNING) << "I'am here" << std::endl;
    Logger::get().log(ERRORS) << "I'am here" << std::endl;

    return 0;
}