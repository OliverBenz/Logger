#include "LogOutputFile.hpp"

#include <fstream>
#include <filesystem>

namespace Logging {

LogOutputFile::LogOutputFile(const std::string& filePath, std::size_t maxFileSize)
    : m_filePath(filePath), m_maxFileSize(maxFileSize)
{}

void LogOutputFile::RotateFile() {
    // TODO: Test this function
    std::size_t pos = m_filePath.rfind('.');
    const std::string path = m_filePath.substr(0, pos);
    const std::string ext = m_filePath.substr(pos+1);

    // New filename of logFile has postfix [number].
    unsigned count = 0;
    std::string newFilePath;
    do {
        newFilePath = path + "[" + std::to_string(count) + "]." + ext;
        ++count;
    } while(std::filesystem::exists(newFilePath));

    // The current file is renamed with the postfix.
    if (!std::rename(m_filePath.c_str(), newFilePath.c_str()) == 0) {
        // throw std::ios_base::failure(std::stderror(-1));
    }
}

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

    // Check max filesize reached
    const auto fileSize = outfile.tellp();
    outfile.close();
    if (fileSize != std::ofstream::pos_type(-1) && static_cast<std::uintmax_t>(fileSize) >= m_maxFileSize) {
        RotateFile();
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

    // Check max filesize reached
    const auto fileSize = outfile.tellp();
    outfile.close();
    if (fileSize != std::ofstream::pos_type(-1) && static_cast<std::uintmax_t>(fileSize) >= m_maxFileSize) {
        RotateFile();
    }
}

std::string LogOutputFile::FilePath() const {
    return m_filePath;
}

}