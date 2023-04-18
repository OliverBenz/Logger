#pragma once

#include "LogConfig.hpp"
#include "LogEntry.hpp"
#include "LogLevel.hpp"

#include <mutex>
#include <vector>

namespace Logging {

class Logger {
public:
	Logger(LogConfig& config);

	//! The destructor logs the entries to the specified outputs.
	~Logger();

	//! Manually write the log entries to the specified outputs.
	void Flush();

	//! Add a new log entry with the specified log level.
	void Log(LogLevel level, const std::string& text);

private:
	LogConfig& m_config;  //!< Configuration by which this logger object should adhere.
	std::vector<LogEntry> m_entries;  //!< List of log entries received.
};

}  // namespace Logging
