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
#include "reverb.h"
#include "param_reverb.h"

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

#define SAMPLES_PER_SECOND 16000L
#define GAIN_IN_dB 0

/* Param reverb data */
/* TO DO: Define data needed for param reverb modules */
/* Buffer size */
/* Reverb buffer (Int16 array with length of "Buffer size") */
/* read index */
/* write index */
/* delay (number of samples) */

// Zadatak 4
#define r_buf_size 8196
Int16 reverb_buffer_L[8196];
Int16 reverb_buffer_R[8196];
Int16 rb_write_L;
Int16 rb_read_L;
Int16 rb_write_R;
Int16 rb_read_R;

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

    printf("\n Vezba 6b - Simulator \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

	aic3204_set_input_filename("../acoustic_guitar.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

	/* Init reverb module*/
	/* Your code here */

    // Vrijednost pojacanja [-1, 1] preslikana na cjelobrojne vrijednosti [-32768, 32768]
    // Pojacanje 0.5 = 16384, 0.25 = 8192

    // Zadatak 3
    //simple_reverb_init(4000, 8192);

    // Zadatak 4
    param_reverb_init(reverb_buffer_L, r_buf_size, &rb_read_L, &rb_write_L, 1600);
    param_reverb_init(reverb_buffer_R, r_buf_size, &rb_read_R, &rb_write_R, 4800);

	/* Loop 10s */
	for(i=0; i<SAMPLES_PER_SECOND/AUDIO_IO_SIZE*10L; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);
		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			/* Call reverb module on InputBufferL and InputBufferR */
			/* Your code here */
			// Zadatak 3
			/*OutputBufferL[j] = simple_reverb(InputBufferL[j]);
			OutputBufferR[j] = InputBufferR[j];*/

			// Zadatak 4
			OutputBufferL[j] = param_reverb(InputBufferL[j], reverb_buffer_L, r_buf_size, &rb_read_L, &rb_write_L, 9830);
			OutputBufferR[j] = param_reverb(InputBufferR[j], reverb_buffer_R, r_buf_size, &rb_read_R, &rb_write_R, 16384);
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

