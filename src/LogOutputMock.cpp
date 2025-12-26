#include "Logger/LogOutputMock.hpp"

namespace Logging {

void LogOutputMock::Write(const std::vector<LogEntry>& logEntries) {
	m_logEntries.insert(m_logEntries.end(), logEntries.begin(), logEntries.end());
}

void LogOutputMock::Write(const LogEntry& entry) {
	m_logEntries.emplace_back(entry);
}

}  // namespace Logging
