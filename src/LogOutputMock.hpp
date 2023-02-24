#pragma once

#include "ILogOutput.hpp"

namespace Logging {

//! Mock that just stored all log data in class member.
class LogOutputMock : public ILogOutput {
public:

	void Write(const std::vector<LogEntry>& logEntries) override {
        for (std::size_t i = 0; i != logEntries.size(); ++i) {
            // TODO: Properly copy all at once..
            m_logEntries.emplace_back(logEntries[i]);
        }
    }

private:
    std::vector<LogEntry> m_logEntries;
};

}