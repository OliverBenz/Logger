#include "Logger.hpp"

#include <iostream>

namespace Logging {

Logger::Logger(LogConfig& config) : m_config(config)
{}

Logger::~Logger() {
    for(const auto& entry: m_entries) {
        // TODO: Have multiple options how to output
        std::cout << entry.LoggedText() << std::endl;
    }
}

LogEntry& Logger::operator<<(LogLevel level) {
    m_entries.emplace_back(LogEntry(level));
    return m_entries.back();
}

}