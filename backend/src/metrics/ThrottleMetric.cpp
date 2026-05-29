/**
 * @file    ThrottleMetric.cpp
 * @brief   F-14D twin-engine throttle metric — STUB.
 *
 * TODO (implementation tasks):
 *   1. In update(), find DataRow with index 25 (throttle positions).
 *        - Extract values[0] → m_throttleLeft
 *        - Extract values[1] → m_throttleRight
 *   2. Find DataRow with index 45 (N1 per engine).
 *        - Extract values[0] → m_n1Left, values[1] → m_n1Right
 *   3. Find DataRow with index 46 (N2 per engine).
 *        - Extract values[0] → m_n2Left, values[1] → m_n2Right
 *   4. Find DataRow with index 37 (EGT per engine).
 *        - Extract values[0] → m_egtLeft, values[1] → m_egtRight
 *   5. Afterburner detection:
 *        - m_afterburnerLeft  = (m_throttleLeft  > AFTERBURNER_THRESHOLD)
 *        - m_afterburnerRight = (m_throttleRight > AFTERBURNER_THRESHOLD)
 *        - TODO: define AFTERBURNER_THRESHOLD in Constants.hpp once confirmed.
 *   6. Asymmetry check:
 *        - If |m_throttleLeft - m_throttleRight| > some tolerance, set WARNING.
 *        - Asymmetric thrust at low speed is a significant handling hazard.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/ThrottleMetric.hpp"

namespace xpt
{
namespace metrics
{

ThrottleMetric::ThrottleMetric()
    : m_throttleLeft(0.0F)
    , m_n1Left(0.0F)
    , m_n2Left(0.0F)
    , m_egtLeft(0.0F)
    , m_afterburnerLeft(false)
    , m_throttleRight(0.0F)
    , m_n1Right(0.0F)
    , m_n2Right(0.0F)
    , m_egtRight(0.0F)
    , m_afterburnerRight(false)
    , m_status(MetricStatus::INVALID)
{
}

void ThrottleMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement — see file header
}

std::string ThrottleMetric::name() const
{
    return "Engine_F110_Twin";
}

MetricStatus ThrottleMetric::status() const
{
    return m_status;
}

xpt::common::float32 ThrottleMetric::throttleLeftPosition()  const { return m_throttleLeft; }
xpt::common::float32 ThrottleMetric::n1LeftPercent()         const { return m_n1Left; }
xpt::common::float32 ThrottleMetric::n2LeftPercent()         const { return m_n2Left; }
xpt::common::float32 ThrottleMetric::egtLeftDegC()           const { return m_egtLeft; }
bool                 ThrottleMetric::isAfterburnerLeft()      const { return m_afterburnerLeft; }

xpt::common::float32 ThrottleMetric::throttleRightPosition() const { return m_throttleRight; }
xpt::common::float32 ThrottleMetric::n1RightPercent()        const { return m_n1Right; }
xpt::common::float32 ThrottleMetric::n2RightPercent()        const { return m_n2Right; }
xpt::common::float32 ThrottleMetric::egtRightDegC()          const { return m_egtRight; }
bool                 ThrottleMetric::isAfterburnerRight()     const { return m_afterburnerRight; }

} // namespace metrics
} // namespace xpt
