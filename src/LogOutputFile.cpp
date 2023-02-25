#include "LogOutputFile.hpp"

#include <fstream>

namespace Logging {

LogOutputFile::LogOutputFile(const std::string& fileName) : m_fileName(fileName)
{}

void LogOutputFile::Write(const std::vector<LogEntry>& logEntries) {
    std::ofstream outfile;
    outfile.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    if (outfile.fail()) {
        //throw std::ios_base::failure(std::stderror(-1));
    }

    for (const auto& entry : logEntries) {
        outfile << entry.OutputText() << "\n";
    }
}

void LogOutputFile::Write(const LogEntry& entry) {
    std::ofstream outfile;
    outfile.open(m_fileName.c_str(), std::ios::out | std::ios::app);
    if (outfile.fail()) {
        // throw std::ios_base::failure(std::stderror(-1));
    }

    outfile << entry.OutputText() << "\n";
}

}