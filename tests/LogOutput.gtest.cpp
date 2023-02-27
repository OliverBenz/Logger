#include "gtest/gtest.h"

#include "Logger.hpp"
#include "LogLevel.hpp"
#include "LogOutputConsole.hpp"
#include "LogOutputMock.hpp"
#include "LogOutputFile.hpp"
#include <filesystem>
#include <fstream>

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

TEST(LogOutput, FileBasic) {
    auto logFile1 = std::make_shared<LogOutputFile>("Log1.txt");
	auto logFile2 = std::make_shared<LogOutputFile>("Log2.txt");

    LogConfig config;
	config.AddLogOutput(logFile1);
	config.AddLogOutput(logFile2);

	std::array<std::string, 3> expectOutput {
		"[Info] This is a test.",
		"[Debug] Debug Entry",
		"[Error] Error text"
	};

	//! Lambda to check a files content is the expectedOutput.
	auto compareExpect = [&expectOutput](const std::string& fileName) {
		// Read file and compare
		std::ifstream file(fileName.c_str());
		unsigned counter = 0;
		std::string text;
		while(getline(file, text)) {
			// line contains the timestap so we use .find()
			EXPECT_TRUE(text.find(expectOutput[counter]) != std::string::npos);
			++counter;
		}
		file.close();
	};

	// Write data to file
	{
		Logger logger = Logger(config);
		logger << LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << LogLevel::Debug << "Debug" << " Entry";
		logger << LogLevel::Error << "Error text";
	}

	// Check the file content is as expected
	compareExpect(logFile1->FilePath());
	compareExpect(logFile2->FilePath());

	// Cleanup
	EXPECT_EQ(std::remove(logFile1->FilePath().c_str()), 0);
	EXPECT_EQ(std::remove(logFile2->FilePath().c_str()), 0);
}

TEST(LogOutput, FileMaxSize) {
	static constexpr std::uintmax_t maxSize = 50;
    auto logFile = std::make_shared<LogOutputFile>("Logfile.txt", maxSize);

    LogConfig config;
	config.AddLogOutput(logFile);

	// With timestamp/loglevel, this string produces output > maxSize Bytes
	const std::string testString('a', maxSize);

	// Write to output file
	{
		Logger(config) << LogLevel::Info << testString;
	}
	EXPECT_FALSE(std::filesystem::exists("Logfile.txt"));    // New file only created after next write
	EXPECT_TRUE(std::filesystem::exists("Logfile(1).txt"));  // Wrapping happens after a write
	EXPECT_FALSE(std::filesystem::exists("Logfile(2).txt")); // Does not exist yet

	// Less than maxSize Bytes
	{
		Logger(config) << LogLevel::Info << "a";	
	}
	EXPECT_TRUE(std::filesystem::exists("Logfile.txt"));     // New write -> Create file again
	EXPECT_TRUE(std::filesystem::exists("Logfile(1).txt"));  // Still exists
	EXPECT_FALSE(std::filesystem::exists("Logfile(2).txt")); // Does not exist yet

	// Fill the current log file
	{
		Logger(config) << LogLevel::Debug << testString;
	}
	EXPECT_FALSE(std::filesystem::exists("Logfile.txt"));    // New file only created after new write
	EXPECT_TRUE(std::filesystem::exists("Logfile(1).txt"));  // Still exists
	EXPECT_TRUE(std::filesystem::exists("Logfile(2).txt"));  // Newly created from write
	EXPECT_FALSE(std::filesystem::exists("Logfile(3).txt"));  // Does not exist yet

	// Fill two files worth (whole will be in one file -> One write operation)
	{
		Logger logger = Logger(config);
		logger << LogLevel::Debug << testString;
		logger << LogLevel::Debug << testString;
	}
	EXPECT_FALSE(std::filesystem::exists("Logfile.txt"));    // New file only created after new write
	EXPECT_TRUE(std::filesystem::exists("Logfile(1).txt"));  // Still exists
	EXPECT_TRUE(std::filesystem::exists("Logfile(2).txt"));  // Still exists
	EXPECT_TRUE(std::filesystem::exists("Logfile(3).txt"));  // Newly created from write -> One log write always to one file
	EXPECT_FALSE(std::filesystem::exists("Logfile(4).txt"));  // Does not exist

	// Cleanup
	EXPECT_NE(std::remove("Logfile.txt"), 0);     // Does not exist
	EXPECT_EQ(std::remove("Logfile(1).txt"), 0);
	EXPECT_EQ(std::remove("Logfile(2).txt"), 0);
	EXPECT_EQ(std::remove("Logfile(3).txt"), 0);
	EXPECT_NE(std::remove("Logfile(4).txt"), 0);  // Does not exist
}

}
}