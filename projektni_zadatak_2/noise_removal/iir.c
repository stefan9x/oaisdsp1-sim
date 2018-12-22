#include "iir.h"

/**************************************
 * IIR filtar prvog reda
 *
 * input - ulazni odbirak
 * coefficients - koeficijenti [a0 a1 b0 b1]
 * z_x - memorija za ulazne odbirke (niz duzine 2)
 * z_y - memorija za izlazne odbirke (niz duzine 2)
 *
 * povratna vrednost - izlazni odbirak
 *
 **************************************/

Int16 first_order_IIR(Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y) {
	Int32 temp;

	z_x[0] = input; /* Copy input to x[0] */

	temp = ((Int32) coefficients[0] * z_x[0]); /* B0 * x(n)     */
	temp += ((Int32) coefficients[1] * z_x[1]); /* B1 * x(n-1) */
	temp -= ((Int32) coefficients[3] * z_y[1]); /* A1 * y(n-1) */

	/* Divide temp by coefficients[A0] to remove fractional part */
	temp >>= 15;

	z_y[0] = (Int16) (temp);

	/* Range limit temp between maximum and minimum */

	if (temp > 32767) {
		temp = 32767;
	} else if (temp < -32767) {
		temp = -32767;
	}

	/* Shuffle values along one place for next time */

	z_y[1] = z_y[0]; /* y(n-1) = y(n)   */
	z_x[1] = z_x[0]; /* x(n-1) = x(n)   */

	return ((Int16) temp);
}

/**************************************
 * IIR filtar drugog reda
 *
 * input - ulazni odbirak
 * coefficients - koeficijenti [a0 a1/2 a2 b0 b1/2 b2]
 * z_x - memorija za ulazne odbirke (niz duzine 3)
 * z_y - memorija za izlazne odbirke (niz duzine 3)
 *
 * povratna vrednost - izlazni odbirak
 *
 * NAPOMENA: Koeficijenti b1 i a1 se nalaze u opsegu [-2, 2),
 * stoga se prosledjuje polovina njihove vrednosti kako bi
 * mogli biti prezentovani u 1.31 prezentaciji brojeva u
 * nepokretnom zarezu
 *************************************/

Int16 second_order_IIR(Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y) {
	Int32 temp;

	z_x[0] = input; /* Copy input to x[0] */

	temp = ((Int32) coefficients[0] * z_x[0]); /* B0 * x(n)     */
	temp += ((Int32) coefficients[1] * z_x[1]); /* B1/2 * x(n-1) */
	temp += ((Int32) coefficients[1] * z_x[1]); /* B1/2 * x(n-1) */
	temp += ((Int32) coefficients[2] * z_x[2]); /* B2 * x(n-2)   */
	temp -= ((Int32) coefficients[4] * z_y[1]); /* A1/2 * y(n-1) */
	temp -= ((Int32) coefficients[4] * z_y[1]); /* A1/2 * y(n-1) */
	temp -= ((Int32) coefficients[5] * z_y[2]); /* A2 * y(n-2)   */

	/* Divide temp by 2^15 to remove fractional part */
	temp >>= 15;

	/* Range limit temp between maximum and minimum */

	if (temp > 32767) {
		temp = 32767;
	} else if (temp < -32767) {
		temp = -32767;
	}

	z_y[0] = (Int16) (temp);

	/* Shuffle values along one place for next time */

	z_y[2] = z_y[1]; /* y(n-2) = y(n-1) */
	z_y[1] = z_y[0]; /* y(n-1) = y(n)   */
	z_x[2] = z_x[1]; /* x(n-2) = x(n-1) */
	z_x[1] = z_x[0]; /* x(n-1) = x(n)   */

	return ((Int16) temp);
}

Int16 fourth_order_IIR(Int16 input, Int16 coefficients[][6], Int16 z_x[][3],
		Int16 z_y[][3]) {
	Int32 temp = 0;

	/* Copy input to temp */

	/* for two stages */

		/* Copy input to x[stages][0] */

		/* B0 * x(n)     */

		/* B1/2 * x(n-1) */

		/* B1/2 * x(n-1) */

		/* B2 * x(n-2)   */

		/* A1/2 * y(n-1) */

		/* A1/2 * y(n-1) */

		/* A2 * y(n-2)   */

		/* Divide temp by 2^15 to remove fractional part */

		/* Range limit temp between maximum and minimum */

		/* Shuffle values along one place for next time */

		/* y(n-2) = y(n-1) */
		/* y(n-1) = y(n)   */

		/* x(n-2) = x(n-1) */
		/* x(n-1) = x(n)   */

		/* temp is used as input next time through */

	/* End loop */

	return (Int16)temp;
}

