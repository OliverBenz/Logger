#include "gtest/gtest.h"

#include "LogConfig.hpp"
#include "LogOutputMock.hpp"
#include "Profiler.hpp"

#include <chrono>
#include <thread>

namespace Logging {
namespace GTest {

TEST(Profiler, LogsStartStepsAndEnd) {
	LogConfig config;
	auto mock = std::make_shared<LogOutputMock>();
	config.AddLogOutput(mock);

	{
		Logger logger(config);
		Profiler profiler(logger, "ProfileCase");

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		profiler.LogStep("First");
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		profiler.LogStep("Second");
	}

	ASSERT_EQ(mock->m_logEntries.size(), 4u);
	EXPECT_NE(mock->m_logEntries[0].m_text.find("ProfileCase"), std::string::npos);
	EXPECT_NE(mock->m_logEntries[0].m_text.find("START"), std::string::npos);

	EXPECT_NE(mock->m_logEntries[1].m_text.find("STEP First"), std::string::npos);
	EXPECT_NE(mock->m_logEntries[1].m_text.find("ms"), std::string::npos);

	EXPECT_NE(mock->m_logEntries[2].m_text.find("STEP Second"), std::string::npos);
	EXPECT_NE(mock->m_logEntries[2].m_text.find("ms"), std::string::npos);

	EXPECT_NE(mock->m_logEntries[3].m_text.find("END"), std::string::npos);
	EXPECT_NE(mock->m_logEntries[3].m_text.find("ProfileCase"), std::string::npos);
}

}  // namespace GTest
}  // namespace Logging
