#include "LogEntry.hpp"

namespace Logging {

LogEntry::LogEntry(LogLevel level) : m_level(level)
{}

LogEntry& LogEntry::operator<<(const std::string& text) {
    m_textInputs.emplace_back(text);
    return *this;
}

std::string LogEntry::LoggedText() const {
    std::string result;
    for (const auto& entry : m_textInputs) {
        result += entry;
    }
    return result;
}

}