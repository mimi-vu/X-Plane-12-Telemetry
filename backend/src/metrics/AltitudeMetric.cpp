/**
 * @file    AltitudeMetric.cpp
 * @brief   AltitudeMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/AltitudeMetric.hpp"

namespace xpt
{
namespace metrics
{

AltitudeMetric::AltitudeMetric()
    : m_altMSLFt(0.0F)
    , m_altAGLFt(0.0F)
    , m_vertSpeedFpm(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void AltitudeMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string AltitudeMetric::name() const
{
    return "AltitudeMetric"; // TODO: refine to match display label convention
}

MetricStatus AltitudeMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
