/**
 * @file    AltitudeMetric.hpp
 * @brief   Altitude MSL, AGL, and vertical speed from XPlane DATA index 20.
 *
 * XPlane DATA index 20 layout:
 *   [0] Altitude MSL (feet)
 *   [1] Altitude AGL (feet)
 *   [2] Radar altitude (feet)  — may differ from AGL in mountainous terrain
 *   [3] Indicated altitude (with baro correction)
 *   [4..7] — see net_spec.cpp for details
 *
 * XPlane DATA index 21 contains vertical speed (fpm).
 *
 * TODO: Confirm indices, implement update(), add altitude alert thresholds
 *       (e.g. ground proximity warning system — GPWS logic stub).
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_ALTITUDE_METRIC_HPP
#define XPT_METRICS_ALTITUDE_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class AltitudeMetric : public IFlightMetric
{
public:
    AltitudeMetric();
    virtual ~AltitudeMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 altitudeMSLFt()  const;
    xpt::common::float32 altitudeAGLFt()  const;
    xpt::common::float32 vertSpeedFpm()   const;

private:
    xpt::common::float32 m_altMSLFt;
    xpt::common::float32 m_altAGLFt;
    xpt::common::float32 m_vertSpeedFpm;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_ALTITUDE_METRIC_HPP
