/**
 * @file    SwingWingMetric.cpp
 * @brief   F-14 variable-geometry wing sweep metric — STUB.
 *
 * TODO (implementation tasks):
 *   1. Find the correct DataRow index for wing sweep angle.
 *        - Try standard DREF: sim/aircraft/parts/acf_sweep_hi / acf_sweep_lo
 *        - Or check the Heatblur F-14 DREF list for a custom path.
 *   2. In update():
 *        - Extract left wing sweep angle and right wing sweep angle separately
 *          if the model exposes them independently (asymmetry detection).
 *        - If only a single combined angle is available, use that and note
 *          the limitation.
 *        - Determine sweep mode from a separate mode DREF or throttle/switch state.
 *   3. Asymmetry check:
 *        - If |leftSweep - rightSweep| > tolerance → m_asymmetric = true,
 *          m_status = WARNING (asymmetric sweep is a serious flight safety event).
 *   4. Oversweep check:
 *        - If sweepAngle >= WING_SWEEP_OVERSWEEP_DEG → m_status = WARNING
 *          (oversweep is only safe with weight-on-wheels on carrier deck).
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/SwingWingMetric.hpp"
#include "common/Constants.hpp"

namespace xpt
{
namespace metrics
{

SwingWingMetric::SwingWingMetric()
    : m_sweepAngleDeg(xpt::common::constants::WING_SWEEP_MIN_DEG)
    , m_sweepMode(WingSweepMode::AUTO)
    , m_asymmetric(false)
    , m_status(MetricStatus::INVALID)
{
}

void SwingWingMetric::update(const xpt::telemetry::DataPacket& packet)
{
    (void)packet;
    // TODO: implement — see file header
}

std::string SwingWingMetric::name() const
{
    return "SwingWing_F14";
}

MetricStatus SwingWingMetric::status() const
{
    return m_status;
}

xpt::common::float32 SwingWingMetric::sweepAngleDeg() const
{
    return m_sweepAngleDeg;
}

WingSweepMode SwingWingMetric::sweepMode() const
{
    return m_sweepMode;
}

bool SwingWingMetric::isAsymmetric() const
{
    return m_asymmetric;
}

bool SwingWingMetric::isOversweep() const
{
    return m_sweepAngleDeg >= xpt::common::constants::WING_SWEEP_OVERSWEEP_DEG;
}

} // namespace metrics
} // namespace xpt
