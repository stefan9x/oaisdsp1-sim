/*
 * processing.c
 *
 *  Created on: 29.02.2016.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.com)
 */

#include "processing.h"
#include "fir.h"
#include "filter_coeff.h"

void downsample(Int16 *input, Int16 *output, int M, int N)
{
	Int16 i, j;

	for(i = 0, j = 0; i< N; i += M, j++)
	{
		output[j] = input[i];
	}
}

static Int16 filtered[1024] ={0};
static Int16 history2[N_COEFF];
static Int16 history[M_FACTOR][N_COEFF_P] = {0};
static Uint16 state[M_FACTOR] = {0, 0};
static Uint16 state2= 0;

void decimate(Int16 *input, Int16 *output, int M, int N)
{
	Int16 i = 0;

	for(i = 0; i< N; i++)
	{
		filtered[i] = fir_circular(input[i], lp_filter, history2, N_COEFF, &state2);
	}
	downsample(filtered, output, M, N);
}

void decimate_poly(Int16 *input, Int16 *output, int M, int N)
{
	Int16 i = 0, j = 0, k = 0;
	for(j=0; j < N_COEFF_P;j++)
		{
			for(k = 0; k < M; k++)
			{
				history[k][j] = 0;
			}
		}

	for(i = 0, j=0; i < N_COEFF; i+=M, j++)
	{
		for(k = 0; k < M; k++)
		{
			lp_filter_poly[k][j] = lp_filter[i+k];
		}
	}

	output[0] = fir_circular(input[0], lp_filter_poly[0], history[0], N_COEFF_P, &state[0]);

	for(i = M, j = 1; i< N; i+=M, j++)
	{
		output[j] = fir_circular(input[i], lp_filter_poly[0], history[0], N_COEFF_P, &state[0]);
		for(k = 1; k < M; k++ )
		{
			output[j] += fir_circular(input[i-k], lp_filter_poly[k], history[k], N_COEFF_P, &state[k]);
		}
	}
}


void upsample(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */
	Int16 i, j, k;

	for(i = 0, j = 0; i < N; i++, j+=L)
	{
		output[j] = input[i];
		for(k = 1; k < L; k++){
			output[j+k] = 0;
		}
	}

}

void interpolate(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */
	//upsample
	upsample(input, filtered, L, N);

	//low_pass
	Int16 i = 0;

	for(i = 0; i < N * L; i++)
	{
		output[i] = fir_circular(filtered[i], lp_filter, history2, N_COEFF, &state2);
	}
}

void resample(Int16 *input, Int16 *output, int L, int M, int N)
{
	/* your code here... */
	Int16 i = 0;

	upsample(input, filtered, L, N);

	for(i = 0; i < N * L; i++)
	{
		filtered[i] = fir_circular(filtered[i], lp_filter, history2, N_COEFF, &state2);
	}

	downsample(filtered, output, M, N * L);


}

void interpolate_poly(Int16 *input, Int16 *output, int L, int N)
{
	/* your code here... */

	Int16 i = 0, j = 0, k = 0;
	for(j=0; j < N_COEFF_P;j++)
	{
		for(k = 0; k < L; k++)
		{
			history[k][j] = 0;
		}
	}

	for(i = 0; i < N; i++)
	{
		for(k = 0; k < L; k++)
		{
			output[i*L+k] = fir_circular(input[i], lp_filter_poly[k], history[k], N_COEFF_P, &state[k]);
		}
	}



}

