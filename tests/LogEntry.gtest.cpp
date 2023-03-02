#include "gtest/gtest.h"

#include "LogEntry.hpp"
#include <regex>

namespace Logging {
namespace GTest {

TEST(LogEntry, OutputFormat) {
    LogEntry logEntry{LogLevel::Info, "This is a test", "2023-02-03 15:47:00"};
    const std::string expected = "2023-02-03 15:47:00 [Info] This is a test";

    EXPECT_STREQ(logEntry.OutputText().c_str(), expected.c_str());

/*
    std::regex r("%d%d.%d%d.%d%d %d%d-%d%d-%d%d%d%d [%s] %s");

    std::smatch match;
    std::regex_search(logEntry.OutputText(), match, r);
*/
    // TODO:
    //   - Check the output string has proper format. Should formatting be job of entry? For now ok.
    //   - Use all functions once so it's covered..
}

}
}
