#include <iostream>
#include "Logger.hpp"
#include "LogOutputConsole.hpp"

int main(){
	std::cout << "Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
	
	static Logging::LogConfig config;
	config.AddLogOutput(std::make_shared<Logging::LogOutputConsole>());

	{
		Logging::Logger logger = Logging::Logger(config);
		logger << Logging::LogLevel::Info << "This" << " is" << " a" << " test.";
		logger << Logging::LogLevel::Debug << "Debug" << " Entry";
		logger << Logging::LogLevel::Error << "Error text";
	}

	return 0;
}
