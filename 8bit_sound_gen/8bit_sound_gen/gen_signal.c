//////////////////////////////////////////////////////////////////////////////
// * File name: gen_signal.c
// *
// * Description: Generate Square Wave, White Noise and Triangle Wave
// * Course: OAiS DSP1
// * Year: 2018
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdlib.h>
#include "gen_signal.h"
#include <math.h>

#define PI 3.14159265


////////////////////////////////////////////////////////////////////////////////////////////
// Generate square wave
// params:
//     - n - number of samples
//     - a - amplitude
//     - f - norm frequency (0 - 0.5)
//     - D - Duty cycle (in percents [0%, 100%])
//     - ph - current phase (NOTE: Current phase is given as a number of samples, not radians!!)
//     - buffer - output buffer
////////////////////////////////////////////////////////////////////////////////////////////
void gen_square(Int16 n, float a, float f, float D, Int16 ph, float buffer[])
{
	// TO DO
	Int16 i = 0, j=ph;
	int T = 1/f;
	int Tmax = D*T/100;

	for(i = 0; i < n; i++)
	{
		if(j < Tmax)
		{
			buffer[i] = a;
		}
		else if(j < T)
		{
			buffer[i] = -a;
		}
		else
		{
			j = 0;
			buffer[i] = a;
		}
		j++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// Generate white noise
// params:
//     - n - number of samples
//     - a - amplitude
//     - buffer - output buffer
////////////////////////////////////////////////////////////////////////////////////////////
void gen_white_noise(Int16 n, float a, float buffer[])
{
	// TO DO
	Int16 i = 0;

	for(i = 0; i < n; i++)
	{
		float tmp = (float) rand() / 32767;

		if (i%2 == 0)
		{
			buffer[i] = a * tmp;
		}
		else
		{
			buffer[i] = -tmp * a;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// Generate triangle wave
// params:
//     - n - number of samples
//     - a - amplitude
//     - f - norm frequency (0 - 0.5)
//     - ph - current phase (NOTE: Current phase is given as a number of samples, not radians!!)
//     - buffer - output buffer
////////////////////////////////////////////////////////////////////////////////////////////
void gen_triangle(Int16 n, float a, float f, Int16 ph, float buffer[])
{
	// TO DO
	Int16 i = 0;
	int T = 1/f;

	for(i = 0; i < n; i++)
	{
		buffer[i] = (4 * a) / T *(abs((i + ph) % T - T / 2) - T / 4);
	}
}
