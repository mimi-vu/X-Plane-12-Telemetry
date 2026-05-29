/**
 * @file    DataPacket.cpp
 * @brief   XPlane 12 DATA packet parser — STUB.
 *
 * TODO (implementation tasks):
 *   1. Validate the buffer is at least 5 bytes (header "DATA\0") + one DataRow.
 *   2. Read bytes 0–3 and confirm they equal 'D','A','T','A'.
 *   3. Starting at byte 5, cast each 36-byte block to a DataRow:
 *        int32   @ offset+0  → row.index
 *        float32 @ offset+4  → row.values[0]
 *        float32 @ offset+8  → row.values[1]
 *        ...
 *        float32 @ offset+32 → row.values[7]
 *   4. Increment outPacket.rowCount per valid row; stop at DATA_PACKET_MAX_ROWS.
 *   5. Record receiveTimestampMs (use a platform clock call).
 *
 * CAUTION: Mind endianness — XPlane sends little-endian; ensure host byte order
 *          matches or add a swap step for big-endian targets.
 *
 * @author  XPT Flight Software Team
 */

#include "telemetry/DataPacket.hpp"

namespace xpt
{
namespace telemetry
{

ParseResult parseDataPacket(const xpt::common::uint8* buffer, xpt::common::uint32 length, DataPacket& outPacket)
{
    const xpt::common::uint32 HEADER_SIZE = 5U;
    const xpt::common::uint32 ROW_SIZE = 36U;

    // validate length
    if (length < 5)
        return ParseResult::ERR_TOO_SHORT;

    // validate header
    if (buffer[0] != 'D' || buffer[1] != 'A' || buffer[2] != 'T' || buffer[3] != 'A')
        return ParseResult::ERR_BAD_HEADER;

    // sub-records
    outPacket.rowCount = 0;
    xpt::common::uint32 offset = HEADER_SIZE; // 5

    while ((offset + ROW_SIZE) <= length)
    {
        if (outPacket.rowCount >= DATA_PACKET_MAX_ROWS)
            return ParseResult::ERR_OVERFLOW;

        DataRow& row = outPacket.rows[outPacket.rowCount];

        // read index from first 4 bytes of the row
        memcpy(&row.index, buffer + offset, sizeof(xpt::common::int32));
        offset += sizeof(xpt::common::int32);

        // read 8 float32 values

        for (xpt::common::uint32 i = 0U; i < 8U; ++i)
        {
            memcpy(&row.values[i], buffer + offset, sizeof(xpt::common::float32));
            offset += sizeof(xpt::common::float32);
        }

        ++outPacket.rowCount;
    }

    outPacket.receiveTimestampMs =
        static_cast<xpt::common::TimestampMs>(static_cast<xpt::common::uint64>(clock()) * 1000U / CLOCKS_PER_SEC);

    return ParseResult::OK;
}

} // namespace telemetry
} // namespace xpt
