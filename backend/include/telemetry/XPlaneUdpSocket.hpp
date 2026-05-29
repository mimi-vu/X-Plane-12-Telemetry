/**
 * @file    XPlaneUdpSocket.hpp
 * @brief   Platform-abstracted UDP socket wrapper for XPlane 12 DATA packets.
 *
 * XPlane 12 broadcasts telemetry via UDP on port 49000 (default).
 * This class owns the OS socket handle and exposes a blocking receive call.
 * The socket is non-copyable and RAII-managed.
 *
 * JSF AV Rule 77: Encapsulate all OS resource handles in RAII wrappers.
 *
 * @author  XPT Flight Software Team
 * @version 0.1.0
 */

#ifndef XPT_TELEMETRY_XPLANE_UDP_SOCKET_HPP
#define XPT_TELEMETRY_XPLANE_UDP_SOCKET_HPP

#include "common/Types.hpp"
#include <string>

namespace xpt
{
namespace telemetry
{

/**
 * @brief Result codes for socket operations.
 */
enum class SocketResult : xpt::common::uint8
{
    OK          = 0U, ///< Operation succeeded.
    ERR_BIND    = 1U, ///< Failed to bind to port.
    ERR_RECV    = 2U, ///< Receive error or timeout.
    ERR_CLOSED  = 3U, ///< Socket has been closed.
    ERR_PLATFORM = 4U ///< Unrecoverable platform error.
};

/**
 * @class XPlaneUdpSocket
 * @brief Non-blocking / blocking UDP socket that receives XPlane 12 broadcasts.
 *
 * Lifecycle:
 *   XPlaneUdpSocket sock;
 *   sock.open(49000);         // bind to port
 *   sock.receive(buf, len);   // blocks until data arrives or timeout
 *   sock.close();             // explicit release (also called by destructor)
 */
class XPlaneUdpSocket
{
public:
    XPlaneUdpSocket();
    ~XPlaneUdpSocket();

    /**
     * @brief  Bind the socket to a local UDP port.
     * @param  port          UDP port number (default: 49000).
     * @param  bindAddress   Interface to bind on; "" means INADDR_ANY.
     * @return SocketResult::OK on success.
     */
    SocketResult open(xpt::common::uint16 port, const std::string& bindAddress = "");

    /**
     * @brief  Receive one UDP datagram into the caller-supplied buffer.
     * @param  buffer         Destination byte buffer.
     * @param  bufferCapacity Size of buffer in bytes.
     * @param  bytesReceived  Out: number of bytes written to buffer.
     * @param  timeoutMs      Receive timeout in milliseconds (0 = blocking).
     * @return SocketResult::OK if data was received.
     */
    SocketResult receive(xpt::common::uint8* buffer,
                         xpt::common::uint32 bufferCapacity,
                         xpt::common::uint32& bytesReceived,
                         xpt::common::uint32  timeoutMs = 0U);

    /**
     * @brief  Close and release the socket handle.
     */
    void close();

    /** Returns true when the socket is open and bound. */
    bool isOpen() const;

private:
    // Non-copyable (JSF AV Rule 68)
    XPlaneUdpSocket(const XPlaneUdpSocket&);
    XPlaneUdpSocket& operator=(const XPlaneUdpSocket&);

    // Platform handle stored as intptr to avoid platform headers in this header
    xpt::common::int64 m_socketHandle;
    bool               m_isOpen;
};

} // namespace telemetry
} // namespace xpt

#endif // XPT_TELEMETRY_XPLANE_UDP_SOCKET_HPP
