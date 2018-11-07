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
#include "string.h"

#define FS_48kHz 48000L
#define FS_24kHz 24000L
#define FS_16kHz 16000L
#define FS_8kHz 8000L

#define BUFFER_LENGTH 128
#define GAIN_IN_dB 0

Int16 left_input[BUFFER_LENGTH];
Int16 right_input[BUFFER_LENGTH];
Int16 left_output[BUFFER_LENGTH];
Int16 right_output[BUFFER_LENGTH];
Int16 buffer_48k[BUFFER_LENGTH];
Int16 buffer_24k[BUFFER_LENGTH];
Int16 buffer_16k[BUFFER_LENGTH];
Int16 buffer_8k[BUFFER_LENGTH];


typedef struct CircularBuffer_
{
	Int16 *data;
	Int16 read_indx;
	Int16 write_indx;
	size_t size;
} CircularBuffer;

CircularBuffer cbuf;

void circular_buffer_init(CircularBuffer* circular_buffer, Int16* buffer, size_t size)
{
	memset(buffer, 0, size*sizeof(Int16));
	circular_buffer->data = buffer;
	circular_buffer->size = size;
	circular_buffer->read_indx = 0;
	circular_buffer->write_indx = 0;
}

Int16 circular_buffer_read(CircularBuffer* circular_buffer)
{
	Int16 ret;
	if(circular_buffer->read_indx != circular_buffer->write_indx)
	{
		ret = circular_buffer->data[circular_buffer->read_indx];
		circular_buffer->read_indx++;
		circular_buffer->read_indx = circular_buffer->read_indx % (circular_buffer->size-1);
		return ret;
	}
	else
		return 0;
}

void circular_buffer_write(CircularBuffer* circular_buffer, Int16 value)
{
	circular_buffer->data[circular_buffer->write_indx] = value;
	circular_buffer->write_indx++;
	circular_buffer->write_indx = circular_buffer->write_indx % (circular_buffer->size-1);
	if(circular_buffer->read_indx == circular_buffer->write_indx)
	{
		circular_buffer->read_indx++;
		circular_buffer->read_indx = circular_buffer->read_indx % (circular_buffer->size-1);
	}
}

/*
 *
 *  main( )
 *
 */
void main( void )
{
	unsigned long int i = 0;
	unsigned long int j = 0;

    /* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Simulator loopback \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

	aic3204_set_input_filename("../dual_sine_6kHz_10kHz.pcm");
	aic3204_set_output_filename("../output48.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
	// Ne radi na simulatoru
    set_sampling_frequency_and_gain(FS_48kHz, GAIN_IN_dB);

	/* Loop 10s */
	for(i = 0; i < FS_48kHz/BUFFER_LENGTH * 10L; i++)
	{
		aic3204_read_block(left_input, right_input);

		for(j = 0; j < BUFFER_LENGTH; j++)
		{
			buffer_48k[j] = left_input[j];

			// Radjeno iz razloga sto simulator ne podrzava promjenu frekvencije odabiranja
			if (j < BUFFER_LENGTH / 6)
				buffer_8k[j] = left_input[j*6];

			else if (j < BUFFER_LENGTH / 3)
				buffer_16k[j] = left_input[j*3];

			else if (j < BUFFER_LENGTH / 2)
				buffer_24k[j] = left_input[j*2];
		}

		aic3204_write_block(buffer_48k, buffer_48k);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

