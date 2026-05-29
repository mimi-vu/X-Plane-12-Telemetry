/**
 * @file    XPlaneUdpSocket.cpp
 * @brief   UDP socket wrapper — STUB.
 *

 *   2. In open():
 *        - Create a UDP socket via socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP).
 *        - Set SO_REUSEADDR so the process can restart cleanly.
 *        - Bind to INADDR_ANY (or bindAddress if specified) on the given port.
 *        - Store the handle in m_socketHandle.
 *   3. In receive():
 *        - If timeoutMs > 0, use setsockopt(SO_RCVTIMEO) or select() to set a timeout.
 *        - Call recvfrom() into the caller's buffer.
 *        - Write actual byte count to bytesReceived.
 *   4. In close():
 *        - On Windows call closesocket(); on POSIX call ::close().
 *        - Reset m_isOpen = false.
 *
 * @author  XPT Flight Software Team
 */

#include "telemetry/XPlaneUdpSocket.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // link socket functions ?

namespace xpt
{
namespace telemetry
{

XPlaneUdpSocket::XPlaneUdpSocket()
    : m_socketHandle(-1)
    , m_isOpen(false)
{
    // TODO: on Windows, call WSAStartup() here (or in a global init function)
}

XPlaneUdpSocket::~XPlaneUdpSocket()
{
    if (m_isOpen)
    {
        close();
    }
}

SocketResult XPlaneUdpSocket::open(xpt::common::uint16 port, const std::string& bindAddress)
{
    // create socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) return SocketResult::ERR_PLATFORM;

    int resuse = 1; 

    // setsockopt() is a function that configures options for the socket
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(resuse)); 

    sockaddr_in addr{};
    addr.sin_family = AF_INET; 
    addr.sin_port   = htons(port); // cpu reads port number in little-endian, needs to be big

    if (bindAddress.empty()) addr.sin_addr.s_addr = INADDR_ANY;  // accept from any network 
    else inet_pton(AF_INET, bindAddress.c_str(), &addr.sin_addr); // convert IP address to binary

    // bind to port
    int result = bind(sock, (sockaddr*)&addr, sizeof(addr)); 

    if (result < 0) return SocketResult::ERR_BIND;

    return SocketResult::ERR_CLOSED;
}

// waits for udp packet to arrive, copies bytes into buffer
SocketResult XPlaneUdpSocket::receive(xpt::common::uint8*  buffer,
                                       xpt::common::uint32  bufferCapacity,
                                       xpt::common::uint32& bytesReceived,
                                       xpt::common::uint32  timeoutMs)
{
    if (timeoutMS > 0U) {
        DWORD tv = static_cast<DWORD>(timeoutMs);
        setsockopt(m_socketHandle, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
    }

    
    return SocketResult::ERR_CLOSED;
}

void XPlaneUdpSocket::close()
{
    // TODO: implement — see file header
    m_isOpen = false;
}

bool XPlaneUdpSocket::isOpen() const
{
    return m_isOpen;
}

} // namespace telemetry
} // namespace xpt
