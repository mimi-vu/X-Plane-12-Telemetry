/**
 * @file    TelemetryReceiver.cpp
 * @brief   TelemetryReceiver implementation — STUB.
 *
 * TODO (implementation tasks):
 *   1. start()  — open the socket, set m_running = true, spawn receiveLoop
 *                 on a std::thread (stored as a member).
 *   2. stop()   — set m_running = false, call m_socket.close() to unblock
 *                 any pending recv, then join the thread.
 *   3. receiveLoop() — see the pseudocode in TelemetryReceiver.hpp.
 *                 Handle SocketResult::ERR_RECV (log and continue) vs
 *                 SocketResult::ERR_CLOSED (exit loop cleanly).
 *
 * Threading consideration:
 *   m_running is read on both the main thread (stop()) and the receive thread.
 *   Use std::atomic<bool> or a mutex-guarded flag to avoid a data race.
 *
 * @author  XPT Flight Software Team
 */

#include "telemetry/TelemetryReceiver.hpp"
#include "common/Logger.hpp"

namespace xpt
{
namespace telemetry
{

TelemetryReceiver::TelemetryReceiver()
    : m_handler(nullptr)
    , m_running(false)
{
}

TelemetryReceiver::~TelemetryReceiver()
{
    if (m_running)
    {
        stop();
    }
}

bool TelemetryReceiver::start(xpt::common::uint16 port)
{
    (void)port;
    // TODO: implement — open socket, start thread
    return false;
}

void TelemetryReceiver::stop()
{
    // TODO: implement — set m_running = false, close socket, join thread
}

void TelemetryReceiver::setHandler(IPacketHandler* handler)
{
    m_handler = handler;
}

bool TelemetryReceiver::isRunning() const
{
    return m_running;
}

void TelemetryReceiver::receiveLoop()
{
    // TODO: implement receive loop — see TelemetryReceiver.hpp pseudocode
}

} // namespace telemetry
} // namespace xpt
