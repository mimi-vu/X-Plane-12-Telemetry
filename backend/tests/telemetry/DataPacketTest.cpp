/**
 * @file    DataPacketTest.cpp
 * @brief   Unit tests for parseDataPacket() — STUB.
 *
 * TODO (test cases to write once parseDataPacket is implemented):
 *   1. Empty buffer         → ParseResult::ERR_TOO_SHORT
 *   2. Wrong header bytes   → ParseResult::ERR_BAD_HEADER
 *   3. Valid single-row packet  → rowCount == 1, correct index and values
 *   4. Valid multi-row packet   → rowCount correct, spot-check values
 *   5. Packet with too many rows → ParseResult::ERR_OVERFLOW
 *   6. Timestamp is non-zero after parse
 *
 * @author  XPT Flight Software Team
 */

#include "telemetry/DataPacket.hpp"

// TODO: #include <gtest/gtest.h> and replace the stub below.

int main()
{
    // Stub: replace with GoogleTest RUN_ALL_TESTS() once GTest is wired in.
    return 0;
}
