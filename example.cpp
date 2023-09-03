#include "logger.h"

int main(int argc, char* argv) {

    Logger& LOG = Logger::getInstance("logger.txt", TRACE, true);
    LOG.simple_test();
    return 0;
}