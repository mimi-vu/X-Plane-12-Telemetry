/**
 * @file    AirspeedMetric.hpp
 * @brief   Extracts and validates airspeed values from XPlane DATA index 3.
 *
 * XPlane DATA index 3 layout (slots 0–7):
 *   [0] Vind  — Indicated airspeed (KIAS)
 *   [1] Vind  — Equivalent airspeed (KEAS)
 *   [2] Vtrue — True airspeed (KTAS)
 *   [3] Vtrue — True airspeed (m/s)
 *   [4] Vgnd  — Ground speed (KIAS)
 *   [5] Vind  — mph indicated
 *   [6] Vtrue — mph true
 *   [7] -999  — unused
 *
 * TODO: Confirm slot layout against your XPlane 12 net_spec.cpp.
 * TODO: implement update() — extract values, compute Mach = KTAS / speed-of-sound,
 *       check against VMAX_KIAS and set status accordingly.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_AIRSPEED_METRIC_HPP
#define XPT_METRICS_AIRSPEED_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class AirspeedMetric : public IFlightMetric
{
public:
    AirspeedMetric();
    virtual ~AirspeedMetric() {}

    virtual void        update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 indicatedKts() const;
    xpt::common::float32 trueKts()      const;
    xpt::common::float32 groundKts()    const;
    xpt::common::float32 mach()         const;

private:
    xpt::common::float32 m_indicatedKts;
    xpt::common::float32 m_trueKts;
    xpt::common::float32 m_groundKts;
    xpt::common::float32 m_mach;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_AIRSPEED_METRIC_HPP
