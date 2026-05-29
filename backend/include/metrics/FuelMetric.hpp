/**
 * @file    FuelMetric.hpp
 * @brief   Total fuel quantity and fuel flow from XPlane DATA indices 96/97.
 *
 * XPlane DATA index 96 — fuel quantities (lbs) per tank.
 * XPlane DATA index 97 — total fuel (lbs) and fuel flow (lbs/hr) per engine.
 *
 * TODO: implement update(), sum per-tank quantities for total fuel,
 *       compute fuel endurance = totalFuelLbs / fuelFlowLbsPerHr (hours).
 *       Add a LOW_FUEL warning threshold.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_FUEL_METRIC_HPP
#define XPT_METRICS_FUEL_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class FuelMetric : public IFlightMetric
{
public:
    FuelMetric();
    virtual ~FuelMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 totalFuelLbs()      const;
    xpt::common::float32 fuelFlowLbsPerHr()  const;
    xpt::common::float32 enduranceHours()    const;

private:
    xpt::common::float32 m_totalFuelLbs;
    xpt::common::float32 m_fuelFlowLbsPerHr;
    xpt::common::float32 m_enduranceHours;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_FUEL_METRIC_HPP
