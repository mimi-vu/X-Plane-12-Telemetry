/**
 * @file    FuelMetric.cpp
 * @brief   FuelMetric implementation -- STUB.
 *
 * TODO: implement update() -- see the matching header for field layout
 *       and the XPlane 12 DATA index to extract from the DataPacket.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/FuelMetric.hpp"

namespace xpt
{
namespace metrics
{

FuelMetric::FuelMetric()
    : m_totalFuelLbs(0.0F)
    , m_fuelFlowLbsPerHr(0.0F)
    , m_enduranceHours(0.0F)
    , m_status(MetricStatus::INVALID)
{
}

void FuelMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement
    //   1. Search packet.rows for the relevant index.
    //   2. Copy float32 values into member fields.
    //   3. Apply unit conversions.
    //   4. Compare against envelope limits -> update m_status.
}

std::string FuelMetric::name() const
{
    return "FuelMetric"; // TODO: refine to match display label convention
}

MetricStatus FuelMetric::status() const
{
    return m_status;
}

} // namespace metrics
} // namespace xpt
