#ifndef FIR_FILTER_H
#define FIR_FILTER_H


#define FIR_FILTER_LENGTH 24

typedef struct 
{
    float buff[FIR_FILTER_LENGTH];  //circular buffer 
    uint8_t buffIndex;              //index del buffer  
    float out;                      //salida del buffer
}FIRFilter;

float * uint8_to_float(uint8_t* data, size_t size);
uint8_t *float_to_uint8(float* signal, size_t size);
void FIRFilter_Init(FIRFilter *fir);
float * convolution(FIRFilter *fir, float *signal_in, size_t size );
uint8_t * FIR_filter(FIRFilter *fir, uint8_t* data, size_t size);

#endif