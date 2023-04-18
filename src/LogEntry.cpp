#include "LogEntry.hpp"

#include <fmt/core.h>

namespace Logging {

std::string LogEntry::OutputText() const {
	return fmt::format("{} {} {}", m_time, LevelToText(m_level), m_text);
}

}  // namespace Logging