#pragma once

#include "ILogOutput.hpp"
#include <iostream>

namespace Logging {

class LogOutputConsole : public ILogOutput {
public:
    LogOutputConsole() = default;

	void Write(const std::vector<LogEntry>& logEntries) override {
        // TODO: cout or cerr
        for (const auto& entry : logEntries) {
            std::cout << LevelToText(entry.m_level) << "TODO";
        }
    }
};

}