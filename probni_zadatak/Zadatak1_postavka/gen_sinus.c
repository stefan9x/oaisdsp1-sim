#include <stdint.h>
#include <stdlib.h>
#include "gen_sinus.h"
#include "sine_table.h"
#include <math.h>

#define PI 3.14159265

////////////////////////////////////////////////////////////////////////////////////////////
// Generate sine wave using lookup table
// params:
//     - n - number of samples
//     - a - amplitude
//     - f - norm frequency (0 - 0.5)
//     - ph - current phase (NOTE: Current phase is given as a number of samples, not radians!!)
//     - buffer - output buffer
////////////////////////////////////////////////////////////////////////////////////////////
void gen_sinus_table(Int16 n, float a, float f, Int16 ph, float buffer[])
{
	// TO DO
	Int16 i=0;
	Int16 delta = f * SINE_TABLE_SIZE;
	Int16 mask = SINE_TABLE_SIZE - 1;
	Int16 k = (Int16)(((Int32)ph*delta) & mask);

	for (i=0; i<n; i++)
	{
		k = k & mask;

		if (i <= SINE_TABLE_SIZE/4)
		{
			buffer[i] = a*p_sine_table[k];
		}

		else if(k <= SINE_TABLE_SIZE/2)
		{
			buffer[i] = a*p_sine_table[SINE_TABLE_SIZE/2 - k];
		}

		else if (k <= 3*SINE_TABLE_SIZE/4)
		{
			buffer[i] = -a*p_sine_table[k - SINE_TABLE_SIZE/2];
		}

		else
		{
			buffer[i] = -a*p_sine_table[SINE_TABLE_SIZE - k];
		}

		k+=delta;
	}
}

