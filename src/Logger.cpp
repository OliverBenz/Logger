#include "Logger.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>

namespace Logging {

Logger::Logger(LogConfig& config) : m_config(config)
{}

Logger::~Logger() {
    for (const auto& output : m_config.LogOutputs()) {
        output->Write(m_entries);
    }
}

void Logger::Log(const LogLevel level, const std::string& text) {
    if(!m_config.LoggingEnabled()) {
        return;
    }
    
    // Get current time
    const auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream time;
    time << std::put_time(std::localtime(&timeNow), "%d.%m.%Y %H:%M:%S");

    LogEntry entry{level, text, time.str()};
    
    // Thread safe vector access
    std::unique_lock<std::mutex> lock(m_writeLock);
    m_entries.emplace_back(entry);
}

}