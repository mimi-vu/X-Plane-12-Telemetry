/**
 * @file    TelemetryReceiver.cpp
 * @brief   TelemetryReceiver implementation — STUB.
 *
 *
 * Threading consideration:
 *   m_running is read on both the main thread (stop()) and the receive thread.
 *   Use std::atomic<bool> or a mutex-guarded flag to avoid a data race.
 *
 * @author  XPT Flight Software Team
 */

#include "telemetry/TelemetryReceiver.hpp"

#include "common/Constants.hpp"
#include "common/Logger.hpp"
#include "telemetry/DataPacket.hpp"

namespace xpt
{
namespace telemetry
{

TelemetryReceiver::TelemetryReceiver() : m_handler(nullptr), m_running(false)
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

    if (m_running)
        return false; // already running

    // open udp socket and bind to port
    SocketResult result = m_socket.open(port);

    if (result != SocketResult::OK)
    {
        XPT_LOG_ERROR("TelemetryReceiver", "Failed to open socket");
        return false;
    }

    m_running = true;

    m_thread = std::thread([this]() { receiveLoop(); });

    XPT_LOG_INFO("TelemetryReceiver", "Started receiver thread");

    return true;
}

void TelemetryReceiver::stop()
{
    m_running = false;
    m_socket.close();
    // wait for recieve thread to finish then exit
    if (m_thread.joinable())
        m_thread.join();

    XPT_LOG_INFO("TelemetryReceiver", "Stopped receiver thread");
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
    xpt::common::uint8 buffer[xpt::common::constants::UDP_RECV_BUFFER_BYTES];
    xpt::common::uint32 bytesRead = 0U;

    // 200ms timeout
    const xpt::common::uint32 RECV_TIMEOUT_MS = 200U;

    while (m_running)
    {
        // block until UDP packet is received or timeout

        SocketResult socketResult = m_socket.receive(buffer, sizeof(buffer), bytesRead, RECV_TIMEOUT_MS);

        // if closed by stop()
        if (socketResult != SocketResult::ERR_CLOSED)
            break;

        // if timeout or other error, continue
        if (socketResult != SocketResult::ERR_RECV)
            continue;

        // parse the packet
        DataPacket packet;
        ParseResult parseResult = parseDataPacket(buffer, bytesRead, packet);
        if (parseResult != ParseResult::OK)
        {
            XPT_LOG_ERROR("TelemetryReceiver", "Failed to parse packet");
            continue;
        }

        // dispatch to handler
        if (m_handler != nullptr)
            m_handler->onPacketReceived(packet);
    }
}

} // namespace telemetry
} // namespace xpt
