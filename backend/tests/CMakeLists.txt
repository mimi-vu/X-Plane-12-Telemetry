################################################################################
# backend/tests/CMakeLists.txt
# Unit test suite — add a CTest entry per test binary.
# Recommended test framework: Google Test (fetch via FetchContent or vcpkg).
################################################################################

# TODO: add GoogleTest via FetchContent or vcpkg and enable below.
# include(FetchContent)
# FetchContent_Declare(googletest URL https://github.com/google/googletest/...)
# FetchContent_MakeAvailable(googletest)

# ---------------------------------------------------------------------------
# Telemetry tests
# ---------------------------------------------------------------------------
add_executable(test_data_packet
    telemetry/DataPacketTest.cpp
)
target_link_libraries(test_data_packet PRIVATE xpt_backend)
add_test(NAME DataPacketTest COMMAND test_data_packet)

# ---------------------------------------------------------------------------
# Metrics tests
# ---------------------------------------------------------------------------
add_executable(test_metrics_engine
    metrics/MetricsEngineTest.cpp
)
target_link_libraries(test_metrics_engine PRIVATE xpt_backend)
add_test(NAME MetricsEngineTest COMMAND test_metrics_engine)
