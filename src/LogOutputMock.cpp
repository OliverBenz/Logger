#include "LogOutputMock.hpp"

namespace Logging {

void LogOutputMock::Write(const std::vector<LogEntry>& logEntries) {
	for (std::size_t i = 0; i != logEntries.size(); ++i) {
		// TODO: Properly copy all at once..
		m_logEntries.emplace_back(logEntries[i]);
	}
}

void LogOutputMock::Write(const LogEntry& entry) {
	m_logEntries.emplace_back(entry);
}

}  // namespace Logging
