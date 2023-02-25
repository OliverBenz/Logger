#pragma once

#include "ILogOutput.hpp"
#include <string>
#include <mutex>

namespace Logging {

class LogOutputFile : public ILogOutput {
public:
    LogOutputFile(const std::string& filePath);

	void Write(const std::vector<LogEntry>& logEntries) override;
    void Write(const LogEntry& entry) override;

    //! Get the filepath as entered in the constructor.
    std::string FilePath() const;

private:
    std::string m_filePath;  //!< Path to the log file.
    std::mutex m_writeLock;  //!< Lock so file is only opened on one thread.
};

}