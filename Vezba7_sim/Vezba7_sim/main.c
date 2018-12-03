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
#include "fir.h"

// Zadatak 2
//#include "low_pass_8th_order.h"
#include "low_pass_32th_order.h"
//#include "low_pass_120th_order.h"

// Zadatak 3
#include "high_pass_32th_order.h"

// Zadatak 4
#include "band_pass_32th_order.h"

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

Int16 dirac[AUDIO_IO_SIZE];
Int16 dirac_out[AUDIO_IO_SIZE];

#define SAMPLES_PER_SECOND 48000
#define GAIN_IN_dB 0

/* TO DO: Define history buffers and Rd/Wr pointers*/
/* Your code here */
/*Uint16 p_state_d;
Uint16 p_state_L;
Uint16 p_state_R;*/

// Zadatak 2
/*Int16 history_d[LP_LENGTH];
Int16 history_L[LP_LENGTH];
Int16 history_R[LP_LENGTH];*/

// Zadatak 3
/*Int16 history_d[HP_LENGTH];
Int16 history_L[HP_LENGTH];
Int16 history_R[HP_LENGTH];*/

// Zadatak 4
/*Int16 history_d[BP_LENGTH];
Int16 history_L[BP_LENGTH];
Int16 history_R[BP_LENGTH];*/

// Zadatak 5
Int16 lp_buffer[AUDIO_IO_SIZE];
Int16 bp_buffer[AUDIO_IO_SIZE];
Int16 hp_buffer[AUDIO_IO_SIZE];
Int16 history_lp[LP_LENGTH];
Int16 history_bp[BP_LENGTH];
Int16 history_hp[HP_LENGTH];
Uint16 p_state_lp;
Uint16 p_state_bp;
Uint16 p_state_hp;
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

    // Zadatak 1-4
	//aic3204_set_input_filename("../signal1.pcm");

    // Zadatak 5
    aic3204_set_input_filename("../SpeachPlusNoise.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    dirac[0] = 16000;

	for (i=1; i<AUDIO_IO_SIZE; i++)
	{
		dirac[i] = 0;
	}

    /* TO DO: Initialize history buffers to 0 */
       /* Your code here */
    // Zadatak 2
    /*for (i=0; i<LP_LENGTH; i++)
    {
    	history_d[i] = 0;
    	history_L[i] = 0;
    	history_R[i] = 0;
    }*/

    // Zadatak 3
    /*for (i=0; i<HP_LENGTH; i++)
	{
		history_d[i] = 0;
		history_L[i] = 0;
		history_R[i] = 0;
	}*/

    // Zadatak 4
	/*for (i=0; i<BP_LENGTH; i++)
	{
		history_d[i] = 0;
		history_L[i] = 0;
		history_R[i] = 0;
	}*/

	// Zadatak 5
	for (i=0; i<LP_LENGTH; i++)
	{
		history_lp[i] = 0;
	}

	for (i=0; i<BP_LENGTH; i++)
	{
		history_bp[i] = 0;
	}

	for (i=0; i<HP_LENGTH; i++)
	{
		history_hp[i] = 0;
	}

	/* Loop 10s */
	for(i=0; i<SAMPLES_PER_SECOND/AUDIO_IO_SIZE*10L; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/* TO DO: Invoke filtering routine */
		/* Your code here */

		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			// Zadatak 2
			/*dirac_out[j] = fir_circular(dirac[j], lowpass_5kHz_120th_order, history_d, LP_LENGTH, &p_state_d);
			OutputBufferL[j] = fir_circular(InputBufferL[j], lowpass_5kHz_120th_order, history_L, LP_LENGTH, &p_state_L);
			OutputBufferR[j] = fir_circular(InputBufferR[j], lowpass_5kHz_120th_order, history_R, LP_LENGTH, &p_state_R);*/

			// Zadatak 3
			/*dirac_out[j] = fir_circular(dirac[j], highpass_12kHz_32th_order, history_d, HP_LENGTH, &p_state_d);
			OutputBufferL[j] = fir_circular(InputBufferL[j], highpass_12kHz_32th_order, history_L, HP_LENGTH, &p_state_L);
			OutputBufferR[j] = fir_circular(InputBufferR[j], highpass_12kHz_32th_order, history_R, HP_LENGTH, &p_state_R);*/

			// Zadatak 4
			/*dirac_out[j] = fir_circular(dirac[j], bandpass_5kHz_12kHz_32th_order, history_d, BP_LENGTH, &p_state_d);
			OutputBufferL[j] = fir_circular(InputBufferL[j], bandpass_5kHz_12kHz_32th_order, history_L, BP_LENGTH, &p_state_L);
			OutputBufferR[j] = fir_circular(InputBufferR[j], bandpass_5kHz_12kHz_32th_order, history_R, BP_LENGTH, &p_state_R);*/

			// Zadatak 5
			lp_buffer[j] = fir_circular(InputBufferL[j], lowpass_5kHz_32th_order, history_lp, LP_LENGTH, &p_state_lp);
			bp_buffer[j] = fir_circular(InputBufferL[j], bandpass_5kHz_12kHz_32th_order, history_bp, BP_LENGTH, &p_state_bp);
			hp_buffer[j] = fir_circular(InputBufferL[j], highpass_12kHz_32th_order, history_hp, HP_LENGTH, &p_state_hp);

			OutputBufferL[j] = _smpy(0.75 * 32768, lp_buffer[j]) + bp_buffer[j] + _smpy(0.5*32768, hp_buffer[j]);
			OutputBufferR[j] = InputBufferR[j];
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

