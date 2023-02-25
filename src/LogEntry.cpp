#include "LogEntry.hpp"

namespace Logging {

LogEntry::LogEntry(LogLevel level) : m_level(level)
{}

LogEntry& LogEntry::operator<<(const std::string& text) {
    m_text += text;
    return *this;
}

std::string LogEntry::GetText() const {
    return m_text;
}

std::string LogEntry::OutputText() const {
    return LevelToText(m_level) + " " + m_text;  
}

}