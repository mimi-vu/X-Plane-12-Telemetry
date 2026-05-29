/**
 * @file    IFlightMetric.hpp
 * @brief   Pure-virtual base for every flight metric computation unit.
 *
 * Each metric (airspeed, altitude, G-force, etc.) is a self-contained object
 * that knows:
 *   1. Which XPlane DataRow indices it needs.
 *   2. How to compute a derived value from those rows.
 *   3. Whether it is currently in a warning or limit-exceeded state.
 *
 * The MetricsEngine calls update() on every registered IFlightMetric once per
 * DataPacket, then queries the results for the display bridge.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_IFLIGHT_METRIC_HPP
#define XPT_METRICS_IFLIGHT_METRIC_HPP

#include "telemetry/DataPacket.hpp"
#include "common/Types.hpp"
#include <string>

namespace xpt
{
namespace metrics
{

/**
 * @brief Validity and alerting state for a computed metric value.
 */
enum class MetricStatus : xpt::common::uint8
{
    VALID         = 0U, ///< Value is current and within normal envelope.
    WARNING       = 1U, ///< Value is approaching a limit.
    LIMIT_EXCEEDED = 2U, ///< Value has exceeded a structural/flight limit.
    INVALID       = 3U  ///< No valid data received yet (initialisation state).
};

/**
 * @class IFlightMetric
 * @brief Interface that every metric must implement.
 */
class IFlightMetric
{
public:
    virtual ~IFlightMetric() {}

    /**
     * @brief  Ingest a new DataPacket and recompute the metric's output value.
     * @param  packet  The latest parsed XPlane 12 DATA frame.
     *
     * Implementations should:
     *   1. Find the relevant DataRow(s) by index.
     *   2. Extract the float32 value(s).
     *   3. Apply any unit conversions.
     *   4. Run envelope checks and update m_status accordingly.
     */
    virtual void update(const xpt::telemetry::DataPacket& packet) = 0;

    /**
     * @brief  Human-readable name for this metric (e.g. "Airspeed_KIAS").
     */
    virtual std::string name() const = 0;

    /**
     * @brief  Current alerting / validity status.
     */
    virtual MetricStatus status() const = 0;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_IFLIGHT_METRIC_HPP
