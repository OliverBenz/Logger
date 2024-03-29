#include "LogOutputConsole.hpp"

namespace Logging {

void LogOutputConsole::Write(const std::vector<LogEntry>& logEntries) {
	// TODO: cout or cerr
	for (const auto& entry: logEntries) {
		std::cout << entry.OutputText() << "\n";
	}
}

void LogOutputConsole::Write(const LogEntry& entry) {
	std::cout << entry.OutputText() << "\n";
}

}  // namespace Logging