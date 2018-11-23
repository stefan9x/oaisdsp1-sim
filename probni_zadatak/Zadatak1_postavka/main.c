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
#include "ADSR.h"
#include "gen_sinus.h"
#include "fur_elise.h"
#include "quant.h"

#define BLOCK_SIZE 197
#define SAMPLE_RATE 44100
#define NUM_SAMPLES (SAMPLE_RATE*furEliseLength)
#define GENERATOR_NUM 5
#define GAIN_IN_dB 0

#pragma DATA_ALIGN(outputBuffer, 4)
Int16 outputBuffer[BLOCK_SIZE];

float tempBuffer[BLOCK_SIZE];
Int16 tempBuffer2[BLOCK_SIZE];


/*
 *
 *  main( )
 *
 */
void main( void )
{
	Int32 i;
	Int16 j;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initializatition
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Projektni zadatak 1 \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

	aic3204_set_output_filename("../output.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN_IN_dB);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Task No.1
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // TO DO
    //gen_sinus_table(1000, 1, 0.02, 0, tempBuffer);
    //gen_sinus_table(1000, 5, 0.05, 234, tempBuffer);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Task No.2 - Synthisizer
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Create current tone pointer for each sine generator
    tone_t* current_tone_ch[GENERATOR_NUM] = {furEliseNotes0, furEliseNotes1, furEliseNotes2,furEliseNotes3, furEliseNotes4 };

    // Loop through entire song
	for(i=0; i<furEliseLength; i++)
	{
		int k;

		// Set output buffer to silence
		for(k = 0; k < BLOCK_SIZE; k++)
		{
			outputBuffer[k] = 0;
		}

		// For each sine generator
		for(j = 0; j < GENERATOR_NUM; j++)
		{
			// If current tone timestamp is less than or equals current moment (i)
			if( current_tone_ch[j]->time <= i)
			{

				// Generate sine wave using frequency of a current tone
				// Phase is number of samples passed since tone has started playing
				// Amplitude is 1.0
				gen_sinus_table(BLOCK_SIZE, 1.0, note_to_freq(current_tone_ch[j]->note)/SAMPLE_RATE, (i-current_tone_ch[j]->time) * BLOCK_SIZE, tempBuffer);

			    // TO DO
				// Pass tone through ADSR unit
				ADSR(tempBuffer, BLOCK_SIZE, (i - current_tone_ch[j]->time), current_tone_ch[j]->duration*BLOCK_SIZE);
				// TO DO

				// Perform quantization and clipping of generated signal
				// Add the result to outputBuffer
				// TO DO
				for(k = 0; k < BLOCK_SIZE; k++)
				{
					tempBuffer2[k] = quantB(tempBuffer[k], 15);
					tempBuffer2[k] = clipB(tempBuffer2[k], 14);
					outputBuffer[k] += tempBuffer2[k];

				}

				// If current tone is finished, increment current tone ptr
				if((i - current_tone_ch[j]->time) >= (current_tone_ch[j]->duration - 1))
				{
					current_tone_ch[j]++;
				}
			}
		}

       // Write outputBuffer to output file
	   aic3204_write_data(outputBuffer, BLOCK_SIZE);
	}


	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

