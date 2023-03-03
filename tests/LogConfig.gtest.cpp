#include "gtest/gtest.h"

#include "Logger.hpp"
#include "LogConfig.hpp"
#include "LogOutputFile.hpp"
#include "LogOutputMock.hpp"
#include "LogOutputConsole.hpp"

namespace Logging {
namespace GTest {

TEST(LogConfig, DisableLogging) {
	Logging::LogConfig config;
	auto mock = std::make_shared<Logging::LogOutputMock>();
	config.AddLogOutput(mock);

	Logger logger(config);

	// Disbled logging
	config.SetLogEnabled(false);
	logger.Log(LogLevel::Info,  "Testing Entry 1");
	logger.Log(LogLevel::Debug, "Testing Entry 2");
	logger.Log(LogLevel::Error, "Testing Entry 3");
	logger.Flush();

	EXPECT_EQ(mock->m_logEntries.size(), 0u);

	// Enable logging
	config.SetLogEnabled(true);
	logger.Log(LogLevel::Info,  "Testing Entry 1");
	logger.Log(LogLevel::Debug, "Testing Entry 2");
	logger.Flush();

	EXPECT_EQ(mock->m_logEntries.size(), 2u);

	// Disbled logging
	config.SetLogEnabled(false);
	logger.Log(LogLevel::Info,  "Testing Entry 1");
	logger.Log(LogLevel::Debug, "Testing Entry 2");
	logger.Flush();

	EXPECT_EQ(mock->m_logEntries.size(), 2u); // Still 2 entries
}

TEST(LogConfig, MinLogLevel) {
	Logging::LogConfig config;
	auto mock = std::make_shared<Logging::LogOutputMock>();
	config.AddLogOutput(mock);

	Logger logger(config);

	//! Add 5 log entries and check the mock contains the expected amount of entries.
	const auto RunTest = [&](const std::size_t expectCount) {
		logger.Log(LogLevel::Info,    "This is info.");
		logger.Log(LogLevel::Debug,   "This is debug.");
		logger.Log(LogLevel::Warning, "This is warning.");
		logger.Log(LogLevel::Error,   "This is error.");
		logger.Log(LogLevel::Critical,"This is critical.");
		logger.Flush();

		EXPECT_EQ(mock->m_logEntries.size(), expectCount);
		mock->m_logEntries.clear();
	};

	// Minimum: Any by default
	RunTest(5u);

	// Minimum: Debug
	config.SetMinLogLevel(LogLevel::Debug);
	RunTest(4u);

	// Minimum: Warning
	config.SetMinLogLevel(LogLevel::Warning);
	RunTest(3u);

	// Minimum: Error
	config.SetMinLogLevel(LogLevel::Error);
	RunTest(2u);

	// Minimum: Critical
	config.SetMinLogLevel(LogLevel::Critical);
	RunTest(1u);
}

TEST(LogConfig, LogOutputs) {
	static Logging::LogConfig config;
	auto mock = std::make_shared<Logging::LogOutputMock>();
	auto logFile = std::make_shared<Logging::LogOutputFile>("LogSectionA.txt");
	auto logFile1 = std::make_shared<Logging::LogOutputFile>("LogSectionB.txt");
	auto logFile2 = std::make_shared<Logging::LogOutputFile>("LogSectionC.txt");

	config.AddLogOutput(std::make_shared<Logging::LogOutputConsole>());
	config.AddLogOutput(mock);
	config.AddLogOutput(logFile);
	config.AddLogOutput(logFile1);
	config.AddLogOutput(logFile2);

	EXPECT_EQ(config.LogOutputs().size(), 5u);
}

}
}
