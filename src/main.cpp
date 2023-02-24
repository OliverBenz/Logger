#include <iostream>
#include "Logger.hpp"

int main(){
	std::cout << "Version: " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;

	{
		Logger logger;
		logger << LogLevel::Info << "This" << " is" << " a" << " test.";
	}

	return 0;
}
