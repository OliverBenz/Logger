#include "gtest/gtest.h"

#include "Logger.hpp"
#include "LogLevel.hpp"
#include "LogOutputConsole.hpp"
#include "LogOutputMock.hpp"
#include "LogOutputFile.hpp"

TEST(LogOutput, Mock) {
    auto mock = std::make_shared<Logging::LogOutputMock>();

    Logging::LogConfig config;
	config.AddLogOutput(mock);

	{
		Logging::Logger logger = Logging::Logger(config);
		logger << Logging::LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << Logging::LogLevel::Debug << "Debug" << " Entry";
		logger << Logging::LogLevel::Error << "Error text";
	}

    EXPECT_EQ(mock->m_logEntries.size(), 3);
    EXPECT_STREQ(mock->m_logEntries[0].OutputText().c_str(), "[Info] This is a test.");
    EXPECT_STREQ(mock->m_logEntries[1].OutputText().c_str(), "[Debug] Debug Entry");
    EXPECT_STREQ(mock->m_logEntries[2].OutputText().c_str(), "[Error] Error text");
}

TEST(LogOutput, File) {
    auto file = std::make_shared<Logging::LogOutputFile>("/home/oliver/dev/Log.txt");

    Logging::LogConfig config;
	config.AddLogOutput(file);

	{
		Logging::Logger logger = Logging::Logger(config);
		logger << Logging::LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << Logging::LogLevel::Debug << "Debug" << " Entry";
		logger << Logging::LogLevel::Error << "Error text";
	}
}
