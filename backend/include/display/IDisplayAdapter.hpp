/**
 * @file    IDisplayAdapter.hpp
 * @brief   Pure-virtual interface between the backend and any display frontend.
 *
 * The backend never knows whether the frontend is a Qt widget, a WebSocket
 * server, a shared-memory MFD renderer, or a unit-test mock.
 * It only calls IDisplayAdapter::publish() with a FlightState.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_DISPLAY_IDISPLAY_ADAPTER_HPP
#define XPT_DISPLAY_IDISPLAY_ADAPTER_HPP

#include "metrics/MetricsEngine.hpp"

namespace xpt
{
namespace display
{

class IDisplayAdapter
{
public:
    virtual ~IDisplayAdapter() {}

    /**
     * @brief  Push the latest FlightState to the display layer.
     * @param  state  Snapshot from MetricsEngine::currentState().
     *
     * Implementations can:
     *   - Serialise to JSON and push over WebSocket (for a web-based MFD).
     *   - Write to shared memory (for a same-process Qt frontend).
     *   - Emit Qt signals (if the adapter lives inside the Qt event loop).
     *
     * TODO: choose an IPC/serialisation strategy and implement in DisplayBridge.
     */
    virtual void publish(const xpt::metrics::FlightState& state) = 0;
};

} // namespace display
} // namespace xpt

#endif // XPT_DISPLAY_IDISPLAY_ADAPTER_HPP
