/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Band Pass
Filter model: Chebyshev
Filter order: 1
Sampling Frequency: 16 KHz
Fc1 and Fc2 Frequencies: 0.800000 KHz and 2.400000 KHz
Pass band Ripple: 1.000000 dB
Coefficents Quantization: 16-bit

Koeficijente za IIR filter drugog reda generisete tako da u WinFilter programu
za "order" stavite za jedan manje od reda koji vama treba.

Zatim prekopirate keoficijente ovim redoslijedom:
A[0], A[1], A[2], B[0], B[1], B[2]

ali tako da vrijednosti A[1] i B[1] podijelite sa 2, i upisete ovde.
** Ovo vazi za brojeve koji su >=21954

Ako se pojavi vrijednosti 32768, smanjite je za 1 (32767)
***************************************************************/

Int16 IIR_band_pass_2nd_order[6] = {29776, 0, -29776,
		16384, -17011, 3614};
