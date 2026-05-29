/**
 * @file    Constants.hpp
 * @brief   Physical, aviation, and system constants for the F-14 Tomcat simulation.
 *
 * Aircraft: Grumman F-14D Tomcat, twin General Electric F110-GE-400 engines,
 *           variable-geometry swing wings (20°–68°, oversweep 75° on deck).
 *
 * JSF AV Rule 141: Use const/constexpr — never #define for numeric values.
 *
 * TODO (research tasks):
 *   - Determine XPlane 12's default UDP port and packet structure from
 *     the XPlane 12 Developers guide / net_spec.cpp in the SDK.
 *   - Decide on a target update rate that balances latency vs CPU load.
 *   - Confirm F110-GE-400 afterburner engagement throttle threshold.
 *   - Confirm wing sweep schedule vs Mach/altitude from NATOPS.
 *
 * @author  XPT Flight Software Team
 */

#ifndef XPT_COMMON_CONSTANTS_HPP
#define XPT_COMMON_CONSTANTS_HPP

#include "Types.hpp"

namespace xpt
{
namespace common
{
namespace constants
{

// ---------------------------------------------------------------------------
// Physical constants — research ISA/ICAO standard atmosphere
// ---------------------------------------------------------------------------
constexpr float64 STANDARD_GRAVITY_MPS2    = 9.80665;  
constexpr float32 SPEED_OF_SOUND_SL_KTS   = 661.47F; 
constexpr float32 STD_PRESSURE_INHG        = 29.92F; 
constexpr float32 FEET_PER_METRE           = 3.28084F; 
constexpr float32 KNOTS_TO_MPS             = 0.514444F; 

// ---------------------------------------------------------------------------
// F-14D flight envelope limits — consult NATOPS / Jane's / open-source data
// F-14D structural limit is +7.5g; operational (FCS-protected) is +6.5g
// ---------------------------------------------------------------------------
constexpr float32 G_LIMIT_POSITIVE         = 7.5F;
constexpr float32 G_LIMIT_NEGATIVE         = -3.0F;
constexpr float32 VMAX_KIAS                = 800.0F;  // Mach 2.34 at altitude
constexpr float32 AOA_WARNING_DEG          = 50.0F;   // TODO: verify F-14 departure threshold
constexpr float32 CEILING_FEET             = 50000.0F;

// ---------------------------------------------------------------------------
// F-14 variable-geometry wing sweep limits
// ---------------------------------------------------------------------------
constexpr float32 WING_SWEEP_MIN_DEG       = 20.0F;  // fully forward (low speed)
constexpr float32 WING_SWEEP_MAX_DEG       = 68.0F;  // fully swept (high speed)
constexpr float32 WING_SWEEP_OVERSWEEP_DEG = 75.0F;  // carrier deck stow only
constexpr float32 WING_SWEEP_AUTO_SCHEDULE = 0.0F;   // TODO: document auto-schedule Mach breakpoints

// ---------------------------------------------------------------------------
// XPlane 12 UDP protocol — see XPlane 12 SDK net_spec.cpp
// ---------------------------------------------------------------------------
constexpr uint16 XPLANE_DEFAULT_UDP_PORT   = 49000U;   // xplane12 docs
constexpr uint32 UDP_RECV_BUFFER_BYTES     = 4096U;   //  size to max expected packet
constexpr uint32 XPLANE_DATA_VALUES_PER_ROW = 8U;  

// ---------------------------------------------------------------------------
// Metrics / display timing
// ---------------------------------------------------------------------------
constexpr uint32 METRICS_UPDATE_RATE_HZ    = 60U;   // TODO: decide based on display needs
constexpr uint32 DISPLAY_PUBLISH_RATE_HZ   = 20U;   // TODO: decide

} 
} 
} 

#endif // XPT_COMMON_CONSTANTS_HPP
