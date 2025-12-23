#include "gtest/gtest.h"

#include "LogEntry.hpp"
#include <regex>

namespace Logging {
namespace GTest {

TEST(LogEntry, OutputFormat) {
	LogEntry logEntry{LogLevel::Info, "This is a test", "2023-02-03 15:47:00"};
	const std::string expected = "2023-02-03 15:47:00 [Info] This is a test";

	EXPECT_STREQ(logEntry.OutputText().c_str(), expected.c_str());
}

TEST(LogEntry, OutputTextPattern) {
	LogEntry logEntry{LogLevel::Warning, "Pattern Check", "01.02.2023 03:04:05"};
	const auto output = logEntry.OutputText();

	std::regex pattern(R"(^\d{2}\.\d{2}\.\d{4} \d{2}:\d{2}:\d{2} \[Warning\] Pattern Check$)");
	EXPECT_TRUE(std::regex_match(output, pattern));
}

}  // namespace GTest
}  // namespace Logging
