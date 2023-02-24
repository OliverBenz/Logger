#pragma once

#include <vector>
#include <string>

enum class LogLevel {
	Any      = 000,
	Info     = 100,
	Debug    = 200,
	Warning  = 300,
	Error    = 400,
	Critical = 500
};


class ILogOutput {
public:
	ILogOutput() = delete;
	~ILogOutput() = delete;
	virtual void Write() = 0; 
};


class LogConfig {
public:
	void AddLogOutput(ILogOutput output) {
		m_logOutputs.emplace_back(output);
	}

private:
	bool m_logEnabled;                      //!< Enable/Disable logging.
	LogLevel m_minLogLevel = LogLevel::Any; //!< Only log messages with severity above this.
	std::vector<ILogOutput> m_logOutputs;   //!< Where to write the log data to.
};



class LogEntry{
public:
	LogEntry(LogLevel level) : m_level(level)
	{}

	LogEntry& operator<<(const std::string& text) {
		m_textInputs.emplace_back(text);
		return *this;
	}

	std::string LoggedText() const {
		std::string result;
		for (const auto& entry : m_textInputs) {
			result += entry;
		}
		return result;
	}

private:
	LogLevel m_level;
	std::vector<std::string> m_textInputs;  // TODO: Do i want this separate? Just append immediately..
};


class Logger {
public:
	Logger(LogConfig& config) : m_config(config)
	{}
	
	~Logger() {
		for(const auto& entry: m_entries) {
			// TODO: Have multiple options how to output
			std::cout << entry.LoggedText() << std::endl;
		}
	}

	LogEntry& operator<<(LogLevel level) {
		m_entries.emplace_back(LogEntry(level));
		return m_entries.back();
	}

private:
	LogConfig& m_config;              //!< Configuration by which this logger object should adhere.
	std::vector<LogEntry> m_entries;  //!< List of log entries received.
};
