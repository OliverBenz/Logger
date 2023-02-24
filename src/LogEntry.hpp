#pragma once

#include "LogLevel.hpp"

#include <string>
#include <vector>

namespace Logging {

class LogEntry{
public:
	LogEntry(LogLevel level);

    //! Log new text.
	LogEntry& operator<<(const std::string& text);

    //! Returns the logged text.
	std::string LoggedText() const;

private:
	LogLevel m_level;                       //!< Log level of this one entry.
	std::vector<std::string> m_textInputs;  //!< All log entries.
    // TODO: Do i want this separate? Just append immediately..
};

}