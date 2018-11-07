//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Vezba 2 - Generisanje signala.
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include "ezdsp5535.h"
#include "math.h"
#include "gen_sinus.h"

#define PI 3.14159265

#define BUFFER_LENGTH 2048

float buffer[BUFFER_LENGTH];

/*
 *
 *  main( )
 *
 */
void main( void )
{

	printf("\n Vezba 2 - generisanje signala \n");

	/* Your code here */

	// Zadatak 1
	// gen_sinus(broj odbiraka, amplituda, frekvencija, fazni pomeraj, buffer)

	gen_sinus(1000, 10, 0.02, 0, buffer);
	gen_sinus(1000, 5, 0.05, PI/2, buffer);

	// Zadatak 2
	//gen_sinus_multiton(broj odbiraka, amplituda, pocetna frekvencija, udaljenost frekvencija, fazni pomeraj, buffer)

	gen_sinus_multiton(1000, 10, 0.05, 0.1, 0, buffer);
	gen_sinus_multiton(1000, 1, 0.1, 0.03, PI/2, buffer);

	// Zadatak 3
	//gen_log_sweep(broj odbiraka, amplituda, pocetna f, krajnja f, fazni pomeraj, buffer)

	gen_log_sweep(1000, 5, 0.01, 0.1, 0, buffer);
	gen_lin_sweep(1000, 5, 0.01, 0.1, 0, buffer);

	// Zadatak 4
	// gen_sinus_table(broj odbiraka, amplituda, frekvencija, fazni pomeraj, buffer)

	gen_sinus_table(1000, 10, 0.02, 0, buffer);
	gen_sinus_table(1000, 5, 0.05, PI/2, buffer);

	// Zadatak 5
	// gen_square(broj odbiraka, amplituda, frekvencija, faktor ispunjenosti, buffer)

	gen_square(1000, 10, 0.05, 50, buffer);

	// Zadatak 6
	// gen_sinus_table_mod(broj odbiraka, amplituda, frekvencija, fazni pomeraj, buffer)

	gen_sinus_table_mod(1000, 10, 0.02, 0, buffer);

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}
