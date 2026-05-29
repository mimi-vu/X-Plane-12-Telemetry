/**
 * @file    MetricsEngine.hpp
 * @brief   Orchestrator: receives DataPackets, fans out to all metrics,
 *          assembles a FlightState snapshot for the display bridge.
 *
 * MetricsEngine implements IPacketHandler so it can be registered directly
 * with TelemetryReceiver.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_METRICS_METRICS_ENGINE_HPP
#define XPT_METRICS_METRICS_ENGINE_HPP

#include "IFlightMetric.hpp"
#include "telemetry/TelemetryReceiver.hpp"
#include "common/Types.hpp"
#include <vector>

namespace xpt
{
namespace metrics
{

/**
 * @struct FlightState
 * @brief  Snapshot of all computed metric values at a single point in time.
 *
 * Aircraft: Grumman F-14D Tomcat.
 * Populated by MetricsEngine after every update cycle and passed to the
 * display bridge. Add a field here for each metric you implement.
 *
 * TODO: add fields as you implement each metric class.
 */
struct FlightState
{
    xpt::common::TimestampMs timestampMs;

    // -- Airspeed --
    xpt::common::float32 indicatedAirspeedKts;   // TODO: populate in AirspeedMetric
    xpt::common::float32 trueAirspeedKts;
    xpt::common::float32 groundspeedKts;
    xpt::common::float32 machNumber;

    // -- Altitude --
    xpt::common::float32 altitudeMSLFt;          // TODO: populate in AltitudeMetric
    xpt::common::float32 altitudeAGLFt;
    xpt::common::float32 verticalSpeedFpm;

    // -- Attitude --
    xpt::common::float32 pitchDeg;               // TODO: populate in AttitudeMetric
    xpt::common::float32 rollDeg;
    xpt::common::float32 headingMagDeg;
    xpt::common::float32 headingTrueDeg;

    // -- G-Force --
    xpt::common::float32 gForceNormal;           // TODO: populate in GForceMetric
    xpt::common::float32 gForceLateral;
    xpt::common::float32 gForceAxial;

    // -- Fuel --
    xpt::common::float32 fuelTotalLbs;           // TODO: populate in FuelMetric
    xpt::common::float32 fuelFlowLbsPerHr;

    // -- Angle of Attack --
    xpt::common::float32 aoaDeg;                 // TODO: populate in AOAMetric

    // -- Engines (F110-GE-400, twin) --       TODO: populate in ThrottleMetric
    xpt::common::float32 throttleLeftPosition;
    xpt::common::float32 throttleRightPosition;
    xpt::common::float32 engineLeftN1Percent;
    xpt::common::float32 engineRightN1Percent;
    xpt::common::float32 engineLeftN2Percent;
    xpt::common::float32 engineRightN2Percent;
    xpt::common::float32 engineLeftEgtDegC;
    xpt::common::float32 engineRightEgtDegC;
    bool                 afterburnerLeft;
    bool                 afterburnerRight;

    // -- Variable-Geometry Swing Wing --      TODO: populate in SwingWingMetric
    xpt::common::float32 wingSweepAngleDeg;      // 20° = fwd, 68° = swept, 75° = oversweep
    bool                 wingSweepAutoMode;       // true = CADC auto-schedule active

    // -- Navigation --
    xpt::common::float32 latitudeDeg;            // TODO: populate in NavigationMetric
    xpt::common::float32 longitudeDeg;
};

/**
 * @class MetricsEngine
 * @brief Drives all IFlightMetric objects and owns the current FlightState.
 */
class MetricsEngine : public xpt::telemetry::IPacketHandler
{
public:
    MetricsEngine();
    virtual ~MetricsEngine();

    /**
     * @brief  Register a metric to be updated each cycle.
     *         The engine does NOT take ownership — caller manages lifetime.
     */
    void registerMetric(IFlightMetric* metric);

    /**
     * @brief  Returns the most recently computed FlightState snapshot.
     *
     * TODO: Decide on thread-safety strategy — the receiver thread writes
     *       FlightState while the display thread reads it.
     *       Options: double-buffer, mutex, lock-free ring.
     */
    const FlightState& currentState() const;

    // IPacketHandler
    virtual void onPacketReceived(const xpt::telemetry::DataPacket& packet) override;

private:
    MetricsEngine(const MetricsEngine&);
    MetricsEngine& operator=(const MetricsEngine&);

    std::vector<IFlightMetric*> m_metrics;
    FlightState                 m_state;
};

} // namespace metrics
} // namespace xpt

#endif // XPT_METRICS_METRICS_ENGINE_HPP
