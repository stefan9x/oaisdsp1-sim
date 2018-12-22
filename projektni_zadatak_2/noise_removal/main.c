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
#include "fir.h"
#include "iir.h"
#include "coeff.h"

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

Int16 impulse[AUDIO_IO_SIZE];
Int16 impulseOut[AUDIO_IO_SIZE];

Int16 temp1[AUDIO_IO_SIZE];
Int16 temp2[AUDIO_IO_SIZE];

// Promijeniti duzinu niza u zavisnosti 
// od duzine filtera F1_COEFFS = 33 ili F2_COEFFS = 121
Int16 historyImp[F2_COEFFS];
Int16 historyL[F2_COEFFS];

Uint16 p_state_imp;
Uint16 p_state_L;

Int16 x_z[3];
Int16 y_z[3];
Int16 x_z1[3];
Int16 y_z1[3];
Int16 x_z2[3];
Int16 y_z2[3];

//TO DO: Create history buffer here



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

    aic3204_set_input_filename("../signal2.wav");
	aic3204_set_output_filename("../Zadatak6.wav");

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

	impulse[0] = 16000;

	for (i = 1; i < AUDIO_IO_SIZE; i++)
	{
		impulse[i] = 0;
	}

	for (i = 0; i < F1_COEFFS; i++)
	{
		historyImp[i] = 0;
		historyL[i] = 0;
	}

	p_state_imp = 0;
	p_state_L = 0;

	for (i = 0; i < 3; i++)
	{
		x_z[i] = 0;
		y_z[i] = 0;
		x_z1[i] = 0;
		y_z1[i] = 0;
		x_z2[i] = 0;
		y_z2[i] = 0;
	}

	// Processing loop. Place your code here...
    for(i = 0; i < number_of_blocks; i++)
    {
    	aic3204_read_block(inputBufferL, inputBufferR);

    	for(j = 0; j < AUDIO_IO_SIZE; j++)
    	{
			//TO DO: Call filter routine here. Use coefficients from coeffs.h
    		// Zadatak 2
    		//impulseOut[j] = fir_circular(impulse[j], filter1_coeffs, historyImp, F1_COEFFS, &p_state_imp);
    		//outputBufferL[j] = fir_circular(inputBufferL[j], filter1_coeffs, historyL, F1_COEFFS, &p_state_L);

    		// Zadatak 3
    		//impulseOut[j] = fir_circular(impulse[j], filter2_coeffs, historyImp, F2_COEFFS, &p_state_imp);
    		//outputBufferL[j] = fir_circular(inputBufferL[j], filter2_coeffs, historyL, F2_COEFFS, &p_state_L);

    		// Zadatak 5
    		//impulseOut[j] = second_order_IIR(impulse[j], iir_notch_coeffs, x_z, y_z);
    		//outputBufferL[j] = second_order_IIR(inputBufferL[j], iir_notch_coeffs, x_z, y_z);

    		// Zadatak 6
    		/*temp1[j] = second_order_IIR(impulse[j], iir_notch_coeffs, x_z, y_z);
    		temp2[j] = second_order_IIR(temp1[j], iir_notch_coeffs, x_z1, y_z1);
    		impulseOut[j] = second_order_IIR(temp2[j], iir_notch_coeffs, x_z2, y_z2);*/

    		temp1[j] = second_order_IIR(inputBufferL[j], iir_notch_coeffs, x_z, y_z);
			temp2[j] = second_order_IIR(temp1[j], iir_notch_coeffs, x_z1, y_z1);
			outputBufferL[j] = second_order_IIR(temp2[j], iir_notch_coeffs, x_z2, y_z2);

    	}
    	aic3204_write_block(outputBufferL, outputBufferL);
    	printf( "%ld of %ld \n", i, number_of_blocks);
	}


	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

