# Logger
In this repository singleton logger is represented. There are several modes: TRACE, INFO, WARNING, ERRORS. They are sequentially nested within each other: TRACE > INFO > WARNING > ERRORS. This means that if you use INFO mode all messages from `LOG.trace()` commands will not be displayed and written into the text file.
# How to use
## Example №1
```c++
#include <logger.h>

int main(int argc, char* argv) {
Logger& LOG = Logger::getInstance("logger.txt", TRACE);
LOG.trace("I will be written in file logger.txt");
LOG.info("I will be written in file logger.txt");
LOG.warn("I will be written in file logger.txt");
LOG.error("I will be written in file logger.txt");
LOG.fatal("I will be written in file logger.txt");
}
```
Every line will be displayed and written in file "logger.txt".
## Example №2
```c++
#include <logger.h>

int main(int argc, char* argv) {
Logger& LOG = Logger::getInstance("logger.txt", WARNING, false);
LOG.trace("I will not be written in file logger.txt");
LOG.info("I will not be written in file logger.txt");
LOG.warn("I will be written in file logger.txt");
LOG.error("I will be written in file logger.txt");
LOG.fatal("I will be written in file logger.txt");
}
```
Nothing will be displayed and three lines will be written in file "logger.txt".
