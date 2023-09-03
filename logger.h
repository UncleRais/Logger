#pragma once

#include <time.h>
#include <windows.h>

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

enum MODE {
	TRACE,
	INFO,
	WARNING,
	ERRORS
};

enum COLOR {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE,
	WHITE
};

class LoggerDestroyer;

class Logger {

	private:
		static Logger* p_instance_;
		static LoggerDestroyer destroyer_;

		HANDLE hwnd_ = GetStdHandle(STD_OUTPUT_HANDLE);
		const std::string barrier_ = " >> ";
		std::ofstream logfile_;
		MODE mode_ = TRACE;
		bool verbose_ = false;

	protected:
	//Condtructors and destructors

		Logger() {
			info("Logger is initialized.");
		};

		Logger(std::string filename, MODE mode, bool verbose) {
			set_params(mode, verbose);
			logfile_.open(filename);
			info("Logger is initialized.");
		};

		Logger(const Logger& LOG) {};
		Logger& operator= (Logger&) {};

		~Logger() {
			if (logfile_.is_open()) {
				logfile_.close();
			};
			info("Logger is destructred.");
		};

		friend class LoggerDestroyer;


	public:
	// Getters
		static Logger& getInstance(std::string filename = "logger.txt", MODE mode = TRACE, bool verbose = false);
		std::string get_time();

	// Logger modes
		void trace(std::string text);
		void info(std::string text);
		void warn(std::string text);
		void error(std::string text);
		void fatal(std::string text);

	// Functionality
		void set_params(MODE mode, bool verbose);
		void set_text_color(COLOR color);
		void print_time();
		void print_text(std::ostream& out, const std::string& text, COLOR color = WHITE);
		void write_logfile(const std::string& text);
		void simple_test();
};

class LoggerDestroyer {
	private:
		Logger* p_instance_;
	public:
		LoggerDestroyer(): p_instance_(nullptr){};
		~LoggerDestroyer() {
				delete p_instance_;
		};
		void initialize(Logger* p_instance) { p_instance_ = p_instance; };
};

