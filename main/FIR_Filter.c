#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "FIR_Filter.h"

static float FIR_IMPULSE_RESPONSE[FIR_FILTER_LENGTH]={
0.006245, 
0.004522, 
0.000001, 
-0.004696, 
-0.006808, 
-0.004918, 
-0.000013, 
0.005151, 
0.007454, 
0.005415, 
0.000001, 
-0.005674, 
-0.008259, 
-0.005995, 
-0.000013, 
0.006342, 
0.009228, 
0.006739, 
0.000001, 
-0.007155, 
-0.010479, 
-0.007662, 
-0.000013, 
0.008234, 
};

float *uint8_to_float(uint8_t* data, size_t size){
	float signal = 0.0;
	float *signal_data = NULL;
	if(signal_data!=NULL)
		free(signal_data);
	signal_data = (float*)calloc(size, sizeof(float));
	for(int i=0 ; i<size ; i++){
		signal = ( ( (float)data[i] /255)*2 ) -1.0;
		signal_data[i] = signal;
	}
	return (float*)signal_data;
}

uint8_t *float_to_uint8(float* signal, size_t size){
	uint8_t *signal_out = NULL;
	if(signal_out!=NULL)
		free(signal_out);
	signal_out =(uint8_t*)calloc(size,sizeof(uint8_t));
	for(int i = 0; i<size ; i++){
		signal_out[i] = (uint8_t)(( (signal[i] +1 )/2 )*256);
	}
	return (uint8_t*)signal_out;
}


void FIRFilter_Init(FIRFilter *fir){
    /* clear filter buffer */
    for (uint8_t n = 0 ; n < FIR_FILTER_LENGTH ; n++){
        fir->buff[n] = 0.0f;
    }
    /* Reset Buffer Index */
    fir->buffIndex = 0;
    /* Clear Filter Output */
    fir->out = 0.0; 
}

/* funcion muestra de convolucion */
float * convolution(FIRFilter *fir, float *signal_in, size_t size ){
	float *signal_out = NULL;
	if(signal_out != NULL)
		free(signal_out);
	signal_out = (float*)calloc(size, sizeof(float));
	/* ASIGNAR EL VALOR DE LA SEÑAL DE ENTRADA AL BUFFER CIRCULAR */
	for(int i=0; i<size ; i++){
		fir->buff[i] = signal_in[i];
	}

	for(int m = 0; m<size ; m++){
		fir->out = 0.0;
		for(int i=0 ; i<size ; i++){

			/* MULTIPLICAR COEFICIENTE CON LA SEÑAL DE ENTRADA RECORRIDA Y SUMARLA AL OUTPUT */
			fir->out += FIR_IMPULSE_RESPONSE[i] * fir->buff[fir->buffIndex];
			/* incrementar el index de n en caso de ser menor que L*/
			(fir->buffIndex == 0) ? fir->buffIndex = FIR_FILTER_LENGTH-1 : fir->buffIndex--;
		}
		/* si el buffer esta en la pos 0 le incremento 1 y si no tambien xd */
		fir->buffIndex++;
		//printf("Conv [%d] = %f\n", m, fir->out);
		signal_out[m] = fir->out;

	}
	return (float*)signal_out;
}

uint8_t * FIR_filter(FIRFilter *fir, uint8_t* data, size_t size){
	
	float *signal_data = NULL;
	if(signal_data!=NULL)
		free(signal_data);
	signal_data = (float*)calloc(size, sizeof(float));
	
	signal_data = (float*)uint8_to_float(data, size); 
	//signal_data = (float*)convolution(&fir, signal_data, size); 
	
	data = (uint8_t*)float_to_uint8(signal_data, size);
	free(signal_data);
	return (uint8_t*)data;
}
