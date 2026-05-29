/**
 * @file    AttitudeMetric.cpp
 * @brief   AttitudeMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/AttitudeMetric.hpp"

namespace xpt
{
namespace metrics
{

AttitudeMetric::AttitudeMetric()
    : m_pitchDeg(0.0F)
    , m_rollDeg(0.0F)
    , m_headingMagDeg(0.0F)
    , m_headingTrueDeg(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void AttitudeMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string AttitudeMetric::name() const
{
    return "AttitudeMetric"; // TODO: refine to match display label convention
}

MetricStatus AttitudeMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
