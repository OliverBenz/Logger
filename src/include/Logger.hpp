#pragma once

#include "LogConfig.hpp"
#include "LogEntry.hpp"
#include "LogLevel.hpp"

#include <vector>
#include <mutex>

namespace Logging {

class Logger {
public:
	Logger(LogConfig& config);
	
	//! The destructor logs the entries to the specified outputs.
	~Logger();

	// TODO: Allow intermediate output -> WriteLogEntries function; also clears the m_entries.

	//! Add a new log entry with the specified log level.
	void Log(LogLevel level, const std::string& text);

private:
	LogConfig& m_config;              //!< Configuration by which this logger object should adhere.
	std::vector<LogEntry> m_entries;  //!< List of log entries received.
	std::mutex m_writeLock;           //!< Ensure only one thread access m_logEntries at a time.
};

}
