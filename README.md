# Logger
In this repository singleton logger is represented. There are several modes: TRACE, INFO, DEBUG, WARNING, ERRORS. 
They are sequentially nested within each other: TRACE > INFO > DEBUG > WARNING > ERRORS. 
This means that if you set INFO mode during first usage of 'Logger::get()' command, all messages will not be displayed or written into text file if you use TRACE mode in log command.
# How to use
## Example №1
```c++
#include <logger.h>

int main(int argc, char* argv) {
    Logger::get(TRACE, std::make_unique<file_stream>("logger.txt"));
    Logger::get().log(TRACE)   << "I will be written in file logger.txt" << std::endl;
    Logger::get().log(INFO)    << "I will be written in file logger.txt" << std::endl;
    Logger::get().log(DEBUG)   << "I will be written in file logger.txt" << std::endl;
    Logger::get().log(WARNING) << "I will be written in file logger.txt" << std::endl;
    Logger::get().log(ERRORS)  << "I will be written in file logger.txt" << std::endl;
}
```
Every line will be written in file "logger.txt".
## Example №2
```c++
#include <logger.h>

int main(int argc, char* argv) {
    Logger::get(DEBUG, std::make_unique<cout_stream>());
    Logger::get().log(TRACE)   << "I will not be displayed" << std::endl;
    Logger::get().log(INFO)    << "I will not be displayed" << std::endl;
    Logger::get().log(DEBUG)   << "I will be displayed" << std::endl;
    Logger::get().log(WARNING) << "I will be displayed" << std::endl;
    Logger::get().log(ERRORS)  << "I will be displayed" << std::endl;
}
```
Every line will be displayed.
