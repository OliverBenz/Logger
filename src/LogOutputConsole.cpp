#include "Logger/LogOutputConsole.hpp"

#include <iostream>

namespace Logging {

void LogOutputConsole::Write(const std::vector<LogEntry>& logEntries) {
	for (const auto& entry: logEntries) {
		std::clog << entry.OutputText() << "\n";
	}
}

void LogOutputConsole::Write(const LogEntry& entry) {
	std::clog << entry.OutputText() << "\n";
}

} // namespace Logging
