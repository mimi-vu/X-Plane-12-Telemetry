/**
 * @file    AOAMetric.cpp
 * @brief   AOAMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/AOAMetric.hpp"

namespace xpt
{
namespace metrics
{

AOAMetric::AOAMetric()
    : m_alphaDeg(0.0F)
    , m_betaDeg(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void AOAMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string AOAMetric::name() const
{
    return "AOAMetric"; // TODO: refine to match display label convention
}

MetricStatus AOAMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
