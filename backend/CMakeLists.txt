################################################################################
# backend/CMakeLists.txt
# Builds the xpt_backend static library consumed by the main executable
################################################################################

# ---------------------------------------------------------------------------
# Source files
# ---------------------------------------------------------------------------
set(XPT_COMMON_SOURCES
    src/common/Logger.cpp
)

set(XPT_TELEMETRY_SOURCES
    src/telemetry/XPlaneUdpSocket.cpp
    src/telemetry/DataPacket.cpp
    src/telemetry/TelemetryReceiver.cpp
)

set(XPT_METRICS_SOURCES
    src/metrics/MetricsEngine.cpp
    src/metrics/AirspeedMetric.cpp
    src/metrics/AltitudeMetric.cpp
    src/metrics/AttitudeMetric.cpp
    src/metrics/GForceMetric.cpp
    src/metrics/FuelMetric.cpp
    src/metrics/NavigationMetric.cpp
    src/metrics/AOAMetric.cpp
    src/metrics/ThrottleMetric.cpp
    src/metrics/SwingWingMetric.cpp
)

set(XPT_DISPLAY_SOURCES
    src/display/DisplayBridge.cpp
)

# ---------------------------------------------------------------------------
# Static library: xpt_backend
# ---------------------------------------------------------------------------
add_library(xpt_backend STATIC
    ${XPT_COMMON_SOURCES}
    ${XPT_TELEMETRY_SOURCES}
    ${XPT_METRICS_SOURCES}
    ${XPT_DISPLAY_SOURCES}
)

target_include_directories(xpt_backend
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Platform socket libraries
if(WIN32)
    target_link_libraries(xpt_backend PUBLIC ws2_32)
endif()

# ---------------------------------------------------------------------------
# Main executable
# ---------------------------------------------------------------------------
add_executable(xpt_main src/main.cpp)

target_link_libraries(xpt_main PRIVATE xpt_backend)
