#pragma once

#include <vector>
#include <string>

enum class LogLevel {
	Info    = 100,
	Debug   = 200,
	Warning = 300,
	Error   = 400
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

	// TODO: Do i want this separate? Just append immediately..
	std::vector<std::string> m_textInputs;
};


class Logger {
public:
	Logger() = default;
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
	std::vector<LogEntry> m_entries;
};
