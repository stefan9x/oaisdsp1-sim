#include "tistdtypes.h"

void convolution(Int16* x, Uint16 xLength, Int16* h, Uint16 hLength, Int16* output )
{
	/* Your code here */
	int n, k;

	Int32 y;

	for (n = 0; n < xLength; n++)
	{
		y = 0;

		for (k = 0; k < hLength; k++)
		{
			if ( n < k) break;
			y = _smac(y, x[n - k], h[k]);
		}

		output[n] = y >> 16;
	}
}
