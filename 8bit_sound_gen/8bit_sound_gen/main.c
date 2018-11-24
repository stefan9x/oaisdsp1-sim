//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Course assignment 1 - Simulator of Nintendo NES Audio
// * Processing Unit.
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
#include "ADSR.h"
#include "gen_signal.h"
#include "super_mario_theme.h"
#include "quant.h"
#include "WAVheader.h"
#include "math.h"

#define BLOCK_SIZE 2100
#define SAMPLE_RATE 44100L
#define NUM_SAMPLES (SAMPLE_RATE*superMarioThemeLength)
#define CHANNEL_NUM 1
#define GAIN_IN_dB 0

static WAV_HEADER outputWAVhdr;

#pragma DATA_ALIGN(outputBuffer, 4)
Int16 outputBuffer[BLOCK_SIZE];

static float tempBuffer[BLOCK_SIZE];
float tone[BLOCK_SIZE];
float noise[BLOCK_SIZE];

float calculate_snr(float* signal, float* noise, Uint16 n)
{
	/* Your code here*/
	// Zadatak 2
	int i = 0;
	float Ps = 0, Pe = 0;
	for (i = 0; i < n; i++)
	{
		Ps += (signal[i] * signal[i]) / n;
		Pe += (noise[i] * noise[i]) / n;
	}
	return 10 * log10(Ps/Pe);
}

/*
 *
 *  main( )
 *
 */
