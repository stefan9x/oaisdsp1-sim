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
#include "convolution_reverb.h"
#include "signal.h"
#include "impulse_response.h"

#define SAMPLES_PER_SECOND 8000L
#define GAIN_IN_dB 0

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];


/* For testing purpose, keep output values in buffer, so it could be plotted */
#pragma DATA_SECTION(output_signal, ".output_signal")
Int16 output_signal[SIGNAL_LENGTH];

/*
 *
 *  main( )
 *
 */
void main( void )
{
    Int16 i, j;

	/* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Vezba 6c - Simulator \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

    aic3204_set_input_filename("../input1.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    /* calculate convolution with room model signal */
	convolution(signal, SIGNAL_LENGTH, impulse_response, IMPULSE_RESPONSE_LENGTH, output_signal);


	for (i = 0; i < SIGNAL_LENGTH/AUDIO_IO_SIZE; i++)
	{
		for (j = 0; j < AUDIO_IO_SIZE; j++)
		{
			OutputBufferL[j] = output_signal[i * AUDIO_IO_SIZE + j];
		}

		aic3204_write_data(OutputBufferL, AUDIO_IO_SIZE);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

