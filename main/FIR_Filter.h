#ifndef FIR_FILTER_H
#define FIR_FILTER_H

void FIRFilter_Init(void);
uint8_t * FIR_filter(uint8_t* data, size_t size);

#endif