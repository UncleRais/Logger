#include "logger.h"

Logger* Logger::p_instance_ = 0;
LoggerDestroyer Logger::destroyer_;

// Getters

Logger& Logger::getInstance(std::string filename, MODE mode, bool verbose) {
	
	if (!p_instance_) {
		p_instance_ = new Logger(filename, mode, verbose);
		destroyer_.initialize(p_instance_);
	}
	return *p_instance_;
}

std::string Logger::get_time() {
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof(str), &result);
	std::string new_str(str);
	new_str.pop_back();
	return(new_str);
};

// Logger types

void Logger::trace(std::string text) {
	if (mode_ <= TRACE) {
		print_time();
		print_text(std::cout, text);
		write_logfile("Trace: " + text);
	};
};

void Logger::info(std::string text) {
	if (mode_ <= INFO) {
		print_time();
		print_text(std::cout, text, BLUE);
		write_logfile("Info: " + text);
	};
};

void Logger::warn(std::string text) {
	if (mode_ <= WARNING) {
		print_time();
		print_text(std::cout, text, YELLOW);
		write_logfile("Warning: " + text);
	};
};

void Logger::error(std::string text) {
	if (mode_ <= ERRORS) {
		print_time();
		print_text(std::cerr, text, RED);
		write_logfile("Error: " + text);
	};
};

void Logger::fatal(std::string text) {
	print_time();
	print_text(std::cerr, text, PURPLE);
	write_logfile("Fatal: " + text);
};

// Functionality

void Logger::set_params(MODE mode, bool verbose) {
	mode_ = mode;
	verbose_ = verbose;
};

void Logger::set_text_color(COLOR color) {
	switch (color) {
	case RED:    SetConsoleTextAttribute(hwnd_, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case BLUE:   SetConsoleTextAttribute(hwnd_, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case GREEN:  SetConsoleTextAttribute(hwnd_, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case YELLOW: SetConsoleTextAttribute(hwnd_, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case WHITE:  SetConsoleTextAttribute(hwnd_, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case PURPLE: SetConsoleTextAttribute(hwnd_, FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	default:     SetConsoleTextAttribute(hwnd_, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	}
};

void Logger::print_time() {
	if (verbose_)
		std::cout << get_time() << barrier_;
};

void Logger::print_text(std::ostream& out, const std::string& text, COLOR color) {
	if (verbose_) {
		set_text_color(color);
		out << text << std::endl;
		set_text_color(WHITE);
	}
}
void Logger::write_logfile(const std::string& text) {
	logfile_ << text << std::endl;
};

void Logger::simple_test() {
	trace("Trace: Everything is good.");
	info("Info: Our warriors are perfectly ammunated.");
	warn("Warning: Orcs are on the outskirts of the mountain!");
	error("Error: We can't figure out if they are orcs or not.");
	fatal("Fatal: ORCS ARE HERE!");
}

