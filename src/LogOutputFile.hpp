#pragma once

#include "ILogOutput.hpp"
#include <string>

namespace Logging {

class LogOutputFile : public ILogOutput {
public:
    LogOutputFile(const std::string& fileName);

	void Write(const std::vector<LogEntry>& logEntries) override;
    void Write(const LogEntry& entry) override;

public:
    std::string m_fileName;
};

}