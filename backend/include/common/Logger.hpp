/**
 * @file    Logger.hpp
 * @brief   Minimal structured logger — thread-safe, level-filtered.
 *
 * Disabled entirely when XPT_LOGGING_ENABLED is not defined (release/DO-178).
 * JSF AV Rule 17: No I/O in safety-critical execution paths; logging is
 * conditionally compiled out.
 *
 * @author  XPT Flight Software Team
 * @version 0.1.0
 */

#ifndef XPT_COMMON_LOGGER_HPP
#define XPT_COMMON_LOGGER_HPP

#include "Types.hpp"
#include <string>

namespace xpt
{
namespace common
{

/**
 * @brief Log severity levels, ordered by increasing criticality.
 */
enum class LogLevel : uint8
{
    DEBUG   = 0U,
    INFO    = 1U,
    WARNING = 2U,
    ERROR   = 3U,
    FATAL   = 4U
};

/**
 * @class Logger
 * @brief Singleton structured logger with compile-time enable guard.
 *
 * Usage:
 *   Logger::instance().log(LogLevel::INFO, "Telemetry", "Receiver started");
 *
 * Or via the convenience macros defined below.
 */
class Logger
{
public:
    /** Returns the process-wide singleton instance. */
    static Logger& instance();

    /**
     * @brief  Emit a log record.
     * @param  level    Severity level.
     * @param  subsystem  Source subsystem tag (e.g. "Telemetry", "Metrics").
     * @param  message  Human-readable message string.
     */
    void log(LogLevel level, const std::string& subsystem, const std::string& message);

    /**
     * @brief  Set the minimum level that will be emitted.
     * @param  level  Anything below this level is silently discarded.
     */
    void setMinLevel(LogLevel level);

    /** Returns the currently active minimum log level. */
    LogLevel minLevel() const;

private:
    Logger();
    ~Logger();

    // Non-copyable, non-movable (JSF AV Rule 68)
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    LogLevel m_minLevel;
};

} // namespace common
} // namespace xpt

// ---------------------------------------------------------------------------
// Convenience macros — compile away when logging is disabled
// ---------------------------------------------------------------------------
#ifdef XPT_LOGGING_ENABLED
    #define XPT_LOG_DEBUG(sys, msg)   xpt::common::Logger::instance().log(xpt::common::LogLevel::DEBUG,   (sys), (msg))
    #define XPT_LOG_INFO(sys, msg)    xpt::common::Logger::instance().log(xpt::common::LogLevel::INFO,    (sys), (msg))
    #define XPT_LOG_WARNING(sys, msg) xpt::common::Logger::instance().log(xpt::common::LogLevel::WARNING, (sys), (msg))
    #define XPT_LOG_ERROR(sys, msg)   xpt::common::Logger::instance().log(xpt::common::LogLevel::ERROR,   (sys), (msg))
    #define XPT_LOG_FATAL(sys, msg)   xpt::common::Logger::instance().log(xpt::common::LogLevel::FATAL,   (sys), (msg))
#else
    #define XPT_LOG_DEBUG(sys, msg)   ((void)0)
    #define XPT_LOG_INFO(sys, msg)    ((void)0)
    #define XPT_LOG_WARNING(sys, msg) ((void)0)
    #define XPT_LOG_ERROR(sys, msg)   ((void)0)
    #define XPT_LOG_FATAL(sys, msg)   ((void)0)
#endif

#endif // XPT_COMMON_LOGGER_HPP
