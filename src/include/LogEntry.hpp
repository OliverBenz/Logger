#pragma once

#include "LogLevel.hpp"

#include <string>
#include <sstream>

namespace Logging {

struct LogEntry {
	//! Returns the formatted log entry data.
	std::string OutputText() const;

	LogLevel m_level;   //!< Log level of this one entry.
	std::string m_text; //!< All log entries.
	std::string m_time; //!< Timestamp of the log entry.
};

}