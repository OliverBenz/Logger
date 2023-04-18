#include "Profiler.hpp"
#include <fmt/core.h>

namespace Logging {

Profiler::Profiler(Logger logger, std::string identifier)
    : m_logger(std::move(logger)), m_identifier(std::move(identifier)) {
	m_startTime = std::chrono::steady_clock::now();
	m_lastTime = m_startTime;

	m_logger.Log(Logging::LogLevel::Info, fmt::format("--> {} START", m_identifier));
}

Profiler::~Profiler() {
	const auto now = std::chrono::steady_clock::now();
	const auto timeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime).count();  // t in ms
	m_logger.Log(Logging::LogLevel::Info, fmt::format("<-- {} END: ", m_identifier, timeMs));
}

void Profiler::LogStep(const std::string& stepName) {
	const auto timeMs =
	        std::chrono::duration_cast<std::chrono::milliseconds>(m_lastTime - m_startTime).count();  // t in ms
	m_logger.Log(Logging::LogLevel::Info, fmt::format("--- {} STEP {}: ", m_identifier, stepName, timeMs));
	m_lastTime = std::chrono::steady_clock::now();
}


}  // namespace Logging