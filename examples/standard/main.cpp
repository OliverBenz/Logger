#include <iostream>
#include "Logger.hpp"
#include "LogLevel.hpp"
#include "LogOutputConsole.hpp"
#include "LogOutputMock.hpp"
#include "LogOutputFile.hpp"

int main(){
	std::cout << "Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
	
	static Logging::LogConfig config;
	auto mock = std::make_shared<Logging::LogOutputMock>();
	auto logFile = std::make_shared<Logging::LogOutputFile>("Filename.txt");

	config.AddLogOutput(std::make_shared<Logging::LogOutputConsole>());
	config.AddLogOutput(mock);
	config.AddLogOutput(logFile);

	{
		Logging::Logger logger = Logging::Logger(config);
		logger << Logging::LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << Logging::LogLevel::Debug << "Debug" << " Entry";
		logger << Logging::LogLevel::Error << "Error text";
	}

	std::cout << "\nMockData:\n";
	for (const auto& entry : mock->m_logEntries){
		std::cout << LevelToText(entry.GetLevel()) + " " + entry.GetText() + "\n";
	}

	// Cleanup log file
	std::remove(logFile->FilePath().c_str());

	return 0;
}
