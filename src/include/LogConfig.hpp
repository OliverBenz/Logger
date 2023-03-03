#pragma once

#include "LogLevel.hpp"
#include "ILogOutput.hpp"

#include <vector>
#include <memory>

namespace Logging {

//! Configuration for a logger object.
class LogConfig {
public:
    //! Add a new log sink to the configuration.
	void AddLogOutput(std::shared_ptr<ILogOutput> output);

	//! Get a list of all log outputs in the config.
	const std::vector<std::shared_ptr<ILogOutput>>& LogOutputs();

	//! Set if logging is enabled or not.
	void SetLogEnabled(bool enable);

	//! Get if the logging is enabled of not. 
	bool LoggingEnabled() const;

	//! Set the minimum log level to be output.
	void SetMinLogLevel(LogLevel logLevel);

	//! Get the minimum log level.
	LogLevel MinLogLevel() const;

private:
	bool m_logEnabled = true;                               //!< Enable/Disable logging.
	LogLevel m_minLogLevel = LogLevel::Any;                 //!< Only log messages with severity above this.
	std::vector<std::shared_ptr<ILogOutput>> m_logOutputs;  //!< Where to write the log data to.
};

}