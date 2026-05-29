/**
 * @file    GForceMetric.cpp
 * @brief   GForceMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/GForceMetric.hpp"

namespace xpt
{
namespace metrics
{

GForceMetric::GForceMetric()
    : m_normalG(0.0F)
    , m_lateralG(0.0F)
    , m_axialG(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void GForceMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string GForceMetric::name() const
{
    return "GForceMetric"; // TODO: refine to match display label convention
}

MetricStatus GForceMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
