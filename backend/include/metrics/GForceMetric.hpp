/**
 * @file    GForceMetric.hpp
 * @brief   Normal, lateral, and axial G-force from XPlane DATA index 4.
 *
 * XPlane DATA index 4 layout:
 *   [0] G-force, normal (z-axis, pilot seat direction)
 *   [1] G-force, axial  (x-axis, thrust axis)
 *   [2] G-force, side   (y-axis, lateral)
 *
 * TODO: implement update(), apply G_LIMIT_POSITIVE / G_LIMIT_NEGATIVE
 *       thresholds (from Constants.hpp) to set WARNING / LIMIT_EXCEEDED status.
 *       Consider a G-onset rate computation (ΔG/Δt) for fatigue monitoring.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_GFORCE_METRIC_HPP
#define XPT_METRICS_GFORCE_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class GForceMetric : public IFlightMetric
{
public:
    GForceMetric();
    virtual ~GForceMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 normalG()  const;
    xpt::common::float32 lateralG() const;
    xpt::common::float32 axialG()   const;

private:
    xpt::common::float32 m_normalG;
    xpt::common::float32 m_lateralG;
    xpt::common::float32 m_axialG;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_GFORCE_METRIC_HPP
