/**
 * @file    MetricsEngine.cpp
 * @brief   MetricsEngine implementation — STUB.
 *
 * TODO (implementation tasks):
 *   1. onPacketReceived() — iterate m_metrics, call metric->update(packet),
 *      then harvest each metric's values into m_state fields.
 *   2. currentState()    — decide on thread-safety (see header note).
 *   3. Consider adding a timestamp to m_state so the display bridge can
 *      detect stale data if packets stop arriving.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/MetricsEngine.hpp"
#include "common/Logger.hpp"

namespace xpt
{
namespace metrics
{

MetricsEngine::MetricsEngine()
{
    // TODO: zero-initialise m_state
}

MetricsEngine::~MetricsEngine()
{
    // m_metrics are not owned — do not delete
}

void MetricsEngine::registerMetric(IFlightMetric* metric)
{
    (void)metric;
    // TODO: push_back into m_metrics (add null check first)
}

const FlightState& MetricsEngine::currentState() const
{
    return m_state;
}

void MetricsEngine::onPacketReceived(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement fan-out
    //   for each metric in m_metrics: metric->update(packet);
    //   then populate m_state from each metric's accessors
}

} // namespace metrics
} // namespace xpt
