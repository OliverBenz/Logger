#pragma once

#include "ILogOutput.hpp"
#include <string>

namespace Logging {

class LogOutputFile : public ILogOutput {
public:
    LogOutputFile(const std::string& filePath);

	void Write(const std::vector<LogEntry>& logEntries) override;
    void Write(const LogEntry& entry) override;

    //! Get the filepath as entered in the constructor.
    std::string FilePath() const;

private:
    std::string m_filePath;
};

}