#include <iostream>
#include "Logger.hpp"

Logging::Logger CreateLogger() {
	static Logging::LogConfig config;
	return Logging::Logger(config);
}

int main(){
	std::cout << "Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;

	{
		Logging::Logger logger = CreateLogger();
		logger << Logging::LogLevel::Info << "This" << " is" << " a" << " test.";
	}

	return 0;
}
