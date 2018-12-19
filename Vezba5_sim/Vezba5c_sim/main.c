//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Main function.
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
// *
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "math.h"
#include "sine.h"

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

#define SAMPLES_PER_SECOND 48000
#define GAIN_IN_dB 0

#define PI 3.141592653589793238

Int16 zeros[AUDIO_IO_SIZE];

Int32 DFTReal[AUDIO_IO_SIZE];
Int32 DFTImag[AUDIO_IO_SIZE];

Int32 magnitude[AUDIO_IO_SIZE/2];

void dft(float inreal[], float inimag[], float outreal[], float outimag[], Int16 N)
{
	int n, k;
    for ( n = 0; n < N; n++) {
        float sumreal = 0;
        float sumimag = 0;
        for (k = 0; k < N; k++) {
            sumreal +=  inreal[k] * cos(2 * PI * n * k / N) + inimag[k] * sin(2 * PI * n * k / N);
            sumimag += -inreal[k] *  sin(2 * PI * n * k / N) + inimag[k] * cos(2 * PI * n * k / N);
        }
        outreal[n] = sumreal;
        outimag[n] = sumimag;
    }
}

// TO DO: finish DFT function
void dft_int(Int16 inreal[], Int16 inimag[], Int32 outreal[], Int32 outimag[], Uint16 N)
{
	Uint16 n, k;

	// calculate scale_factor
	/* Your code here */
	int scale_factor = 65536 / N;

	for ( n = 0; n < N; n++)
	{
		Int32 sumreal = 0;
	    Int32 sumimag = 0;

	    for (k = 0; k < N; k++)
	    {
	    	// calculate DFT inner loop
	    	/* Your code here */
	    	sumreal += (Int32) _smpy(inreal[k], cos_LT(n * k * scale_factor)) + _smpy(inimag[k], sin_LT(n * k * scale_factor));
			sumimag += (Int32) _smpy(-inreal[k], sin_LT(n * k * scale_factor)) + _smpy(inimag[k], cos_LT(n * k * scale_factor));

	    }

	    // store calculated values into output buffers
	    /* Your code here */
	    outreal[n] = sumreal;
		outimag[n] = sumimag;
	}
}


/*
 *
 *  main( )
 *
 */
void main( void )
{
	int i, j;
    /* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Vezba 5c - Simulator \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

	aic3204_set_input_filename("../sine_1kHz.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    for(i = 0; i < AUDIO_IO_SIZE; i++)
    {
    	zeros[i] = 0;
    }

	/* Loop 10s */
	for(i=0; i<SAMPLES_PER_SECOND/AUDIO_IO_SIZE*10L; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		dft_int(InputBufferL, zeros, DFTReal, DFTImag, AUDIO_IO_SIZE);

		for (j=0; j < AUDIO_IO_SIZE / 2; j++)
		{
			magnitude[j] = (Int32)DFTReal[j]*DFTReal[j]+(Int32)DFTImag[j]*DFTImag[j];

		}

		aic3204_write_block(InputBufferR, InputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

