
#ifndef IIR_H
#define IIR_H

#include "tistdtypes.h"

Int16 first_order_IIR(Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y);

Int16 second_order_IIR( Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y);

Int16 fourth_order_IIR(Int16 input, Int16 coefficients[][6], Int16 z_x[][3], Int16 z_y[][3]);

#endif
