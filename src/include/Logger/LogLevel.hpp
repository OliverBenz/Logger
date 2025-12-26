#pragma once

#include <string>

namespace Logging {

enum class LogLevel { Any = 000, Info = 100, Debug = 200, Warning = 300, Error = 400, Critical = 500 };

std::string LevelToText(LogLevel level);

}  // namespace Logging