/**
 * @file    AirspeedMetric.cpp
 * @brief   AirspeedMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/AirspeedMetric.hpp"

namespace xpt
{
namespace metrics
{

AirspeedMetric::AirspeedMetric()
    : m_indicatedKts(0.0F)
    , m_trueKts(0.0F)
    , m_groundKts(0.0F)
    , m_mach(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void AirspeedMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string AirspeedMetric::name() const
{
    return "AirspeedMetric"; // TODO: refine to match display label convention
}

MetricStatus AirspeedMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
