#include <iostream>
#include "Logger.hpp"
#include "LogLevel.hpp"
#include "LogOutputConsole.hpp"
#include "LogOutputMock.hpp"


// TODO: This main function can be a unit test
// TODO: Disable logging efficiently
// TODO: Log to file (LogOutputFile class (Thread safe))
// TODO: Handle TODOs in files
int main(){
	std::cout << "Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
	
	static Logging::LogConfig config;
	config.AddLogOutput(std::make_shared<Logging::LogOutputConsole>());

	auto mock = std::make_shared<Logging::LogOutputMock>();
	config.AddLogOutput(mock);

	{
		Logging::Logger logger = Logging::Logger(config);
		logger << Logging::LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << Logging::LogLevel::Debug << "Debug" << " Entry";
		logger << Logging::LogLevel::Error << "Error text";
	}

	std::cout << "\nMockData:\n";
	for (const auto& entry : mock->m_logEntries){
		std::cout << LevelToText(entry.m_level) + " " + entry.m_text + "\n";
	}

	return 0;
}
