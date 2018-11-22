#ifndef GEN_SINUS_H_
#define GEN_SINUS_H_

#include "tistdtypes.h"

////////////////////////////////////////////////////////////////////////////////////////////
// Generate sine wave using lookup table
// params:
//     - n - number of samples
//     - a - amplitude
//     - f - norm frequency (0 - 0.5)
//     - ph - current phase (NOTE: Current phase is given as a number of samples, not radians!!)
//     - buffer - output buffer
////////////////////////////////////////////////////////////////////////////////////////////
extern void gen_sinus_table(Int16 n, float a, float f, Int16 ph, float buffer[]);


#endif /* GEN_SINUS_H_ */
