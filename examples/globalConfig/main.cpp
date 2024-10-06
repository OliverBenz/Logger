#include "LogModule.hpp"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define VERSION_STRING "Version: " STR(LOGVERSION_MAJOR) "." STR(LOGVERSION_MINOR) "." STR(LOGVERSION_PATCH) 

//! Example for logging.
class Calculator {
public:
    Calculator(const int a, const int b) : m_a(a), m_b(b) {
        Logger().Log(Logging::LogLevel::Debug, "Calculator constructor called.");
    }

    int Add() const {
        Logger().Log(Logging::LogLevel::Debug, "Add function called.");
        return m_a + m_b;
    }

private:
    int m_a;
    int m_b;
};

int main() {
    auto logger = Logger();
    logger.Log(Logging::LogLevel::Info, "Starting application.");
    logger.Log(Logging::LogLevel::Info, VERSION_STRING);
    logger.Log(Logging::LogLevel::Info, "Author:  Oliver Benz");
    logger.Flush();

    Calculator calc(9, 10);
    calc.Add();
}