#ifndef FIR_FILTER_H
#define FIR_FILTER_H


#include <stdint.h>

#define FIR_FILTER_LENGTH 101 

typedef struct 
{
    float buff[FIR_FILTER_LENGTH];  //circular buffer 
    uint8_t buffIndex;              //index del buffer  
    float out;                      //salida del buffer
}FIRFilter;


void FIRFilter_Init(FIRFilter *fir);
float FIRFilter_Update(FIRFilter *fir, uint8_t *input_sample);  

#endif