# CAN Bus Vehicle Data Logger

A portfolio-ready automotive CAN telemetry logging project. The logger receives CAN frames, validates them, decodes configured signals, timestamps telemetry and stores normalized records for analysis.

## Architecture

CAN Bus -> CAN Receive -> Frame Validation -> Signal Decoder -> Telemetry Record -> CSV / Diagnostics

## Technology
- Embedded C
- CAN 2.0 concepts
- STM32 / ARM Cortex-M integration hooks
- Linux SocketCAN host testing
- Bit-level signal extraction
- Timestamped CSV logging
- Python validation tests

## Example signal database

| CAN ID | Signal | Start | Length | Scale | Offset |
|---:|---|---:|---:|---:|---:|
| 0x100 | VehicleSpeed | 0 | 16 | 0.01 | 0 |
| 0x101 | EngineRPM | 0 | 16 | 0.25 | 0 |
| 0x102 | CoolantTemp | 0 | 8 | 1 | -40 |

These are illustrative values, not OEM signal definitions.

## Structure

```text
firmware/inc/        C interfaces
firmware/src/        CAN logger and signal decoder
host/                Linux SocketCAN utility
config/              example signal database
tests/               Python decoder tests
docs/                architecture and test documentation
Makefile             GCC build
```

## Build

```bash
make
./build/can_logger
```

## Host SocketCAN

```bash
python3 host/socketcan_logger.py --interface can0 --duration 10
```

## Tests

```bash
python3 -m unittest discover -s tests -v
```

## Production boundary

Vehicle CAN IDs and layouts vary by ECU and OEM. Replace the example database with validated target-vehicle definitions before hardware use. This is an educational portfolio implementation, not production vehicle software.

## Author
Kenny
