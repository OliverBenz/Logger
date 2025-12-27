#include "Logger/LogOutputFile.hpp"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <system_error>

#ifdef _WIN32
#include <shlobj.h>
#include <windows.h>
#endif

namespace Logging {

LogOutputFile::LogOutputFile(const std::string& filePath, std::size_t maxFileSize)
    : m_filePath(filePath), m_maxFileSize(maxFileSize) {
}

void LogOutputFile::RotateFile() {
	const std::filesystem::path originalPath(m_filePath);
	const auto parent    = originalPath.parent_path();
	const auto stem      = originalPath.stem().string();
	const auto extension = originalPath.extension().string();

	const auto baseName = extension.empty() ? originalPath.filename().string() : stem;

	std::error_code ec;
	constexpr unsigned kMaxRotations = 10000;
	unsigned count                   = 1u;
	std::filesystem::path newFilePath;
	do {
		if (count > kMaxRotations) {
			return;
		}

		auto rotatedName = baseName + "(" + std::to_string(count) + ")" + extension;
		newFilePath      = parent.empty() ? std::filesystem::path(rotatedName) : parent / rotatedName;
		++count;
	} while (std::filesystem::exists(newFilePath, ec));
	ec.clear(); // // Any errors during probing are ignored by design

	std::filesystem::rename(originalPath, newFilePath, ec);
	if (ec == std::errc::cross_device_link) {
		// Best-effort fallback
		std::filesystem::copy_file(originalPath, newFilePath, std::filesystem::copy_options::overwrite_existing, ec);

		if (!ec) {
			std::filesystem::remove(originalPath, ec);
		}
	}

	// Any failure beyond this point is intentionally ignored.
}

void LogOutputFile::Write(const std::vector<LogEntry>& logEntries) {
	std::unique_lock<std::mutex> lock(m_writeLock);

	std::ofstream outfile(m_filePath, std::ios::out | std::ios::app);
	if (!outfile.is_open()) {
		return;
	}

	for (const auto& entry: logEntries) {
		outfile << entry.OutputText() << "\n";
	}
	outfile.close();

	// Check max file size reached
	std::error_code ec;
	const auto fileSize = std::filesystem::file_size(m_filePath, ec);
	if (!ec && fileSize >= m_maxFileSize) {
		RotateFile();
	}
}

void LogOutputFile::Write(const LogEntry& entry) {
	std::unique_lock<std::mutex> lock(m_writeLock);

	std::ofstream outfile(m_filePath, std::ios::out | std::ios::app);
	if (!outfile.is_open()) {
		return;
	}

	outfile << entry.OutputText() << "\n";
	outfile.close();

	// Check max filesize reached
	std::error_code ec;
	const auto fileSize = std::filesystem::file_size(m_filePath, ec);
	if (!ec && fileSize >= m_maxFileSize) {
		RotateFile();
	}
}

std::string LogOutputFile::FilePath() const {
	return m_filePath;
}

std::filesystem::path GetDefaultLogDir(const std::string& appName) {
#if defined(_WIN32)
	// 1) Windows: %LOCALAPPDATA%/<AppName>/logs
	PWSTR path = nullptr;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path))) {
		std::filesystem::path p(path);
		CoTaskMemFree(path);
		return p / appName / "logs";
	}
#elif defined(__APPLE__)
	// 2) macOS: ~/Library/Logs/<AppName>
	const char* home = std::getenv("HOME");
	if (home && std::strlen(home) > 0) {
		return std::filesystem::path(home) / "Library/Logs" / appName;
	}
#else
	// 3) Linux/Unix: XDG_STATE_HOME/<AppName>/logs or ~/.local/state/<AppName>/logs
	const char* state = std::getenv("XDG_STATE_HOME");
	if (state && std::strlen(state) > 0) {
		return std::filesystem::path(state) / appName / "logs";
	}
	const char* home = std::getenv("HOME");
	if (home && std::strlen(home) > 0) {
		return std::filesystem::path(home) / ".local/state" / appName / "logs";
	}
#endif

	// 4) Fallback
	return std::filesystem::current_path() / "logs";
}

} // namespace Logging
