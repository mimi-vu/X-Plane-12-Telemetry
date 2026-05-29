/**
 * @file    MetricsEngineTest.cpp
 * @brief   Unit tests for MetricsEngine — STUB.
 *
 * TODO (test cases to write):
 *   1. Engine with no registered metrics processes a packet without crashing.
 *   2. AirspeedMetric is called on each onPacketReceived().
 *   3. currentState() reflects values from a known synthetic DataPacket.
 *   4. G-force metric sets LIMIT_EXCEEDED when packet contains G > G_LIMIT_POSITIVE.
 *   5. Fuel metric sets WARNING when fuel falls below LOW_FUEL threshold.
 *
 * @author  XPT Flight Software Team
 */

#include "metrics/MetricsEngine.hpp"
#include "metrics/AirspeedMetric.hpp"
#include "metrics/GForceMetric.hpp"

// TODO: #include <gtest/gtest.h>

int main()
{
    // Stub: replace with RUN_ALL_TESTS()
    return 0;
}
