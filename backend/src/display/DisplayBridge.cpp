/**
 * @file    DisplayBridge.cpp
 * @brief   DisplayBridge implementation — STUB.
 *
 * TODO (implementation tasks):
 *   1. start() — spawn publishLoop() on a thread.
 *   2. publishLoop() — see header pseudocode.
 *   3. stop()  — set m_running = false, join thread.
 *
 * @author  XPT Flight Software Team
 */

#include "display/DisplayBridge.hpp"

namespace xpt
{
namespace display
{

DisplayBridge::DisplayBridge()
    : m_engine(nullptr)
    , m_adapter(nullptr)
    , m_running(false)
    , m_rateHz(0U)
{
}

DisplayBridge::~DisplayBridge()
{
    if (m_running)
    {
        stop();
    }
}

void DisplayBridge::configure(xpt::metrics::MetricsEngine* engine, IDisplayAdapter* adapter)
{
    m_engine  = engine;
    m_adapter = adapter;
}

bool DisplayBridge::start(xpt::common::uint32 rateHz)
{
    (void)rateHz;
    // TODO: implement
    return false;
}

void DisplayBridge::stop()
{
    // TODO: implement
    m_running = false;
}

void DisplayBridge::publishLoop()
{
    // TODO: implement — see header pseudocode
}

} // namespace display
} // namespace xpt
