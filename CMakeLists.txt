################################################################################
# XPlane12 Telemetry Backend
# Root CMakeLists.txt
#
# Conforms to: JSF Air Vehicle C++ Coding Standards (AV Rules), Rev C
# Compiler: MSVC 19+ / GCC 13+ / Clang 17+   C++ Standard: C++14 (JSF §AV Rule 8)
################################################################################
cmake_minimum_required(VERSION 3.22)

project(
    XPlane12Telemetry
    VERSION 0.1.0
    DESCRIPTION "Real-time F-16/JSF flight metrics backend for XPlane 12"
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# Language standard — JSF AV Rule 8: C++14 maximum for DO-178C alignment
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)   # AV Rule 8: no GNU extensions

# ---------------------------------------------------------------------------
# Compiler warnings — treat warnings as errors in CI (AV Rule 1)
# ---------------------------------------------------------------------------
if(MSVC)
    add_compile_options(/W4 /WX /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wshadow)
endif()

# ---------------------------------------------------------------------------
# Global output directories
# ---------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(XPT_BUILD_TESTS    "Build unit test suite"  ON)
option(XPT_ENABLE_LOGGING "Enable runtime logging" ON)

if(XPT_ENABLE_LOGGING)
    add_compile_definitions(XPT_LOGGING_ENABLED)
endif()

# ---------------------------------------------------------------------------
# Sub-projects
# ---------------------------------------------------------------------------
add_subdirectory(backend)

if(XPT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(backend/tests)
endif()
