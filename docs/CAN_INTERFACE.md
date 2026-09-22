# CAN Interface

The host logger uses Linux SocketCAN.

Example:
ip link set can0 up type can bitrate 500000
python3 host/socketcan_logger.py --interface can0 --duration 30

Use the bitrate and database appropriate to the actual test bench.