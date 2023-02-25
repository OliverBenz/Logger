#include "gtest/gtest.h"

#include "LogLevel.hpp"

namespace Logging {
namespace GTest {

TEST(LogLevel, LevelToText) {
    EXPECT_STREQ(LevelToText(LogLevel::Any).c_str(), "[Any]");
    EXPECT_STREQ(LevelToText(LogLevel::Info).c_str(), "[Info]");
    EXPECT_STREQ(LevelToText(LogLevel::Debug).c_str(), "[Debug]");
    EXPECT_STREQ(LevelToText(LogLevel::Warning).c_str(), "[Warning]");
    EXPECT_STREQ(LevelToText(LogLevel::Error).c_str(), "[Error]");
    EXPECT_STREQ(LevelToText(LogLevel::Critical).c_str(), "[Critical]");
}

}
}
