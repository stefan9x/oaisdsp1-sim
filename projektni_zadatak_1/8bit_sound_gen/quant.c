#include <math.h>
#include "tistdtypes.h"

Int16 quantB(float input, Uint16 B)
{
	/* Maximum value represented with B bits is 2^(B-1)-1 if we use sign integers */
	float max_amp = (1L << (B - 1));
	/* Our interval is [-max_amp, max_amp) */
	float output_float = floor(input * max_amp+0.5);

	if(output_float == max_amp)
		output_float = max_amp-1;
	/* Convert from float to Int16 */
	Int16 output_int = output_float;
	return output_int;
}

float reconstructB(Int16 input, Uint16 B)
{
	float max_amp = (1L << 15);
	float input_float = input << (16-B);
	float output = input_float / max_amp;
	return output; 
}


float snr(float* signal, float* noise, Uint16 n)
{
	// TO DO

	return 0.0;
}


Int16 clipB(Int16 input, Uint16 B)
{
	Int16 max = (1L << (B-1)) - 1;
	Int16 min = - max;
	Int16 output = input;
	if(output > max)
		output = max;
	else if (output < min)
		output = min;

	return output;
}



