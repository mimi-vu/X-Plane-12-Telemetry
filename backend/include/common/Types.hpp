/**
 * @file    Types.hpp
 * @brief   Project-wide fixed-width type aliases and domain value types.
 *
 * JSF AV Rule 209: Use C++ fixed-width integer types from <cstdint>.
 * JSF AV Rule 210: Avoid implicit type conversions.
 *
 * @author  XPT Flight Software Team
 * @version 0.1.0
 */

#ifndef XPT_COMMON_TYPES_HPP
#define XPT_COMMON_TYPES_HPP

#include <cstdint>

namespace xpt
{
namespace common
{

// ---------------------------------------------------------------------------
// Scalar type aliases (JSF §AV Rule 209)
// ---------------------------------------------------------------------------
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float    float32;
typedef double   float64;

// ---------------------------------------------------------------------------
// Domain-specific value types
// Strongly typed wrappers prevent unit mix-ups (knots vs m/s, etc.)
// ---------------------------------------------------------------------------

/** Airspeed in knots (indicated). */
struct Knots
{
    explicit Knots(float32 v) : value(v) {}
    float32 value;
};

/** Altitude in feet MSL. */
struct FeetMSL
{
    explicit FeetMSL(float32 v) : value(v) {}
    float32 value;
};

/** Altitude in feet AGL. */
struct FeetAGL
{
    explicit FeetAGL(float32 v) : value(v) {}
    float32 value;
};

/** Vertical speed in feet per minute. */
struct FeetPerMinute
{
    explicit FeetPerMinute(float32 v) : value(v) {}
    float32 value;
};

/** Angle in degrees. */
struct Degrees
{
    explicit Degrees(float32 v) : value(v) {}
    float32 value;
};

/** Acceleration in G (9.80665 m/s²). */
struct GForce
{
    explicit GForce(float32 v) : value(v) {}
    float32 value;
};

/** Fuel quantity in pounds. */
struct Pounds
{
    explicit Pounds(float32 v) : value(v) {}
    float32 value;
};

/** Fuel flow in pounds per hour. */
struct PoundsPerHour
{
    explicit PoundsPerHour(float32 v) : value(v) {}
    float32 value;
};

/** Throttle position 0.0–1.0. */
struct ThrottlePosition
{
    explicit ThrottlePosition(float32 v) : value(v) {}
    float32 value;
};

/** Mach number (dimensionless). */
struct MachNumber
{
    explicit MachNumber(float32 v) : value(v) {}
    float32 value;
};

/** Angle of attack in degrees. */
struct AOADegrees
{
    explicit AOADegrees(float32 v) : value(v) {}
    float32 value;
};

/** Timestamp in milliseconds since epoch. */
typedef uint64 TimestampMs;

} // namespace common
} // namespace xpt

#endif // XPT_COMMON_TYPES_HPP
