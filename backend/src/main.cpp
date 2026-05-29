/**
 * @file    main.cpp
 * @brief   XPlane 12 Telemetry Backend — entry point.
 *
 * Wires together the four layers:
 *   TelemetryReceiver  →  MetricsEngine  →  DisplayBridge  →  IDisplayAdapter
 *
 * TODO (startup sequence):
 *   1. Parse command-line args (port, log level, display adapter type).
 *   2. Construct all components.
 *   3. Register metrics with the engine.
 *   4. Configure and start the display bridge.
 *   5. Start the telemetry receiver (blocks on its thread).
 *   6. Wait for a shutdown signal (Ctrl-C / SIGTERM).
 *   7. Stop receiver, stop bridge, clean up.
 *
 * @author  XPT Flight Software Team
 */

#include "telemetry/TelemetryReceiver.hpp"
#include "metrics/MetricsEngine.hpp"
#include "metrics/AirspeedMetric.hpp"
#include "metrics/AltitudeMetric.hpp"
#include "metrics/AttitudeMetric.hpp"
#include "metrics/GForceMetric.hpp"
#include "metrics/FuelMetric.hpp"
#include "metrics/AOAMetric.hpp"
#include "metrics/ThrottleMetric.hpp"
#include "metrics/NavigationMetric.hpp"
#include "metrics/SwingWingMetric.hpp"
#include "display/DisplayBridge.hpp"
#include "common/Logger.hpp"
#include "common/Constants.hpp"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    XPT_LOG_INFO("Main", "XPlane 12 Telemetry Backend starting — F-14D Tomcat");

    // ------------------------------------------------------------------
    // TODO step 1: instantiate metrics (F-14D Tomcat)
    // ------------------------------------------------------------------
    xpt::metrics::AirspeedMetric    airspeed;
    xpt::metrics::AltitudeMetric    altitude;
    xpt::metrics::AttitudeMetric    attitude;
    xpt::metrics::GForceMetric      gforce;
    xpt::metrics::FuelMetric        fuel;
    xpt::metrics::AOAMetric         aoa;
    xpt::metrics::ThrottleMetric    throttle;   // twin F110-GE-400
    xpt::metrics::NavigationMetric  navigation;
    xpt::metrics::SwingWingMetric   swingWing;  // variable-geometry wing sweep

    // ------------------------------------------------------------------
    // TODO step 2: register metrics with engine
    // ------------------------------------------------------------------
    xpt::metrics::MetricsEngine engine;
    engine.registerMetric(&airspeed);
    engine.registerMetric(&altitude);
    engine.registerMetric(&attitude);
    engine.registerMetric(&gforce);
    engine.registerMetric(&fuel);
    engine.registerMetric(&aoa);
    engine.registerMetric(&throttle);
    engine.registerMetric(&navigation);
    engine.registerMetric(&swingWing);

    // ------------------------------------------------------------------
    // TODO step 3: create and configure a display adapter, then the bridge
    // ------------------------------------------------------------------
    // xpt::display::SomeConcreteAdapter adapter;
    xpt::display::DisplayBridge bridge;
    // bridge.configure(&engine, &adapter);
    // bridge.start(xpt::common::constants::DISPLAY_PUBLISH_RATE_HZ);

    // ------------------------------------------------------------------
    // TODO step 4: start telemetry receiver
    // ------------------------------------------------------------------
    xpt::telemetry::TelemetryReceiver receiver;
    receiver.setHandler(&engine);
    // receiver.start(xpt::common::constants::XPLANE_DEFAULT_UDP_PORT);

    // ------------------------------------------------------------------
    // TODO step 5: block until shutdown signal, then tear down
    // ------------------------------------------------------------------
    XPT_LOG_INFO("Main", "Stub main — nothing running yet");

    return 0;
}
