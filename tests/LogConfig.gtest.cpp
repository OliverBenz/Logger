#include "gtest/gtest.h"

#include "LogConfig.hpp"

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
    // TODO: 
    //  - Check add all available log outputs
}

}
}
