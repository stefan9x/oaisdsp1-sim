/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: Band Pass
Filter model: Rectangular Window
Sampling Frequency: 16 KHz
Fc1 and Fc2 Frequencies: 0.800000 KHz and 2.400000 KHz
Coefficents Quantization: 16-bit
***************************************************************/

#define Ntap 33

Int16 band_pass_33rd_order[Ntap] = {
		5335,
		 6688,
		 5009,
		 1252,
		-1969,
		-2348,
		  123,
		 2739,
		 1834,
		-4311,
		-13507,
		-20268,
		-18985,
		-7760,
		 9667,
		25428,
		31753,
		25428,
		 9667,
		-7760,
		-18985,
		-20268,
		-13507,
		-4311,
		 1834,
		 2739,
		  123,
		-2348,
		-1969,
		 1252,
		 5009,
		 6688,
		 5335
    };
