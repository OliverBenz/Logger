#include <iostream>
#include "Logger.hpp"

Logger CreateLogger() {
	static LogConfig config;
	return Logger(config);
}

int main(){
	std::cout << "Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;

	{
		Logger logger = CreateLogger();
		logger << LogLevel::Info << "This" << " is" << " a" << " test.";
	}

	return 0;
}
