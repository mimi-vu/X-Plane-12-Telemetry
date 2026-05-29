#include "common/Types.hpp"
#include "telemetry/XPlaneUdpSocket.hpp"

#include <cstdio>
#include <telemetry/DataPacket.hpp>

int main()
{
    xpt::telemetry::XPlaneUdpSocket sock;

    if (sock.open(49003U) != xpt::telemetry::SocketResult::OK)
    {
        printf("ERROR: Failed to open socket\n");
        return 1;
    }

    printf("Socket open. Waiting for data (5 second timeout)...\n");

    xpt::common::uint8 buf[4096U];
    xpt::common::uint32 bytes = 0U;

    xpt::telemetry::SocketResult result = sock.receive(buf, static_cast<xpt::common::uint32>(sizeof(buf)), bytes, 5000U);

    if (result != xpt::telemetry::SocketResult::OK)
    {
        printf("No data received — timeout or error\n");
        printf("Is X-Plane running and sending to port 49003?\n");
        return 1;
    }

    printf("Received %u bytes\n", static_cast<unsigned int>(bytes));

    // Print first 5 bytes — should be D A T A \0
    printf("Header: ");
    for (xpt::common::uint32 i = 0U; i < 5U && i < bytes; ++i)
    {
        printf("[%02X]", buf[i]);
    }
    printf("\n");

    if (bytes >= 5U && buf[0] == static_cast<xpt::common::uint8>('D') && buf[1] == static_cast<xpt::common::uint8>('A') &&
        buf[2] == static_cast<xpt::common::uint8>('T') && buf[3] == static_cast<xpt::common::uint8>('A'))
    {
        printf("Valid DATA packet\n");
        // After "Valid DATA packet" in test.cpp
        xpt::telemetry::DataPacket packet;
        parseDataPacket(buf, bytes, packet);
        for (uint32_t i = 0; i < packet.rowCount; ++i)
        {
            printf("Row %u: index=%d  values[0]=%.2f\n",
                   i, packet.rows[i].index, packet.rows[i].values[0]);
        }
    }
    else
    {
        printf("Unexpected packet format\n");
    }

    sock.close();
    return 0;
}