#include "LogConfig.hpp"

namespace Logging {

void LogConfig::AddLogOutput(ILogOutput output) {
    m_logOutputs.emplace_back(output);
}

}