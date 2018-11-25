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
#include "stdlib.h"
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "delay.h"
#include "echo.h"

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

#define SAMPLES_PER_SECOND 16000L
#define BUFFER_LENGTH 1000
#define GAIN_IN_dB 0

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

    printf("\n Simulator loopback \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

	aic3204_set_input_filename("../acoustic_guitar.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    /* Call delay init */
	// Zadatak 1
    //delay_init(8000);

    // Zadatak 2
    // Vrijednost pojacanja [-1, 1] preslikana na cjelobrojne vrijednosti [-32768, 32767]
    // Pojacanje 0.5 = 16384, 0.25 = 8192
    echo_init(4000, 16384);

	/* Loop 10s */
	for(i=0; i<SAMPLES_PER_SECOND/AUDIO_IO_SIZE*30L; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			// Zadatak 1
			/*OutputBufferR[j] = InputBufferR[j];
			OutputBufferL[j] = delay(InputBufferL[j]);*/

			// Zadatak 2
			OutputBufferR[j] = InputBufferR[j];
			OutputBufferL[j] = echo(InputBufferL[j]);
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}
