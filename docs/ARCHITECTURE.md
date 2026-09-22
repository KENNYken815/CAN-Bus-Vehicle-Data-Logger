# Architecture

CAN interface -> frame validation -> signal decoder -> telemetry record -> CSV / diagnostics

The signal decoder is independent of the CAN controller, allowing unit testing with synthetic frames.