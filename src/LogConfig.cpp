#include "LogConfig.hpp"

namespace Logging {

void LogConfig::AddLogOutput(std::shared_ptr<ILogOutput> output) {
    m_logOutputs.emplace_back(output);
}

}