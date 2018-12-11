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
#include "iir.h"
// Zadatak 1
#include "IIR_low_pass_filters.h"

// Zadatak 2
#include "IIR_high_pass_filters.h"
#include "IIR_band_pass_filters.h"

// Zadatak 3
//#include "IIR_all_pass_filters.h"

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

#define SAMPLES_PER_SECOND 48000
#define GAIN_IN_dB 0

Int16 ImpulseBuffer[AUDIO_IO_SIZE];
Int16 Impulse[AUDIO_IO_SIZE];
// Zadatak 1,3
Int16 xhist_imp[2];
Int16 yhist_imp[2];
/*Int16 xhist[2];
Int16 yhist[2];*/

// Zadatak 2, 4
/*Int16 xhist_imp[2][2];
Int16 yhist_imp[2][2];
Int16 xhist[2][2];
Int16 yhist[2][2];
Int16 xhistR[3][2];
Int16 yhistR[3][2];*/

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

	aic3204_set_input_filename("../signal1.pcm");
	aic3204_set_output_filename("../output1.pcm");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);

    Impulse[0] = 16000;

    for (i = 1; i < AUDIO_IO_SIZE; i++)
    {
    	Impulse[i] = 0;
    }

    for (i = 0; i<2; i++)
    {
    	// Zadatak 1,3
    	/*xhist[i] = 0;
    	yhist[i] = 0;*/
    	xhist_imp[i] = 0;
		yhist_imp[i] = 0;

    	// Zadatak 2,4
    	/*for (j = 0; j<2; j++)
    	{
			xhist_imp[i][j] = 0;
			yhist_imp[i][j] = 0;
			xhist[i][j] = 0;
			yhist[i][j] = 0;
			xhistR[i][j] = 0;
			yhistR[i][j] = 0;
			xhistR[3][j] = 0;
			yhistR[3][j] = 0;
    	}*/
    }

	/* Loop 10s */
	for(i=0; i<SAMPLES_PER_SECOND/AUDIO_IO_SIZE*10L; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);
		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			// Zadatak 1
			/*ImpulseBuffer[j] = second_order_IIR(Impulse[j], IIR_low_pass_5000Hz_2nd_order, xhist_imp, yhist_imp);
			OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_low_pass_5000Hz_2nd_order, xhist, yhist);
			OutputBufferR[j] = InputBufferR[j];*/

			// Zadatak 2
			/*ImpulseBuffer[j] = fourth_order_IIR(Impulse[j], IIR_low_pass_5000Hz_4th_order, xhist_imp, yhist_imp);
			OutputBufferL[j] = fourth_order_IIR(InputBufferL[j], IIR_low_pass_5000Hz_4th_order, xhist, yhist);*/

			/*ImpulseBuffer[j] = fourth_order_IIR(Impulse[j], IIR_high_pass_12000Hz_4th_order, xhist_imp, yhist_imp);
			OutputBufferL[j] = fourth_order_IIR(InputBufferL[j], IIR_high_pass_12000Hz_4th_order, xhist, yhist);*/

			/*ImpulseBuffer[j] = fourth_order_IIR(Impulse[j], IIR_band_pass_5kHz_12kHz_4th_order, xhist_imp, yhist_imp);
			OutputBufferL[j] = fourth_order_IIR(InputBufferL[j], IIR_band_pass_5kHz_12kHz_4th_order, xhist, yhist);*/

			// Zadatak 3
			/*ImpulseBuffer[j] = second_order_IIR(Impulse[j], IIR_all_pass_2nd_order, xhist_imp, yhist_imp);
			OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_all_pass_2nd_order, xhist, yhist);*/

			// Zadatak 4
			/*ImpulseBuffer[j] = Nth_order_IIR(Impulse[j], IIR_low_pass_5000Hz_4th_order, xhist_imp, yhist_imp, 4);
			OutputBufferL[j] = Nth_order_IIR(InputBufferL[j], IIR_low_pass_5000Hz_4th_order, xhist, yhist, 4);
			OutputBufferR[j] = Nth_order_IIR(InputBufferR[j], IIR_low_pass_5000Hz_6th_order, xhistR, yhistR, 6);*/

			// Zadatak 5
			//ImpulseBuffer[j] = halfband(Impulse[j], xhist_imp, yhist_imp, 0); //highpass
			ImpulseBuffer[j] = halfband(Impulse[j], xhist_imp, yhist_imp, 50); //lowpass
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

