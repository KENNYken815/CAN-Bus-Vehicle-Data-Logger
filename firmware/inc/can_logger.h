#ifndef CAN_LOGGER_H
#define CAN_LOGGER_H
#include "can_frame.h"
typedef struct { unsigned long total_frames, decoded_frames, unknown_frames, invalid_frames; } logger_stats_t;
void logger_init(void);
int logger_process_frame(const can_frame_t*, unsigned long timestamp_ms);
const logger_stats_t *logger_get_stats(void);
#endif