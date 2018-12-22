//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Course assignment 2 - Noise removal
// * Course: OAiS DSP1
// * Year: 2018
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "WAVheader.h"

// Zadatak 2
#include "fir.h"
//#include "band_pass_33rd_order.h"

// Zadatak 3
#include "FIR_band_pass_121st_order.h"

// Zadatak 4
#include "iir.h"
#include "IIR_band_pass_2nd_order.h"

// Zadatak 5
#include "IIR_low_pass_2nd_order.h"
#include "IIR_high_pass_2nd_order.h"


#define SAMPLE_RATE 16000L
#define CHANNEL_NUM 2
#define GAIN_IN_dB 0

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#pragma DATA_ALIGN(outputBufferL, 4)
Int16 inputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(outputBufferR, 4)
Int16 inputBufferR[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(outputBufferL, 4)
Int16 outputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(outputBufferR, 4)
Int16 outputBufferR[AUDIO_IO_SIZE];

// Zadatak 2,3
Int16 impulse[AUDIO_IO_SIZE];
Int16 impulseOut[AUDIO_IO_SIZE];
Int16 historyImp[AUDIO_IO_SIZE];
Int16 temp[AUDIO_IO_SIZE];
Int16 historyL[Ntap];
Int16 historyR[Ntap];
Uint16 p_stateImp;
Uint16 p_stateL;
Uint16 p_stateR;

// Zadatak 4, 5
Int16 z_x[3];
Int16 z_y[3];
Int16 z_xL[3];
Int16 z_yL[3];
Int16 z_xR[3];
Int16 z_yR[3];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	Int32 i, j;
	Int32 number_of_blocks;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initializatition
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialize BSL
    EZDSP5535_init( );

    printf("\n OAiS DSP 1 - Second assignment 2018. \n");

    // Initialise hardware interface and I2C for code
    aic3204_hardware_init();

    aic3204_set_input_filename("../signal.wav");

    aic3204_set_output_filename("../Zadatak4.wav");

    // Initialise the AIC3204 codec
	aic3204_init();

    // Setup sampling frequency and 30dB gain for microphone
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN_IN_dB);

    aic3204_read_wav_header(&inputWAVhdr);

	// Set up output WAV header
	outputWAVhdr = inputWAVhdr;

	number_of_blocks = inputWAVhdr.data.SubChunk2Size/
			(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

	aic3204_write_wav_header(&outputWAVhdr);

	// Zadatak 2
	impulse[0] = 16000;

	for (i=1; i<AUDIO_IO_SIZE; i++)
	{
		impulse[i] = 0;
	}

	p_stateImp = 0;
	p_stateL = 0;
	p_stateR = 0;

	for (i = 0; i < Ntap; i++)
	{
		historyImp[i] = 0;
		historyL[i] = 0;
		historyR[i] = 0;
	}

	// Zadatak 4
	for (i = 0; i < 3; i++)
	{
		z_x[i] = 0;
		z_y[i] = 0;

		// Zadatak 5
		z_xL[i] = 0;
		z_yL[i] = 0;
		z_xR[i] = 0;
		z_yR[i] = 0;
	}

	// Processing loop. Place your code here...
    for(i = 0; i < number_of_blocks; i++)
    {
    	aic3204_read_block(inputBufferL, inputBufferR);

    	for(j = 0; j < AUDIO_IO_SIZE; j++)
    	{
    		// Zadatak 2
    		//impulseOut[j] = fir_circular(impulse[j], band_pass_33rd_order, historyImp, Ntap, &p_stateImp);
    		//outputBufferL[j] = fir_circular(inputBufferL[j], band_pass_33rd_order, historyL, Ntap, &p_stateL);

    		// Zadatak 3
			//impulseOut[j] = fir_circular(impulse[j], band_pass_121st_order, historyImp, Ntap, &p_stateImp);
			//outputBufferL[j] = fir_circular(inputBufferL[j], band_pass_121st_order, historyL, Ntap, &p_stateL);

    		// Zadatak 4
    		impulseOut[j] = second_order_IIR(impulse[j], IIR_band_pass_2nd_order, z_x, z_y);
     		//outputBufferL[j] = second_order_IIR(inputBufferL[j], IIR_band_pass_2nd_order, z_x, z_y);

    		// Zadatak 5
    		//temp[j] = second_order_IIR(impulse[j], IIR_low_pass_2nd_order, z_xL, z_yL);
    		//impulseOut[j] = second_order_IIR(temp[j], IIR_high_pass_2nd_order, z_xR, z_yR);

			//temp[j] = second_order_IIR(inputBufferL[j], IIR_low_pass_2nd_order, z_xL, z_yL);
			//outputBufferL[j] = second_order_IIR(temp[j], IIR_high_pass_2nd_order, z_xR, z_yR);

    	}
    	aic3204_write_block(outputBufferL, outputBufferL);
    	printf( "%ld of %ld \n", i, number_of_blocks);
	}


	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}
