#include "LogModule.hpp"

#include "LogConfig.hpp"
#include "LogOutputFile.hpp"
#include "LogOutputConsole.hpp"

Logging::LogConfig config;

//! Enable logging of any entries to an output file + console(for debug builds).
static void InitializeLogger() {
    config.SetLogEnabled(true);
    config.SetMinLogLevel(Logging::LogLevel::Any);

	auto logFile = std::make_shared<Logging::LogOutputFile>("Logfile.txt");
    config.AddLogOutput(logFile);

#ifdef _DEBUG
    config.AddLogOutput(std::make_shared<Logging::LogOutputConsole>());
#endif
}

Logging::Logger Logger() {
    static bool initialized = false;
    if (!initialized) {
        InitializeLogger();
        initialized = true;
    }

    return Logging::Logger(config);
}
