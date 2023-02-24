#include "LogOutputConsole.hpp"

namespace Logging {

void LogOutputConsole::Write(const std::vector<LogEntry>& logEntries) {
    // TODO: cout or cerr
    for (const auto& entry : logEntries) {
        std::cout << LevelToText(entry.m_level) << " " << entry.LoggedText() << "\n";
    }
}

void LogOutputConsole::Write(const LogEntry& entry) {
    std::cout << LevelToText(entry.m_level) << "TODO";
}

}