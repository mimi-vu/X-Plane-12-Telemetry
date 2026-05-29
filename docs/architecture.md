# XPlane 12 Telemetry Backend — Architecture

## Layer Overview

```
XPlane 12 (UDP broadcast)
        │
        ▼
┌───────────────────┐
│  XPlaneUdpSocket  │  OS socket, RAII-managed
└────────┬──────────┘
         │ raw bytes
         ▼
┌───────────────────┐
│   DataPacket      │  Parses XPlane "DATA" UDP frame into typed rows
└────────┬──────────┘
         │ DataPacket
         ▼
┌───────────────────┐
│ TelemetryReceiver │  Receive thread; dispatches via IPacketHandler
└────────┬──────────┘
         │ onPacketReceived()
         ▼
┌───────────────────┐
│  MetricsEngine    │  Fan-out to each IFlightMetric; assembles FlightState
│  ├ AirspeedMetric │
│  ├ AltitudeMetric │
│  ├ AttitudeMetric │
│  ├ GForceMetric   │
│  ├ FuelMetric     │
│  ├ AOAMetric      │
│  ├ ThrottleMetric │  (F135-PW-600, single engine)
│  ├ NavigationMetric
│  ├ LiftSystemMetric  (F-35B: lift fan, 3BSN nozzle, roll posts)
│  └ StovlMetric       (F-35B: conventional / transition / hover state machine)
└────────┬──────────┘
         │ FlightState
         ▼
┌───────────────────┐
│  DisplayBridge    │  Timer thread; publishes at display rate
└────────┬──────────┘
         │ publish()
         ▼
┌───────────────────┐
│ IDisplayAdapter   │  Pluggable: WebSocket, Qt signals, shared memory, …
└───────────────────┘
```

## Threading Model (TODO)

| Thread           | Responsibility                              |
|------------------|---------------------------------------------|
| Receive thread   | Blocks on UDP recv, calls MetricsEngine     |
| Display thread   | Fires at DISPLAY_PUBLISH_RATE_HZ            |
| Main thread      | Startup / shutdown coordination             |

**Data race risk**: MetricsEngine::m_state is written by the receive thread and
read by the display thread. Pick one strategy:
- `std::mutex` around `m_state` reads/writes (simplest)
- Double-buffer (lock-free for reader)
- `std::atomic` flag over a swap pointer

## Key Standards References

- JSF Air Vehicle C++ Coding Standards, Rev C (AV Rules)
- MISRA C++ 2008
- DO-178C (software certification context)
- XPlane 12 SDK `net_spec.cpp` (DATA packet layout)
- ISA (ICAO Doc 7488) — atmospheric constants
