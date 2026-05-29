/**
 * @file    DisplayBridge.hpp
 * @brief   Concrete adapter: polls MetricsEngine and pushes to a registered
 *          IDisplayAdapter at the configured display rate.
 *
 * DisplayBridge runs on its own timer thread and decouples the display
 * refresh rate (e.g. 10 Hz) from the telemetry receive rate (e.g. 20 Hz).
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_DISPLAY_DISPLAY_BRIDGE_HPP
#define XPT_DISPLAY_DISPLAY_BRIDGE_HPP

#include "IDisplayAdapter.hpp"
#include "metrics/MetricsEngine.hpp"
#include "common/Types.hpp"

namespace xpt
{
namespace display
{

class DisplayBridge
{
public:
    DisplayBridge();
    ~DisplayBridge();

    /**
     * @brief  Wire up the data source and the display sink.
     * @param  engine   MetricsEngine to read FlightState from.
     * @param  adapter  IDisplayAdapter to push FlightState to.
     */
    void configure(xpt::metrics::MetricsEngine* engine, IDisplayAdapter* adapter);

    /**
     * @brief  Start the publish timer thread.
     * @param  rateHz  Publish frequency (from constants::DISPLAY_PUBLISH_RATE_HZ).
     */
    bool start(xpt::common::uint32 rateHz);

    /** Stop the timer thread. */
    void stop();

private:
    DisplayBridge(const DisplayBridge&);
    DisplayBridge& operator=(const DisplayBridge&);

    /**
     * @brief  Timer loop body — called at rateHz.
     *
     * TODO: implement:
     *   1. Call m_engine->currentState() to get the latest snapshot.
     *   2. Call m_adapter->publish(state).
     *   3. Sleep for (1000 / rateHz) ms before next iteration.
     */
    void publishLoop();

    xpt::metrics::MetricsEngine* m_engine;
    IDisplayAdapter*             m_adapter;
    bool                         m_running;
    xpt::common::uint32          m_rateHz;
};

} // namespace display
} // namespace xpt

#endif // XPT_DISPLAY_DISPLAY_BRIDGE_HPP
