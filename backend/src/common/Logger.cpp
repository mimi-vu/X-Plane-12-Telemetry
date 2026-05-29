/**
 * @file    Logger.cpp
 * @brief   Logger singleton — STUB.
 *
 * TODO: Decide on a logging sink strategy:
 *       - std::cerr for development
 *       - ring-buffer + file writer for DO-178C data-recording compliance
 *       - no-op in safety-critical release builds
 *
 * @author  XPT Flight Software Team
 */

#include "common/Logger.hpp"

namespace xpt
{
namespace common
{

Logger& Logger::instance()
{
    static Logger s_instance;
    return s_instance;
}

Logger::Logger()
    : m_minLevel(LogLevel::DEBUG)
{
    // TODO: initialise sink(s)
}

Logger::~Logger()
{
    // TODO: flush and close sink(s)
}

void Logger::log(LogLevel level, const std::string& subsystem, const std::string& message)
{
    (void)level;
    (void)subsystem;
    (void)message;
    // TODO: implement — filter by m_minLevel, format timestamp + level tag, write to sink
}

void Logger::setMinLevel(LogLevel level)
{
    (void)level;
    // TODO: implement — assign m_minLevel
}

LogLevel Logger::minLevel() const
{
    return m_minLevel;
}

} // namespace common
} // namespace xpt
