/**
 * @file    XPlaneUdpSocket.cpp
 * @brief   UDP socket wrapper — Windows implementation.
 *
 * @author  XPT Flight Software Team
 */

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include "telemetry/XPlaneUdpSocket.hpp"

#include <cstdio>

namespace xpt
{
namespace telemetry
{

// ---------------------------------------------------------------------------
// Constructor — initialise members and start Winsock on Windows
// ---------------------------------------------------------------------------
XPlaneUdpSocket::XPlaneUdpSocket() : m_socketHandle(-1), m_isOpen(false)
{
#ifdef _WIN32
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        printf("WSAStartup failed: %d\n", result);
    }
#endif
}

// ---------------------------------------------------------------------------
// Destructor — close socket if still open, cleanup Winsock
// ---------------------------------------------------------------------------
XPlaneUdpSocket::~XPlaneUdpSocket()
{
    if (m_isOpen)
    {
        close();
    }

#ifdef _WIN32
    WSACleanup();
#endif
}

// ---------------------------------------------------------------------------
// open() — create socket, set options, bind to port
// ---------------------------------------------------------------------------
SocketResult XPlaneUdpSocket::open(xpt::common::uint16 port, const std::string& bindAddress)
{
    // Step 1 — create the UDP socket
    // socket() asks the OS for a new socket handle
    // AF_INET     = IPv4
    // SOCK_DGRAM  = UDP (datagram, fire and forget)
    // IPPROTO_UDP = explicitly UDP protocol
#ifdef _WIN32
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
    {
        printf("socket() failed: %d\n", WSAGetLastError());
        return SocketResult::ERR_PLATFORM;
    }
#else
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
    {
        return SocketResult::ERR_PLATFORM;
    }
#endif

    // Step 2 — set SO_REUSEADDR
    // allows us to restart the app and reuse the port immediately
    // without this, Windows holds the port for ~60s after the app closes
    int reuse = 1;
    setsockopt(static_cast<SOCKET>(sock), SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&reuse), sizeof(reuse));

    // Step 3 — fill in the address structure
    // this tells bind() which port and interface to listen on
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // convert port to network byte order (big-endian)

    if (bindAddress.empty())
    {
        // INADDR_ANY = accept packets arriving on any network interface
        // this is almost always what you want
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        // convert human-readable IP string "192.168.1.1" to binary
        inet_pton(AF_INET, bindAddress.c_str(), &addr.sin_addr);
    }

    // Step 4 — bind the socket to the port
    // after this, the OS knows that packets arriving on this port
    // belong to our program
    if (bind(static_cast<SOCKET>(sock), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
#ifdef _WIN32
        printf("bind() failed: %d\n", WSAGetLastError());
        closesocket(sock);
#else
        ::close(sock);
#endif
        return SocketResult::ERR_BIND;
    }

    // Step 5 — store the handle and mark as open
    // int64 is wide enough to hold both Windows SOCKET (uint64) and POSIX int
    m_socketHandle = static_cast<xpt::common::int64>(sock);
    m_isOpen = true;

    printf("Socket bound to port %u successfully\n", static_cast<unsigned int>(port));

    return SocketResult::OK;
}

// ---------------------------------------------------------------------------
// receive() — block until a UDP packet arrives, copy into caller's buffer
// ---------------------------------------------------------------------------
SocketResult XPlaneUdpSocket::receive(xpt::common::uint8* buffer, xpt::common::uint32 bufferCapacity,
                                      xpt::common::uint32& bytesReceived, xpt::common::uint32 timeoutMs)
{
    // guard — cannot receive on a closed socket
    if (!m_isOpen)
    {
        bytesReceived = 0U;
        return SocketResult::ERR_CLOSED;
    }

    // Step 1 — set receive timeout if requested
    // without a timeout, recvfrom() blocks forever
    // with a timeout, it returns ERR_RECV after timeoutMs milliseconds
    // so the caller can check if X-Plane is still running
    if (timeoutMs > 0U)
    {
#ifdef _WIN32
        // Windows timeout is a DWORD in milliseconds
        DWORD tv = static_cast<DWORD>(timeoutMs);
        setsockopt(static_cast<SOCKET>(m_socketHandle), SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&tv), sizeof(tv));
#else
        // POSIX timeout uses a timeval struct (seconds + microseconds)
        timeval tv{};
        tv.tv_sec = static_cast<long>(timeoutMs / 1000U);
        tv.tv_usec = static_cast<long>((timeoutMs % 1000U) * 1000U);
        setsockopt(static_cast<int>(m_socketHandle), SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&tv), sizeof(tv));
#endif
    }

    // Step 2 — receive the packet
    // recvfrom() blocks here until a packet arrives or timeout fires
    // it fills buffer with the raw bytes and returns how many bytes arrived
    // sender is filled with the IP/port of whoever sent the packet
    sockaddr_in sender{};
    int senderLen = static_cast<int>(sizeof(sender));

    int received = recvfrom(static_cast<SOCKET>(m_socketHandle),  // which socket
                            reinterpret_cast<char*>(buffer),      // destination buffer
                            static_cast<int>(bufferCapacity),     // max bytes to receive
                            0,                                    // flags (0 = normal)
                            reinterpret_cast<sockaddr*>(&sender), // who sent it
                            &senderLen);                          // size of sender struct

    // Step 3 — handle errors
    if (received < 0)
    {
        bytesReceived = 0U;
        return SocketResult::ERR_RECV; // includes timeout case
    }

    // Step 4 — write out how many bytes arrived
    bytesReceived = static_cast<xpt::common::uint32>(received);
    return SocketResult::OK;
}

// ---------------------------------------------------------------------------
// close() — release the OS socket handle
// ---------------------------------------------------------------------------
void XPlaneUdpSocket::close()
{
    if (m_isOpen)
    {
#ifdef _WIN32
        closesocket(static_cast<SOCKET>(m_socketHandle));
#else
        ::close(static_cast<int>(m_socketHandle));
#endif
        m_socketHandle = -1;
        m_isOpen = false;
    }
}

// ---------------------------------------------------------------------------
// isOpen() — read-only query, does not modify object (const)
// ---------------------------------------------------------------------------
bool XPlaneUdpSocket::isOpen() const
{
    return m_isOpen;
}

} // namespace telemetry
} // namespace xpt