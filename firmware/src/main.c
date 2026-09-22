#include "can_logger.h"
#include "can_frame.h"
#include <stdio.h>
int main(void){
 logger_init();
 can_frame_t speed={.id=0x100,.dlc=2,.data={0x10,0x27}};
 can_frame_t rpm={.id=0x101,.dlc=2,.data={0x80,0x3E}};
 can_frame_t temp={.id=0x102,.dlc=1,.data={90}};
 printf("timestamp_ms,can_id,signal,value\n");
 logger_process_frame(&speed,1000); logger_process_frame(&rpm,1020); logger_process_frame(&temp,1040);
 const logger_stats_t *s=logger_get_stats();
 fprintf(stderr,"frames=%lu decoded=%lu unknown=%lu invalid=%lu\n",s->total_frames,s->decoded_frames,s->unknown_frames,s->invalid_frames);
 return 0;
}