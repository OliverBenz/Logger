#pragma once

#include "Logger.hpp"

namespace Logging {

class Profiler {
public:
	//! Construction of the object also marks the start time for profiling.
	Profiler(Logger logger, std::string identifier);

	//! Destructor logs the total profiling time.
	~Profiler();

	//! Log an intermediate profiling step with a given name.
	void LogStep(const std::string& stepName);

private:
	Logger m_logger;
	std::string m_identifier;

	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	std::chrono::time_point<std::chrono::steady_clock> m_lastTime;
};

}  // namespace Logging