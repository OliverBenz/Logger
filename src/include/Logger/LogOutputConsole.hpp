#pragma once

#include "Logger/ILogOutput.hpp"
#include "Logger/LogEntry.hpp"

#include <vector>

namespace Logging {

class LogOutputConsole : public ILogOutput {
public:
	void Write(const std::vector<LogEntry>& logEntries) override;
	void Write(const LogEntry& entry) override;
};

}  // namespace Logging