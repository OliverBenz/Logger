#include "LogEntry.hpp"

namespace Logging {

std::string LogEntry::OutputText() const {
    return m_time + " " + LevelToText(m_level) + " " + m_text;  
}

}