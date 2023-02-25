#pragma once

#include "LogEntry.hpp"
#include <vector>

namespace Logging {

//! Defines what functionality a log output has to define.
class ILogOutput {
protected:
	ILogOutput() = default;
    ILogOutput(ILogOutput&& other) = default;
    ILogOutput(const ILogOutput& other) = default;

    ILogOutput& operator=(ILogOutput&& other) = default;
    ILogOutput& operator=(ILogOutput const& other) = default;

public:
    virtual ~ILogOutput() = default;

    //! Write multiple log entries to the desired output.
	virtual void Write(const std::vector<LogEntry>& logEntries) = 0;
    
    //! Write a single log entry to the desired output.
    virtual void Write(const LogEntry& entry) = 0;
};

}