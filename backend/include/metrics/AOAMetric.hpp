/**
 * @file    AOAMetric.hpp
 * @brief   Angle of attack (AOA) from XPlane DATA index 18.
 *
 * XPlane DATA index 18 layout:
 *   [0] Alpha — angle of attack (degrees)
 *   [1] Beta  — sideslip angle (degrees)
 *
 * TODO: implement update(), apply AOA_WARNING_DEG threshold.
 *       AOA is critical for departure prevention on the F-16 — a wrong reading
 *       can trigger (or mask) a departure from controlled flight.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_AOA_METRIC_HPP
#define XPT_METRICS_AOA_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class AOAMetric : public IFlightMetric
{
public:
    AOAMetric();
    virtual ~AOAMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 alphaDeg() const;
    xpt::common::float32 betaDeg()  const;

private:
    xpt::common::float32 m_alphaDeg;
    xpt::common::float32 m_betaDeg;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_AOA_METRIC_HPP
