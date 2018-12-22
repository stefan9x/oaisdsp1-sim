/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Low Pass
Filter model: Butterworth
Filter order: 2
Sampling Frequency: 16 KHz
Cut Frequency: 2.400000 KHz
Coefficents Quantization: 16-bit

Redoslijed koeficijenata iz programa WinFilter:
A[0], A[1], A[2], B[0], B[1], B[2]

ali tako da vrijednosti A[1] i B[1] podijelite sa 2, i upisete ovde.
** Ovo vazi za brojeve koji su >=21954

Ako se pojavi vrijednosti 32768, smanjite je za 1 (32767)
***************************************************************/

Int16 IIR_low_pass_2nd_order[6] = {8592, 8592, 8592,
		32767, -12252, 8919};
