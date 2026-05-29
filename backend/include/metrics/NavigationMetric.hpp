/**
 * @file    NavigationMetric.hpp
 * @brief   Geographic position and course from XPlane DATA index 20/14.
 *
 * XPlane DATA index 20:
 *   [0] Latitude  (degrees)
 *   [1] Longitude (degrees)
 *   [2] Altitude  (feet) — duplicate of AltitudeMetric; choose one source.
 *
 * XPlane DATA index 14:
 *   [0] Ground track (degrees true)
 *   [1] Drift angle  (degrees)
 *
 * TODO: implement update(), add dead-reckoning helper stubs,
 *       consider how to feed lat/lon into a moving-map display.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_NAVIGATION_METRIC_HPP
#define XPT_METRICS_NAVIGATION_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class NavigationMetric : public IFlightMetric
{
public:
    NavigationMetric();
    virtual ~NavigationMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    xpt::common::float32 latitudeDeg()     const;
    xpt::common::float32 longitudeDeg()    const;
    xpt::common::float32 groundTrackDeg()  const;

private:
    xpt::common::float32 m_latitudeDeg;
    xpt::common::float32 m_longitudeDeg;
    xpt::common::float32 m_groundTrackDeg;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_NAVIGATION_METRIC_HPP
