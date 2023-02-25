#pragma once

#include "ILogOutput.hpp"
#include <iostream>

namespace Logging {

class LogOutputConsole : public ILogOutput {
public:
	void Write(const std::vector<LogEntry>& logEntries) override;
    void Write(const LogEntry& entry) override;
    
};

}