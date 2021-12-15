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
0.012088, 
0.008905, 
0.000001, 
-0.009661, 
-0.014307, 
-0.010595, 
-0.000013, 
0.011715, 
0.017483, 
0.013106, 
0.000001, 
-0.014834, 
-0.022500, 
-0.017130, 
-0.000013, 
0.020250, 
0.031497, 
0.024763, 
0.000001, 
-0.031817, 
-0.052521, 
-0.044561, 
-0.000013, 
0.074275, 
0.157556, 
0.222838, 
0.257501, 
0.222838, 
0.157556, 
0.074275, 
-0.000013, 
-0.044561, 
-0.052521, 
-0.031817, 
0.000001, 
0.024763, 
0.031497, 
0.020250, 
-0.000013, 
-0.017130, 
-0.022500, 
-0.014834, 
0.000001, 
0.013106, 
0.017483, 
0.011715, 
-0.000013, 
-0.010595, 
-0.014307, 
-0.009661, 
0.000001, 
0.008905, 
0.012088, 
0.008234, 
-0.000013, 
-0.007662, 
-0.010479, 
-0.007155, 
0.000001, 
0.006739, 
0.009228, 
0.006342, 
-0.000013, 
-0.005995, 
-0.008259, 
-0.005674, 
0.000001, 
0.005415, 
0.007454, 
0.005151, 
-0.000013, 
-0.004918, 
-0.006808, 
-0.004696, 
0.000001, 
0.004522, 
0.006245};

void FIRFilter_Init(FIRFilter *fir){

    /* clear filter buffer */
    for (uint8_t n = 0 ; n < FIR_FILTER_LENGTH ; n++){

        fir->buff[n] = 0.0f;
    
    }

    /* Reset Buffer Index */
    fir->buffIndex = 0;

    /* Clear Filter Output */
    fir->out = 0.0f; 


}

float FIRFilter_Update(FIRFilter *fir, uint8_t *input_sample){
    /* Store Latest sample in buffer */
    fir->buff[fir->buffIndex] = 0; 
    /* Increment buffer index and wrap around if necessary */
    fir->buffIndex++;

    if( fir->buffIndex == FIR_FILTER_LENGTH ){

        fir->buffIndex = 0;
    }

    /* Compute new output sample (CONVOLUTION) */
    fir->out = 0.0f;

    uint8_t sumIndex = fir->buffIndex;

    for(uint8_t n = 0 ; n < FIR_FILTER_LENGTH ; n++ ){
        /* Decrement Index and wrap if necesary */
        if (sumIndex > 0) {

            sumIndex--;

        } 
        else {
            
            sumIndex = FIR_FILTER_LENGTH - 1 ;
        }

        /* Multiply impulse response with shifted input sample and add to output */

        fir->out += FIR_IMPULSE_RESPONSE[n] * fir->buff[sumIndex]; 

    }


    /* return Filtered output */
    return fir->out;

}