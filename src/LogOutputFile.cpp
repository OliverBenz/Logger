#include "LogOutputFile.hpp"

#include <filesystem>
#include <fstream>
#include <system_error>

namespace Logging {

LogOutputFile::LogOutputFile(const std::string& filePath, std::size_t maxFileSize)
    : m_filePath(filePath), m_maxFileSize(maxFileSize) {
}

void LogOutputFile::RotateFile() {
	const std::filesystem::path originalPath(m_filePath);
	const auto parent = originalPath.parent_path();
	const auto stem = originalPath.stem().string();
	const auto extension = originalPath.extension().string();

	const auto baseName = extension.empty() ? originalPath.filename().string() : stem;

	unsigned count = 1;
	std::filesystem::path newFilePath;
	do {
		auto rotatedName = baseName + "(" + std::to_string(count) + ")" + extension;
		newFilePath = parent.empty() ? std::filesystem::path(rotatedName) : parent / rotatedName;
		++count;
	} while (std::filesystem::exists(newFilePath));

	std::error_code ec;
	std::filesystem::rename(originalPath, newFilePath, ec);
	if (ec) {
		throw std::filesystem::filesystem_error("Failed to rotate log file", originalPath, newFilePath, ec);
	}
}

void LogOutputFile::Write(const std::vector<LogEntry>& logEntries) {
	std::unique_lock<std::mutex> lock(m_writeLock);

	std::ofstream outfile(m_filePath, std::ios::out | std::ios::app);
	outfile.exceptions(std::ios::failbit | std::ios::badbit);

	for (const auto& entry: logEntries) {
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

	std::ofstream outfile(m_filePath, std::ios::out | std::ios::app);
	outfile.exceptions(std::ios::failbit | std::ios::badbit);

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

}  // namespace Logging
