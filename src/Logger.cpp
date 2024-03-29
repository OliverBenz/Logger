#include "Logger.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace Logging {

Logger::Logger(LogConfig& config) : m_config(config) {
}

Logger::~Logger() {
	Flush();
}

void Logger::Flush() {
	for (const auto& output: m_config.LogOutputs()) {
		output->Write(m_entries);
	}
	m_entries.clear();
}


void Logger::Log(const LogLevel level, const std::string& text) {
	if (!m_config.LoggingEnabled() || level < m_config.MinLogLevel()) {
		return;
	}

	// Get current time
	const auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream time;
	time << std::put_time(std::localtime(&timeNow), "%d.%m.%Y %H:%M:%S");

	LogEntry entry{level, text, time.str()};
	m_entries.emplace_back(entry);
}

}  // namespace Logging