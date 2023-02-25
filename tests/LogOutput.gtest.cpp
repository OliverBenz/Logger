#include "gtest/gtest.h"

#include "Logger.hpp"
#include "LogLevel.hpp"
#include "LogOutputConsole.hpp"
#include "LogOutputMock.hpp"
#include "LogOutputFile.hpp"

namespace Logging {
namespace GTest {

TEST(LogOutput, Mock) {
    auto mock = std::make_shared<LogOutputMock>();

    LogConfig config;
	config.AddLogOutput(mock);

	{
		Logger logger = Logger(config);
		logger << LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << LogLevel::Debug << "Debug" << " Entry";
		logger << LogLevel::Error << "Error text";
	}

    EXPECT_EQ(mock->m_logEntries.size(), 3);
    
	EXPECT_STREQ(mock->m_logEntries[0].GetText().c_str(), "This is a test.");
	EXPECT_EQ(mock->m_logEntries[0].GetLevel(), LogLevel::Info);

    EXPECT_STREQ(mock->m_logEntries[1].GetText().c_str(), "Debug Entry");
	EXPECT_EQ(mock->m_logEntries[1].GetLevel(), LogLevel::Debug);

    EXPECT_STREQ(mock->m_logEntries[2].GetText().c_str(), "Error text");
	EXPECT_EQ(mock->m_logEntries[2].GetLevel(), LogLevel::Error);
}

TEST(LogOutput, File) {
    auto logFile1 = std::make_shared<LogOutputFile>("Log1.txt");
	auto logFile2 = std::make_shared<LogOutputFile>("Log2.txt");

    LogConfig config;
	config.AddLogOutput(logFile1);
	config.AddLogOutput(logFile2);

	{
		Logger logger = Logger(config);
		logger << LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << LogLevel::Debug << "Debug" << " Entry";
		logger << LogLevel::Error << "Error text";
	}

	// TODO: Read file for output

	// Cleanup
	EXPECT_EQ(std::remove(logFile1->FilePath().c_str()), 0);
	EXPECT_EQ(std::remove(logFile2->FilePath().c_str()), 0);
}

}
}