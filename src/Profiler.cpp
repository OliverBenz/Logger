#include "Logger/Profiler.hpp"

#include <format>

namespace Logging {

Profiler::Profiler(Logger logger, std::string identifier)
    : m_logger(std::move(logger)), m_identifier(std::move(identifier)) {
	m_startTime = std::chrono::steady_clock::now();
	m_lastTime = m_startTime;

	m_logger.Log(Logging::LogLevel::Info, std::format("--> {} START", m_identifier));
}

Profiler::~Profiler() {
	const auto now = std::chrono::steady_clock::now();
	const auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();  // t in ms
	m_logger.Log(Logging::LogLevel::Info, std::format("<-- {} END: {}ms", m_identifier, timeMs));
}

void Profiler::LogStep(const std::string& stepName) {
	const auto now = std::chrono::steady_clock::now();
	const auto stepMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTime).count();  // t in ms
	const auto totalMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();  // t in ms
	m_logger.Log(Logging::LogLevel::Info,
	             std::format("--- {} STEP {}: +{}ms ({}ms total)", m_identifier, stepName, stepMs, totalMs));
	m_lastTime = now;
}


}  // namespace Logging
