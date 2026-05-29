/**
 * @file    AttitudeMetric.hpp
 * @brief   Pitch, roll, and heading from XPlane DATA index 17.
 *
 * XPlane DATA index 17 layout:
 *   [0] Pitch  (degrees, nose-up positive)
 *   [1] Roll   (degrees, right-wing-down positive)
 *   [2] True heading (degrees)
 *   [3] Magnetic heading (degrees)
 *
 * TODO: implement update(), add bank angle warning threshold,
 *       consider coordinate frame conventions (NED vs body frame).
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_ATTITUDE_METRIC_HPP
#define XPT_METRICS_ATTITUDE_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class AttitudeMetric : public IFlightMetric
{
public:
    AttitudeMetric();
    virtual ~AttitudeMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 pitchDeg()       const;
    xpt::common::float32 rollDeg()        const;
    xpt::common::float32 headingMagDeg()  const;
    xpt::common::float32 headingTrueDeg() const;

private:
    xpt::common::float32 m_pitchDeg;
    xpt::common::float32 m_rollDeg;
    xpt::common::float32 m_headingMagDeg;
    xpt::common::float32 m_headingTrueDeg;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_ATTITUDE_METRIC_HPP
