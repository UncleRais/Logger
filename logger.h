#pragma once

#include "logger_utils.h"

static std::fstream empty;

struct stream_base {
	std::ostream& out;
	explicit stream_base(std::ostream& out)
		: out{ out } {}
	virtual ~stream_base() noexcept = default;
};

struct cout_stream : public stream_base {
	explicit cout_stream() noexcept
		: stream_base{ std::cout } {}
};

struct cerr_stream : public stream_base {
	explicit cerr_stream() noexcept
		: stream_base{ std::cerr } {}
};

struct file_stream : public stream_base {
	std::fstream file;
	explicit file_stream(const std::filesystem::path& path)
		: stream_base{ file }
		, file{ path, std::ofstream::out } {}
};

class Logger {
	private:		

		std::unique_ptr<stream_base> _out;
		MODE _mode = TRACE;
		bool _colored = true;

	protected:
		Logger() {
			log(DEBUG) << "Logger is initialized." << std::endl;
		};

		Logger(const MODE& mode = TRACE, std::unique_ptr<stream_base>&& out = nullptr) : _mode(mode), _out(std::move(out)){
			_colored = !bool(dynamic_cast<file_stream*>(_out.get()));
			log(DEBUG) << "Logger is initialized." << std::endl;
		};

		Logger(const Logger& log) {};
		Logger& operator= (Logger&) {};

		~Logger() {
			log(DEBUG) << "Logger is destructred." << std::endl;
			if (_colored) reset_color(_out->out);
		};

	public:
		static Logger& get(const MODE& mode = TRACE, std::unique_ptr<stream_base>&& out = nullptr) {

			static Logger log{ mode, out ? std::move(out) : std::make_unique<cout_stream>() };
			return log;
		};

		std::ostream& log(const MODE& mode) {
			if (_mode <= mode) {
					_out->out << general_line(mode, _colored);
				return _out->out;
			}
			return empty;
		};
};
