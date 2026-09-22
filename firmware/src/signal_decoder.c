#include "signal_decoder.h"
#include <stddef.h>
#include <stdint.h>
static const signal_definition_t definitions[] = {
 {0x100u,"VehicleSpeed",0u,16u,0.01,0.0,0u},
 {0x101u,"EngineRPM",0u,16u,0.25,0.0,0u},
 {0x102u,"CoolantTemp",0u,8u,1.0,-40.0,0u}
};
const signal_definition_t *signal_find(uint32_t can_id){
 for(size_t i=0;i<sizeof(definitions)/sizeof(definitions[0]);++i) if(definitions[i].can_id==can_id) return &definitions[i];
 return NULL;
}
int signal_decode(const can_frame_t *frame,const signal_definition_t *def,double *value){
 if(!frame||!def||!value||def->bit_length==0||def->bit_length>32) return -1;
 if(def->start_bit+def->bit_length>64) return -2;
 if(((def->start_bit+def->bit_length)+7u)/8u>frame->dlc) return -3;
 uint64_t raw=0; for(uint8_t i=0;i<frame->dlc;i++) raw|=((uint64_t)frame->data[i])<<(8u*i);
 uint64_t mask=(1ULL<<def->bit_length)-1ULL; raw=(raw>>def->start_bit)&mask;
 int64_t signed_raw=(int64_t)raw;
 if(def->signed_signal&&(raw&(1ULL<<(def->bit_length-1u)))) signed_raw=(int64_t)(raw|~mask);
 *value=(double)signed_raw*def->scale+def->offset; return 0;
}