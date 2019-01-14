//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Vezba 9 - Interpolacija i decimacija
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
//////////////////////////////////////////////////////////////////////////////

#include "tistdtypes.h"
#include <cstdio>
#include "ezdsp5535.h"
#include "math.h"
#include "signal.h"
#include "filter_coeff.h"
#include "processing.h"

Int16 outputBuffer[1024];
#define M 4
#define L 4

/*
 *
 *  main( )
 *
 */
void main( void )
{
	//Int16 i, j, k;

	printf("\n Vezba 9 - Interpolacija i decimacija \n");
	

	/*for(i = 0, j=0; i < N_COEFF; i+=M, j++)
	{
		for(k = 0; k < M; k++)
		{
			lp_filter_poly[k][j] = lp_filter[i+k];
		}
	}*/
	
		/* Your code here */
	// Zadatak 1
	//downsample(signal1, outputBuffer, M, SIGNAL1_LENGTH);

	// Zadatak 2
	//decimate(signal1, outputBuffer , M, SIGNAL1_LENGTH);

	// Zadatak 3
	//upsample(signal2, outputBuffer, L, SIGNAL2_LENGTH);

	// Zadatak 4
	//interpolate(signal2, outputBuffer, L, SIGNAL2_LENGTH);

	// Zadatak 5
	//resample(signal2, outputBuffer, 3, 4, SIGNAL2_LENGTH);
	//resample(signal2, outputBuffer, 4, 3, SIGNAL2_LENGTH);

	// Zaatak 6
	decimate_poly(signal1, outputBuffer, M, SIGNAL1_LENGTH);

	// Zadatak 7
	 // working

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

