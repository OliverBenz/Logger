#include "LogEntry.hpp"

namespace Logging {

LogEntry::LogEntry(LogLevel level) : m_level(level)
{}

LogEntry& LogEntry::operator<<(const std::string& text) {
    m_text += text;
    return *this;
}

std::string LogEntry::LoggedText() const {
    return m_text;
}

}