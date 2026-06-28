#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>

#include <array>

namespace logger {

namespace {
const std::string barrier = " >> ";

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    // localtime_s for Windows and localtime_r for Linux/Mac
    #if defined(_WIN32)
        struct tm timeinfo;
        localtime_s(&timeinfo, &in_time_t);
        ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    #else
        struct tm timeinfo;
        localtime_r(&in_time_t, &timeinfo);
        ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    #endif
    return ss.str();
}

enum COLOR {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE,
	WHITE,

    n_colors
};

COLOR mode_color(const MODE& mode) {
    constexpr std::array<COLOR, size_t(MODE::n_modes)> mode_to_color{ YELLOW, PURPLE, BLUE, RED };
    return mode_to_color[mode];
};

std::string color_code(const COLOR& color) {
    using namespace std::string_literals;
    const std::array<std::string, size_t(COLOR::n_colors)> color_to_code
    { "\033[31m"s, "\033[34m"s, "\033[32m"s, "\033[33m"s, "\033[35m"s, "\033[37m"s };
    return color_to_code[color];
};

std::string mode_string(const MODE& mode) {
    using namespace std::string_literals;
    const std::array<std::string, size_t(MODE::n_modes)> mode_to_string
    { " DEBUG: "s, " WARNING: "s, " INFO: "s, " ERROR: "s };
    return mode_to_string[mode];
};

std::string paint_str(const std::string& str, const COLOR& color) {
	return (color_code(color) + str);
};

std::string general_line(const MODE& mode, bool time, bool colored) {
	std::string line = (time ? get_current_time() + " " : "") + barrier;
	if (colored) {
		line = paint_str(line, WHITE);
		line += paint_str(mode_string(mode), mode_color(mode));
	} else {
		line += mode_string(mode);
	}
	return line + paint_str("", WHITE);
};
};

Logger::Logger(MODE mode, bool time, std::unique_ptr<stream_base>&& out) 
    : _mode(mode), _time(time), _out(std::move(out)){
    _colored = !bool(dynamic_cast<file_stream*>(_out.get()));
    this->operator()(MODE::DEBUG) << "Logger is initialized." << std::endl;
};

Logger::~Logger() {
    this->operator()(MODE::DEBUG) << "Logger is destructred." << std::endl;
};

Logger& Logger::get(MODE mode, bool time, std::unique_ptr<stream_base>&& out) {
    static Logger log{ mode, time, out ? std::move(out) : std::make_unique<cout_stream>() };
    log._time = time;
    log._mode = mode;
    return log;
};

std::ostream& Logger::operator()(MODE mode) {
    if (_mode <= mode) {
            _out->_out << general_line(mode, _time, _colored);
        return _out->_out;
    }
    return empty;
};

std::streambuf* const Logger::get_buffer() const {
    return _out->_out.rdbuf();
}

void Logger::set_buffer(std::streambuf* const buffer) {
    _out->_out.rdbuf(buffer);
}


};


