#pragma once

#include "ILogOutput.hpp"
#include <string>
#include <mutex>

namespace Logging {

class LogOutputFile : public ILogOutput {
public:
    //! The current log file is always the one mentioned in 'filePath'.
    /*!
     * \param[in] filePath Path to the log file.
     * \param[in] maxFileSize Maximum file size in bytes before starting a new file (4MB default).
     */
    LogOutputFile(const std::string& filePath, std::uintmax_t maxFileSize = 4 * 1024 * 1024);

    //! Write set of log entries to the logfile.
	void Write(const std::vector<LogEntry>& logEntries) override;
    
    //! Write single log entry to the logfile.
    void Write(const LogEntry& entry) override;

    //! Get the filepath as entered in the constructor.
    std::string FilePath() const;

private:
    //! Rename the current log file and create a new one.
    void RotateFile();

private:
    std::string m_filePath;       //!< Path to the log file.
    std::uintmax_t m_maxFileSize; //!< Maximum size of a logfile before starting a new file.
    std::mutex m_writeLock;       //!< Lock so file is only opened on one thread.
};

}