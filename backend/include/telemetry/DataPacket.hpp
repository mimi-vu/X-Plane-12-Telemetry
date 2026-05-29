/**
 * @file    DataPacket.hpp
 * @brief   Parsed representation of one XPlane 12 UDP "DATA" frame.
 *
 * XPlane 12 UDP DATA format (little-endian):
 *   Bytes 0-3  : ASCII header "DATA" (or "DATA|" — 5 bytes with null)
 *   Then N sub-records, each:
 *     Byte 0      : int32 — Data Index (which channel, e.g. 3 = speeds, 17 = pitch/roll)
 *     Bytes 4-35  : 8 × float32 — channel values (unused slots = -999.0)
 *
 * TODO: Read XPlane 12 SDK file net_spec.cpp and map every Data Index you need
 *       to a named field in this struct.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_TELEMETRY_DATA_PACKET_HPP
#define XPT_TELEMETRY_DATA_PACKET_HPP

#include "common/Types.hpp"

#include <ctime>
#include <cstring>

namespace xpt
{
namespace telemetry
{

/**
 * @brief  Raw sub-record from one XPlane DATA row.
 *         Each row has an index and 8 float32 slots.
 */
struct DataRow
{
    xpt::common::int32 index;       ///< XPlane data index (channel ID)
    xpt::common::float32 values[8]; ///< Channel values; unused = -999.0f
};

/**
 * @brief  Maximum number of DATA rows expected in a single packet.
 *         TODO: Determine the real max from XPlane 12 SDK docs.
 */
static const xpt::common::uint32 DATA_PACKET_MAX_ROWS = 64U;

/**
 * @struct DataPacket
 * @brief  A fully parsed XPlane 12 DATA frame ready for the metrics engine.
 *
 * Populated by DataPacket::parse() from a raw UDP byte buffer.
 */
struct DataPacket
{
    xpt::common::uint32 rowCount;                ///< Number of valid rows
    DataRow rows[DATA_PACKET_MAX_ROWS];          ///< Parsed rows
    xpt::common::TimestampMs receiveTimestampMs; ///< Wall-clock receive time
};

/**
 * @brief  Parse status returned by DataPacket::parse().
 */
enum class ParseResult : xpt::common::uint8
{
    OK = 0U,             ///< Packet parsed successfully.
    ERR_TOO_SHORT = 1U,  ///< Buffer is smaller than minimum packet size.
    ERR_BAD_HEADER = 2U, ///< First 4 bytes are not "DATA".
    ERR_OVERFLOW = 3U    ///< More rows than DATA_PACKET_MAX_ROWS.
};

/**
 * @brief  Parse a raw UDP byte buffer into a DataPacket.
 *
 * @param  buffer     Pointer to raw UDP payload.
 * @param  length     Number of valid bytes in buffer.
 * @param  outPacket  Destination packet (populated on ParseResult::OK).
 * @return ParseResult indicating success or failure reason.
 *
 * TODO: implement in DataPacket.cpp — walk the buffer, validate header,
 *       loop over sub-records casting to DataRow layout.
 */
ParseResult parseDataPacket(const xpt::common::uint8* buffer, xpt::common::uint32 length, DataPacket& outPacket);

} // namespace telemetry
} // namespace xpt

#endif // XPT_TELEMETRY_DATA_PACKET_HPP
