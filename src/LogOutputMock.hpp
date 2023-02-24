#pragma once

#include "ILogOutput.hpp"

namespace Logging {

//! Mock that just stored all log data in class member.
class LogOutputMock : public ILogOutput {
public:
	void Write(const std::vector<LogEntry>& logEntries) override;
    void Write(const LogEntry& entry) override;

private:
    std::vector<LogEntry> m_logEntries;
};

}