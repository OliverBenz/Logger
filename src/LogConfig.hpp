#pragma once

#include "LogLevel.hpp"
#include "ILogOutput.hpp"

#include <vector>

namespace Logging {

//! Configuration for a logger object.
class LogConfig {
public:
    //! Add a new log sink to the configuration.
	void AddLogOutput(ILogOutput output);

private:
	bool m_logEnabled;                      //!< Enable/Disable logging.
	LogLevel m_minLogLevel = LogLevel::Any; //!< Only log messages with severity above this.
	std::vector<ILogOutput> m_logOutputs;   //!< Where to write the log data to.
};

}