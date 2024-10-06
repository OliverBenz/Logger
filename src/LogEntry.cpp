#include "LogEntry.hpp"

#include <format>

namespace Logging {

std::string LogEntry::OutputText() const {
	return std::format("{} {} {}", m_time, LevelToText(m_level), m_text);
}

}  // namespace Logging