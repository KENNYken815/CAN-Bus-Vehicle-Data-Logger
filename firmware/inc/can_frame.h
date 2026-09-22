#ifndef CAN_FRAME_H
#define CAN_FRAME_H
#include <stdint.h>
#define CAN_MAX_DATA 8
typedef struct { uint32_t id; uint8_t dlc; uint8_t data[CAN_MAX_DATA]; } can_frame_t;
#endif