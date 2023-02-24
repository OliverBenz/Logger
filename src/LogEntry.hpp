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

    //! Returns the logged text.
	std::string LoggedText() const;

public:
	LogLevel m_level;   //!< Log level of this one entry.
	std::string m_text; //!< All log entries.
};

}