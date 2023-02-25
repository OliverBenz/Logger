#pragma once

#include "LogLevel.hpp"

#include <string>
#include <sstream>

namespace Logging {

class LogEntry{
public:
	LogEntry(LogLevel level);

    //! Log new text.
	LogEntry& operator<<(const std::string& text);

	//! Returns the logged text formatted with the log level.
	std::string OutputText() const;

    //! Returns the logged text.
	std::string GetText() const;

	//! Returns the timeStamp of the log entry.
	std::string GetTime() const;
	
	//! Returns the log level of the entry.
	LogLevel GetLevel() const;

private:
	LogLevel m_level;   //!< Log level of this one entry.
	std::string m_time; //!< Timestamp of the log entry.
	std::string m_text; //!< All log entries.
};

}