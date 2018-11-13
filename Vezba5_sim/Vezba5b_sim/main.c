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
#include "Dsplib.h"

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

#define SAMPLES_PER_SECOND 48000
#define BUFFER_LENGTH 1000
#define GAIN_IN_dB 0

Int32 magnitude_response[AUDIO_IO_SIZE/2];

/* 128 HaMMing window in Q0.15 */
Int16 window[AUDIO_IO_SIZE]=
{
	0x0a3d, 0x0a50, 0x0a86, 0x0ae1, 0x0b5f, 0x0c01, 0x0cc6, 0x0daf,
	0x0eb9, 0x0fe5, 0x1131, 0x129e, 0x142a, 0x15d4, 0x179b, 0x197e,
	0x1b7c, 0x1d94, 0x1fc4, 0x220c, 0x2468, 0x26da, 0x295d, 0x2bf2,
	0x2e96, 0x3149, 0x3407, 0x36d0, 0x39a2, 0x3c7b, 0x3f59, 0x423b,
	0x451f, 0x4802, 0x4ae4, 0x4dc2, 0x509b, 0x536d, 0x5636, 0x58f5,
	0x5ba7, 0x5e4b, 0x60e0, 0x6364, 0x65d5, 0x6832, 0x6a79, 0x6ca9,
	0x6ec1, 0x70bf, 0x72a3, 0x746a, 0x7614, 0x77a0, 0x790c, 0x7a59,
	0x7b85, 0x7c8f, 0x7d77, 0x7e3c, 0x7ede, 0x7f5d, 0x7fb7, 0x7fee,
	0x7fff, 0x7fee, 0x7fb7, 0x7f5d, 0x7ede, 0x7e3c, 0x7d77, 0x7c8f,
	0x7b85, 0x7a59, 0x790c, 0x77a0, 0x7614, 0x746a, 0x72a3, 0x70bf,
	0x6ec1, 0x6ca9, 0x6a79, 0x6832, 0x65d5, 0x6364, 0x60e0, 0x5e4b,
	0x5ba7, 0x58f5, 0x5636, 0x536d, 0x509b, 0x4dc2, 0x4ae4, 0x4802,
	0x451f, 0x423b, 0x3f59, 0x3c7b, 0x39a2, 0x36d0, 0x3407, 0x3149,
	0x2e96, 0x2bf2, 0x295d, 0x26da, 0x2468, 0x220c, 0x1fc4, 0x1d94,
	0x1b7c, 0x197e, 0x179b, 0x15d4, 0x142a, 0x129e, 0x1131, 0x0fe5,
	0x0eb9, 0x0daf, 0x0cc6, 0x0c01, 0x0b5f, 0x0ae1, 0x0a86, 0x0a50
};

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

	aic3204_set_input_filename("../sine_1kHz.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

	/* Loop 10s */
	for(i=0; i<SAMPLES_PER_SECOND/AUDIO_IO_SIZE*10L; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		// Zadatak 3
		/*for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			InputBufferR[j] = _smpy(InputBufferR[j], window[j]);
		}*/

		// Zadatak 2
		rfft(InputBufferR, AUDIO_IO_SIZE, SCALE);

		magnitude_response[0] =  (Int32)InputBufferR[0]*InputBufferR[0];

		for (j=1; j < AUDIO_IO_SIZE/2; j++)
		{
			magnitude_response[j] = (Int32)InputBufferR[2*j]*InputBufferR[2*j]+(Int32)InputBufferR[2*j+1]*InputBufferR[2*j+1];

		}

		aic3204_write_block(InputBufferL, InputBufferL);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

