#include "LogEntry.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>

namespace Logging {

LogEntry::LogEntry(LogLevel level) : m_level(level)
{
    const auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeNow), "%d.%m.%Y %H:%M:%S");
    m_time = ss.str();
}

LogEntry& LogEntry::operator<<(const std::string& text) {
    m_text += text;
    return *this;
}

std::string LogEntry::OutputText() const {
    return m_time + " " + LevelToText(m_level) + " " + m_text;  
}

std::string LogEntry::GetText() const {
    return m_text;
}

std::string LogEntry::GetTime() const {
    return m_time;
}

LogLevel LogEntry::GetLevel() const {
    return m_level;
}

}