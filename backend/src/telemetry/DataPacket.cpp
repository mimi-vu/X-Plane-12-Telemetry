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

ParseResult parseDataPacket(const xpt::common::uint8* buffer,
                             xpt::common::uint32        length,
                             DataPacket&                outPacket)
{
    (void)buffer;
    (void)length;
    (void)outPacket;
    // TODO: implement — see file header
    return ParseResult::ERR_TOO_SHORT;
}

} // namespace telemetry
} // namespace xpt
