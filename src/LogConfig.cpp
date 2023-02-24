#include "LogConfig.hpp"

namespace Logging {

void LogConfig::AddLogOutput(std::shared_ptr<ILogOutput> output) {
    m_logOutputs.emplace_back(std::move(output));
}

const std::vector<std::shared_ptr<ILogOutput>>& LogConfig::LogOutputs() {
    return m_logOutputs;
}

bool LogConfig::LoggingEnabled() const {
    return m_logEnabled;
}
	

}