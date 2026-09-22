#ifndef SIGNAL_DECODER_H
#define SIGNAL_DECODER_H
#include "can_frame.h"
typedef struct { uint32_t can_id; const char *name; uint8_t start_bit; uint8_t bit_length; double scale; double offset; uint8_t signed_signal; } signal_definition_t;
int signal_decode(const can_frame_t*, const signal_definition_t*, double*);
const signal_definition_t *signal_find(uint32_t can_id);
#endif