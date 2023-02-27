#include "gtest/gtest.h"

#include "LogEntry.hpp"
#include <regex>

namespace Logging {
namespace GTest {

TEST(LogEntry, OutputFormat) {
    LogEntry logEntry(LogLevel::Info);
    logEntry << "This is a " << "test";
    const std::string expected = "[Info] This is a test";

    EXPECT_TRUE(logEntry.OutputText().find(expected) != std::string::npos);

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
