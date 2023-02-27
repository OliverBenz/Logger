#include "gtest/gtest.h"

#include "LogConfig.hpp"
#include "LogOutputFile.hpp"
#include "LogOutputMock.hpp"
#include "LogOutputConsole.hpp"

namespace Logging {
namespace GTest {

TEST(LogConfig, DisableLogging) {
    // TODO:
    //  - Check enable/disable logging and entries not added if disabled
    //  - Performance check -> Minimal overhead if logging is disabled

}

TEST(LogConfig, MinLogLevel) {
    // TODO:
    //  - Log with different log levels and check output correct
    //  - Check log entry not added to list of entries if below minLogLevel
    //  - Performance check -> Minimal overhead if loglevel too low 
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
