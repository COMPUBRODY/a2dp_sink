#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "FIR_Filter.h"
#include "coeficients.h"

typedef struct 
{
    //float buff[FIR_FILTER_LENGTH];  //circular buffer 
    uint8_t buffIndex;              //index del buffer  
    float out;                      //salida del buffer
}FIRFilter;

FIRFilter fir;
float buffer[1024];

void FIRFilter_Init(void){

	    /* clear filter buffer 
    for (uint8_t n = 0 ; n < FIR_FILTER_LENGTH ; n++){
        fir.buff[n] = 0.0f;
    }*/
		/* Reset Buffer Index */
    fir.buffIndex = 0;
	fir.out = 0.0;

}

inline uint8_t * FIR_filter(uint8_t* data, size_t size){
	for(int i=0; i<size/4; i++){

		buffer[i] = ( ( (float)data[i] /256)*2 )-1.0;
	}
	for(int i=0; i<size/4; i++){
		fir.out = 0.0;
		for(int m = 0; m <FIR_FILTER_LENGTH; m++){
			fir.out += FIR_IMPULSE_RESPONSE[m] * buffer[fir.buffIndex];
			fir.buffIndex = (fir.buffIndex == 0) ?  FIR_FILTER_LENGTH-1 : fir.buffIndex-1;
		}
		fir.buffIndex++;

		data[i] = (uint8_t)((( fir.out +1 )/2 )*256);
	}
	return data;
}