void main( void )
{
	Int32 i;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initializatition
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialize BSL
    EZDSP5535_init( );

    printf("\n OAiS DSP 1 - First assignment 2018. \n");

    // Initialise hardware interface and I2C for code
    aic3204_hardware_init();

	aic3204_set_output_filename("../SuperMario.wav");

    // Initialise the AIC3204 codec
	aic3204_init();

    // Setup sampling frequency and 30dB gain for microphone
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN_IN_dB);

	// Set up output WAV header
	outputWAVhdr = defaultWavHeader;
	outputWAVhdr.fmt.NumChannels = CHANNEL_NUM;
	outputWAVhdr.fmt.SampleRate = SAMPLE_RATE;
	Int16 octetsPerSample = outputWAVhdr.fmt.BitsPerSample/8;
	outputWAVhdr.data.SubChunk2Size = NUM_SAMPLES * CHANNEL_NUM * octetsPerSample;
	outputWAVhdr.fmt.ByteRate = SAMPLE_RATE * octetsPerSample * CHANNEL_NUM;
	outputWAVhdr.riff.ChunkSize = 36 + outputWAVhdr.data.SubChunk2Size;

    aic3204_write_wav_header(&outputWAVhdr);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Task No.1
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // TO DO
    // Zadatak 1
    //gen_square(1000, 1.0, 0.02, 50, 25, tempBuffer);

    // Zadatak 2
    //gen_white_noise(1000, 0.6, tempBuffer);

    // Zadatak 3
    //gen_triangle(1000, 1.0, 0.02, 25, tempBuffer);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Task No.2 - 8 bit sound generator
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Create current tone pointer for each sine generator
	tone_t* current_tone_ch0 = superMarioTriangle;
	tone_t* current_tone_ch1 = superMarioWhiteNoise;
	tone_t* current_tone_ch2 = superMarioSquare30;
	tone_t* current_tone_ch3 = superMarioSquare50;

    // Loop through entire song
	for(i=0; i<superMarioThemeLength; i++)
	{
		int k;

		// Set output buffer to silence
		// TO DO
		for(k = 0; k < BLOCK_SIZE; k++)
		{
			outputBuffer[k] = 0;
		}

		// If current tone 0 timestamp is less than or equals current moment (i)
		if( current_tone_ch0->time <= i)
		{
			// Generate triangle wave using frequency of a current tone
			// Phase is number of samples passed since tone has started playing
			// Amplitude is 1.0
			// TO DO
			float frequency = note_to_freq(current_tone_ch0->note)/SAMPLE_RATE;
			Int16 phase = (i-current_tone_ch0->time) * BLOCK_SIZE;
			gen_triangle(BLOCK_SIZE, 1.0, frequency, phase, tempBuffer);

			// copy of original tone for SNR calculation
			/*
			for(k = 0; k < BLOCK_SIZE; k++)
			{
				tone[k] = tempBuffer[k];
			}*/

			// Pass tone through ADSR unit
			// TO DO
			Int16 duration = current_tone_ch0->duration * BLOCK_SIZE;
			ADSR(tempBuffer, BLOCK_SIZE, phase, duration);

			// Perform quantization/clipping of generated signal
			// Add the result to outputBuffer
			// TO DO
			for(k = 0; k < BLOCK_SIZE; k++)
			{
				outputBuffer[k] += clipB(quantB(tempBuffer[k], 15), 14);
			}

			// SNR calculation
			/*for(k = 0; k < BLOCK_SIZE; k++)
			{
				noise[k] = (outputBuffer[k] - tone[k]);
			}

			float SNR = calculate_snr(tone, noise, BLOCK_SIZE);
			printf("Tone: %s, Freq: %.4f(%.2fHz), SNR: %f\n", note_to_string(current_tone_ch0->note), frequency, frequency*SAMPLE_RATE, SNR);
			*/

			// If current tone is finished, increment current tone ptr
			if((i - current_tone_ch0->time) >= (current_tone_ch0->duration - 1))
			{
				current_tone_ch0++;
			}
		}

		// If current tone 1 timestamp is less than or equals current moment (i)
		if( current_tone_ch1->time <= i)
		{
			// Generate white noise
			// Amplitude is 1.0
			// TO DO
			gen_white_noise(BLOCK_SIZE, 1.0, tempBuffer);

			// Pass tone through ADSR unit
			// TO DO
			Int16 phase = (i-current_tone_ch1->time) * BLOCK_SIZE;
			Int16 duration = current_tone_ch1->duration * BLOCK_SIZE;
			ADSR(tempBuffer, BLOCK_SIZE, phase, duration);

			// Perform quantization/clipping of generated signal
			// Add the result to outputBuffer
			// TO DO

			for(k = 0; k < BLOCK_SIZE; k++)
			{
				outputBuffer[k] += quantB(tempBuffer[k], 12);
			}

			// If current tone is finished, increment current tone ptr
			if((i - current_tone_ch1->time) >= (current_tone_ch1->duration - 1))
			{
				current_tone_ch1++;
			}
		}

		// If current tone 2 timestamp is less than or equals current moment (i)
		if( current_tone_ch2->time <= i)
		{
			// Generate square wave using frequency of a current tone, and duty cycle 30%
			// Phase is number of samples passed since tone has started playing
			// Amplitude is 1.0
			// TO DO
			float frequency = note_to_freq(current_tone_ch2->note)/SAMPLE_RATE;
			Int16 phase = (i-current_tone_ch2->time) * BLOCK_SIZE;
			gen_square(BLOCK_SIZE, 1.0, frequency, 50, phase, tempBuffer);

			// Pass tone through ADSR unit
			// TO DO
			Int16 duration = current_tone_ch2->duration * BLOCK_SIZE;
			ADSR(tempBuffer, BLOCK_SIZE, phase, duration);

			// Perform quantization/clipping of generated signal
			// Add the result to outputBuffer
			// TO DO
			for(k = 0; k < BLOCK_SIZE; k++)
			{
				outputBuffer[k] += quantB(tempBuffer[k], 14);
			}

			// If current tone is finished, increment current tone ptr
			if((i - current_tone_ch2->time) >= (current_tone_ch2->duration - 1))
			{
				current_tone_ch2++;
			}
		}


		// If current tone 3 timestamp is less than or equals current moment (i)
		if( current_tone_ch3->time <= i)
		{
			// Generate square wave using frequency of a current tone, and duty cycle 50%
			// Phase is number of samples passed since tone has started playing
			// Amplitude is 1.0
			// TO DO
			float frequency = note_to_freq(current_tone_ch3->note)/SAMPLE_RATE;
			Int16 phase = (i-current_tone_ch3->time) * BLOCK_SIZE;
			gen_square(BLOCK_SIZE, 1.0, frequency, 30, phase, tempBuffer);

			// Pass tone through ADSR unit
			// TO DO
			Int16 duration = current_tone_ch3->duration * BLOCK_SIZE;
			ADSR(tempBuffer, BLOCK_SIZE, phase, duration);

			// Perform quantization/clipping of generated signal
			// Add the result to outputBuffer
			// TO DO
			for(k = 0; k < BLOCK_SIZE; k++)
			{
				outputBuffer[k] += quantB(tempBuffer[k], 14);
			}

			// If current tone is finished, increment current tone ptr
			if((i - current_tone_ch3->time) >= (current_tone_ch3->duration - 1))
			{
				current_tone_ch3++;
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

