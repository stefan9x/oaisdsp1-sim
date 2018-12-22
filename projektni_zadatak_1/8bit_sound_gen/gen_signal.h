#ifndef GEN_SIGNAL_H_
#define GEN_SIGNAL_H_

#include "tistdtypes.h"

void gen_square(Int16 n, float a, float f, float D, Int16 ph, float buffer[]);

void gen_white_noise(Int16 n, float a, float buffer[]);

void gen_triangle(Int16 n, float a, float f, Int16 ph, float buffer[]);

#endif /* GEN_SIGNAL_H_ */
