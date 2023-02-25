#include "LogOutputFile.hpp"

#include <fstream>

namespace Logging {

LogOutputFile::LogOutputFile(const std::string& filePath) : m_filePath(filePath)
{}

void LogOutputFile::Write(const std::vector<LogEntry>& logEntries) {
    std::unique_lock<std::mutex> lock(m_writeLock);

    std::ofstream outfile;
    outfile.open(m_filePath.c_str(), std::ios::out | std::ios::app);
    if (outfile.fail()) {
        //throw std::ios_base::failure(std::stderror(-1));
    }

    for (const auto& entry : logEntries) {
        outfile << entry.OutputText() << "\n";
    }
}

void LogOutputFile::Write(const LogEntry& entry) {
    std::unique_lock<std::mutex> lock(m_writeLock);
    
    std::ofstream outfile;
    outfile.open(m_filePath.c_str(), std::ios::out | std::ios::app);
    if (outfile.fail()) {
        // throw std::ios_base::failure(std::stderror(-1));
    }

    outfile << entry.OutputText() << "\n";
}

std::string LogOutputFile::FilePath() const {
    return m_filePath;
}

}