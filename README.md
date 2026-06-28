# Logger
In this repository singleton logger is represented. There are several modes: DEBUG, WARNING, INFO, ERROR. 
They are sequentially nested within each other: DEBUG > WARNING > INFO > ERROR. 
It means first setting INFO mode by usage of 'Logger::get()' will ignore all written with DEBUG or WARNING modes messages.
# Simple usage examples
## Example №1
```c++
#include <logger.h>

int main(int argc, char* argv) {
    auto& log = Logger::get(MODE::DEBUG, false, std::make_unique<file_stream>("debug_log.txt"));
    log(MODE::INFO)    << "I will be written in file debug_log.txt" << std::endl;
    log(MODE::DEBUG)   << "I will be written in file debug_log.txt" << std::endl;
    log(MODE::WARNING) << "I will be written in file debug_log.txt" << std::endl;
    log(MODE::ERRORS)  << "I will be written in file debug_log.txt" << std::endl;
}
```
Every line will be written in file "debug_log.txt".
## Example №2
```c++
#include <logger.h>

int main(int argc, char* argv) {
    auto& log = Logger::get(MODE::WARNING, false, std::make_unique<cout_stream>());
    log(MODE::DEBUG)   << "I will not be displayed\n";
    log(MODE::WARNING) << "I will be displayed\n";
    log(MODE::INFO)    << "I will be displayed\n";
    log(MODE::ERROR)   << "I will be displayed\n";
}
```
Last three lines will be displayed. Output : 
```c++
>>  WARNING: I will be displayed
>>  INFO: I will be displayed
>>  ERROR: I will be displayed
```
# Special parameters
By default all modes are colored : DEBUG - YELLOW, WARNING - PURPLE, INFO - BLUE, ERROR - RED.
This feature is used for all streams besides file_stream.
To log messages with time in format "day::hours::minutes" just switch second parameter of Logger::get() to true. 

## Example №3
```c++
#include <logger.h>

int main(int argc, char* argv) {
    auto& log = Logger::get(MODE::INFO, true, std::make_unique<cout_stream>());
    log(MODE::INFO)    << "Calculation is started\n";
    // Some computations and routine
    log(MODE::INFO)    << "Calculation is finished\n";
}
```

Output with random time: 
```c++
2026-01-03 15:04:51  >>  INFO: Calculation is started
2026-01-03 16:46:32  >>  INFO: Calculation is finished
```
