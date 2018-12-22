/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*   ADSR.c                                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*    TO DO                                                                  */
/*                                                                           */
/*   Author  : Dejan Bokan                                                   */
/*                                                                           */
/*****************************************************************************/

#include "tistdtypes.h"


const int attack = 220;
const int decay = 4410;
const float sustain = 0.3;
const int release = 3087;

void ADSR(float buffer[], Int16 n, Int16 current_offset, Int16 tone_duration)
{
	int i;
	int j = 0;
	for(i = current_offset; i < attack; i++ )
	{
		buffer[j] *= ((float)i)/attack;
		j++;
		if(j >= n)
			return;
	}

	for(i = j + current_offset ; i < (attack+decay); i++ )
	{
		buffer[j] *= 1.0 - ((i-attack)*(1.0-sustain))/decay;
		j++;
		if(j >= n)
			return;
	}

	for(i = j + current_offset ; i < (tone_duration-release); i++ )
	{
		buffer[j] *= sustain;
		j++;
		if(j >= n)
			return;
	}

	for(i = j+current_offset ; i < tone_duration; i++)
	{
		buffer[j] *= sustain - (i-(tone_duration-release))*sustain/release;
		j++;
		if(j >= n)
			return;
	}
}


