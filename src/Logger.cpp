#include "Logger.hpp"

namespace Logging {

Logger::Logger(LogConfig& config) : m_config(config)
{}

Logger::~Logger() {
    for (const auto& output : m_config.LogOutputs()) {
        output->Write(m_entries);
    }
}

LogEntry& Logger::operator<<(LogLevel level) {
    m_entries.emplace_back(LogEntry(level));
    return m_entries.back();
}

}