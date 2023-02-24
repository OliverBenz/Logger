#include "LogLevel.hpp"

namespace Logging {

std::string LevelToText(LogLevel level) {
    switch (level) {
    case LogLevel::Any:
        return "[Any]";
    case LogLevel::Info:
        return "[Info]";
    case LogLevel::Debug:
        return "[Debug]";
    case LogLevel::Warning:
        return "[Warning]";
    case LogLevel::Error:
        return "[Error]";
    case LogLevel::Critical:
        return "[Critical]";
    }
    return "";
}

}