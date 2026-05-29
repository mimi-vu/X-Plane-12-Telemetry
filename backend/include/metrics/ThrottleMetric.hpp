/**
 * @file    ThrottleMetric.hpp
 * @brief   Throttle and engine state for the F-14D Tomcat (twin F110-GE-400).
 *
 * The F-14D has two independent engines. Each throttle lever, N1, N2, EGT,
 * and afterburner state must be tracked separately — a single-engine failure
 * or asymmetric afterburner lighting is a significant event.
 *
 * Engine slot mapping (XPlane convention — 0-indexed):
 *   [0] — Left engine  (port)
 *   [1] — Right engine (starboard)
 *
 * XPlane DATA index 25:
 *   [0] left throttle position  (0.0 = idle, 1.0 = full afterburner)
 *   [1] right throttle position
 *
 * XPlane DATA index 45 — N1 fan speed (%) per engine
 * XPlane DATA index 46 — N2 core speed (%) per engine
 * XPlane DATA index 37 — EGT (exhaust gas temperature °C) per engine
 *
 * Afterburner detection:
 *   TODO: determine the throttle position threshold in XPlane 12's F-14 model
 *         that corresponds to afterburner engagement on the F110-GE-400.
 *         Typically above ~0.90–0.95 throttle position.
 *
 * TODO: implement update() — extract both engine slots, detect afterburner
 *       per engine, flag WARNING if engines are significantly asymmetric.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_THROTTLE_METRIC_HPP
#define XPT_METRICS_THROTTLE_METRIC_HPP

#include "IFlightMetric.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace metrics
{

class ThrottleMetric : public IFlightMetric
{
public:
    ThrottleMetric();
    virtual ~ThrottleMetric() {}

    virtual void         update(const xpt::telemetry::DataPacket& packet) override;
    virtual std::string  name()   const override;
    virtual MetricStatus status() const override;

    // -- Left engine (port) --
    xpt::common::float32 throttleLeftPosition()  const;
    xpt::common::float32 n1LeftPercent()         const;
    xpt::common::float32 n2LeftPercent()         const;
    xpt::common::float32 egtLeftDegC()           const;
    bool                 isAfterburnerLeft()      const;

    // -- Right engine (starboard) --
    xpt::common::float32 throttleRightPosition() const;
    xpt::common::float32 n1RightPercent()        const;
    xpt::common::float32 n2RightPercent()        const;
    xpt::common::float32 egtRightDegC()          const;
    bool                 isAfterburnerRight()     const;

private:
    // Left engine
    xpt::common::float32 m_throttleLeft;
    xpt::common::float32 m_n1Left;
    xpt::common::float32 m_n2Left;
    xpt::common::float32 m_egtLeft;
    bool                 m_afterburnerLeft;

    // Right engine
    xpt::common::float32 m_throttleRight;
    xpt::common::float32 m_n1Right;
    xpt::common::float32 m_n2Right;
    xpt::common::float32 m_egtRight;
    bool                 m_afterburnerRight;

    MetricStatus         m_status;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_THROTTLE_METRIC_HPP
