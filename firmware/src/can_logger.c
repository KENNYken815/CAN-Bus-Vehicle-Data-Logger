#include "can_logger.h"
#include "signal_decoder.h"
#include <stdio.h>
static logger_stats_t stats;
void logger_init(void){stats=(logger_stats_t){0};}
int logger_process_frame(const can_frame_t *frame,unsigned long timestamp_ms){
 if(!frame||frame->dlc>CAN_MAX_DATA){stats.invalid_frames++;return -1;}
 stats.total_frames++;
 const signal_definition_t *def=signal_find(frame->id);
 if(!def){stats.unknown_frames++;return 1;}
 double value; if(signal_decode(frame,def,&value)!=0){stats.invalid_frames++;return -2;}
 stats.decoded_frames++; printf("%lu,%lu,%s,%.3f\n",timestamp_ms,(unsigned long)frame->id,def->name,value); return 0;
}
const logger_stats_t *logger_get_stats(void){return &stats;}