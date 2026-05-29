/**
 * @file    TelemetryReceiver.hpp
 * @brief   Drives the receive loop: socket → parse → dispatch to MetricsEngine.
 *
 * This class runs on its own thread. It calls XPlaneUdpSocket::receive(),
 * parses the raw bytes into a DataPacket, then hands the packet to a
 * registered IPacketHandler for further processing.
 *
 * Design note:
 *   The receiver deliberately knows nothing about specific metrics; it only
 *   produces DataPackets. This decouples transport from domain logic.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_TELEMETRY_TELEMETRY_RECEIVER_HPP
#define XPT_TELEMETRY_TELEMETRY_RECEIVER_HPP

#include "DataPacket.hpp"
#include "XPlaneUdpSocket.hpp"
#include "common/Types.hpp"

#include <atomic>
#include <thread>

namespace xpt
{
namespace telemetry
{

/**
 * @class IPacketHandler
 * @brief Callback interface for consumers of parsed DataPackets.
 *
 * Implement this in MetricsEngine (or any other consumer) and register it
 * with TelemetryReceiver::setHandler().
 */
class IPacketHandler
{
public:
    virtual ~IPacketHandler()
    {
    }

    /**
     * @brief  Called once per successfully parsed DataPacket.
     * @param  packet  The freshly parsed XPlane 12 DATA frame.
     *
     * TODO: Keep this handler fast — it runs on the receiver thread.
     *       Offload heavy computation to a separate worker or queue.
     */
    virtual void onPacketReceived(const DataPacket& packet) = 0;
};

/**
 * @class TelemetryReceiver
 * @brief Owns the socket and receive loop; dispatches packets to a handler.
 */
class TelemetryReceiver
{
public:
    TelemetryReceiver();
    ~TelemetryReceiver();

    /**
     * @brief  Bind the socket and start the receive thread.
     * @param  port  UDP port to listen on (XPlane default: 49000).
     * @return true on successful bind and thread start.
     */
    bool start(xpt::common::uint16 port);

    /**
     * @brief  Signal the receive loop to exit and join the thread.
     */
    void stop();

    /**
     * @brief  Register the handler that receives parsed DataPackets.
     * @param  handler  Pointer to an IPacketHandler; must outlive this receiver.
     */
    void setHandler(IPacketHandler* handler);

    /** Returns true while the receive loop is running. */
    bool isRunning() const;

private:
    // Non-copyable (JSF AV Rule 68)
    TelemetryReceiver(const TelemetryReceiver&);
    TelemetryReceiver& operator=(const TelemetryReceiver&);

    /**
     * @brief  The receive loop — runs on m_thread.
     *
     * TODO: implement the loop body:
     *   while (m_running) {
     *     socket.receive(buf, capacity, bytesRead, timeoutMs);
     *     parseDataPacket(buf, bytesRead, packet);
     *     m_handler->onPacketReceived(packet);
     *   }
     */
    void receiveLoop();

    XPlaneUdpSocket m_socket;
    IPacketHandler* m_handler;
    std::atomic<bool> m_running;
    std::thread m_thread;

    // TODO: add a std::thread (or platform thread handle) for receiveLoop()
};

} // namespace telemetry
} // namespace xpt

#endif // XPT_TELEMETRY_TELEMETRY_RECEIVER_HPP
