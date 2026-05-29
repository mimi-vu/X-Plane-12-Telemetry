/**
 * @file    NavigationMetric.cpp
 * @brief   NavigationMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/NavigationMetric.hpp"

namespace xpt
{
namespace metrics
{

NavigationMetric::NavigationMetric()
    : m_latitudeDeg(0.0F)
    , m_longitudeDeg(0.0F)
    , m_groundTrackDeg(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void NavigationMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string NavigationMetric::name() const
{
    return "NavigationMetric"; // TODO: refine to match display label convention
}

MetricStatus NavigationMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
