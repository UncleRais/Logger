#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

namespace logger {

static std::fstream empty;

struct stream_base {
	std::ostream& _out;
	explicit stream_base(std::ostream& out) : _out{ out } {}
	virtual ~stream_base() noexcept = default;
};

struct cout_stream : public stream_base {
	explicit cout_stream() noexcept : stream_base{ std::cout } {}
};

struct cerr_stream : public stream_base {
	explicit cerr_stream() noexcept : stream_base{ std::cerr } {}
};

struct file_stream : public stream_base {
	std::fstream _file;
	explicit file_stream(const std::filesystem::path& path)
		: stream_base{ _file }, _file{ path, std::ofstream::out } {}
};

enum MODE {
    DEBUG,
    WARNING,
	INFO,
	ERROR,

    n_modes
};

class Logger {
	private:		
		std::unique_ptr<stream_base> _out;
		MODE _mode = MODE::INFO;
        bool _time    = false; 
		bool _colored = true;

	protected:
		Logger() = default;
		Logger(MODE mode = MODE::INFO, bool time = false, std::unique_ptr<stream_base>&& out = nullptr);
		Logger(Logger& log) = delete;
        Logger(Logger&& log) = delete;
		~Logger();

	public:
		static Logger& get(MODE mode = MODE::INFO, bool time = false, std::unique_ptr<stream_base>&& out = nullptr);

		std::ostream& operator()(MODE mode = MODE::INFO);

        template <class T>
        std::ostream& operator << (const T& obj) {
            this->operator()() << obj;
            return _out->_out;
        }

        template <class T>
        std::ostream& operator << (T&& obj) {
            this->operator()() << obj;
            return _out->_out;
        }

        std::streambuf* const get_buffer() const;
        void set_buffer(std::streambuf* const buffer);
};

};
