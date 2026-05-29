/**
 * @file    SwingWingMetric.hpp
 * @brief   F-14 Tomcat variable-geometry wing sweep state and safety monitoring.
 *
 * The F-14's defining feature is its variable-geometry (swing) wing, controlled
 * by the Central Air Data Computer (CADC). Wing sweep directly affects:
 *   - Stall speed (forward = lower stall speed, safer at low speed)
 *   - Maximum G available (swept = higher, but higher structural loads)
 *   - Drag (swept = lower drag at high Mach)
 *
 * Sweep range:
 *   20°  — fully forward (carrier approach, low-speed flight)
 *   68°  — fully swept   (high-speed dash, Mach 2+)
 *   75°  — oversweep     (carrier deck stow only, not for flight)
 *
 * Modes:
 *   AUTO   — CADC schedules sweep automatically based on Mach and altitude.
 *            This is the normal mode. The pilot should not normally override it.
 *   MANUAL — Pilot commands a specific angle via the wing sweep handle.
 *            Used if CADC fails or for special manoeuvres.
 *   EMER   — Emergency symmetry mode; both wings driven to a safe angle
 *            if asymmetric sweep is detected.
 *
 * XPlane DATA source:
 *   TODO: find the correct DATA index or DREF for wing sweep angle in the
 *         XPlane 12 F-14 model. Check sim/aircraft/parts/acf_sweep or
 *         the Heatblur F-14 custom DREF list if using their model.
 *
 * TODO: implement update(), monitor for asymmetric sweep (left != right),
 *       warn if oversweep is commanded in flight.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_SWING_WING_METRIC_HPP
#define XPT_METRICS_SWING_WING_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

/**
 * @brief F-14 wing sweep control mode.
 */
enum class WingSweepMode : xpt::common::uint8
{
    AUTO   = 0U, ///< CADC automatic scheduling.
    MANUAL = 1U, ///< Pilot-commanded position.
    EMER   = 2U  ///< Emergency symmetry mode.
};

class SwingWingMetric : public IFlightMetric
{
public:
    SwingWingMetric();
    virtual ~SwingWingMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    /** Current wing sweep angle in degrees (20°–75°). */
    xpt::common::float32 sweepAngleDeg()     const;

    /** Current sweep control mode (AUTO / MANUAL / EMER). */
    WingSweepMode        sweepMode()          const;

    /**
     * @brief  True if left and right wing sweep angles differ by more than
     *         a tolerance threshold — indicates a potential asymmetry fault.
     *
     * TODO: define the asymmetry tolerance in Constants.hpp.
     *       An asymmetric sweep in flight will cause severe roll moment.
     */
    bool                 isAsymmetric()       const;

    /** True when wing is in the carrier-deck oversweep position (75°). */
    bool                 isOversweep()        const;

private:
    xpt::common::float32 m_sweepAngleDeg;
    WingSweepMode        m_sweepMode;
    bool                 m_asymmetric;
    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_SWING_WING_METRIC_HPP
