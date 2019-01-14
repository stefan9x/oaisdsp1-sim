/*
 * filter_coeff.h
 *
 *  Created on: 29.02.2016.
 *      Author: Dejan Bokan (dejan.bokan@rt-rk.com)
 */

#ifndef VEZBA9_SIM_FILTER_COEFF_H_
#define VEZBA9_SIM_FILTER_COEFF_H_

#include "tistdtypes.h"

#define N_COEFF 21
#define N_COEFF_P 6
#define M_FACTOR 4
extern Int16 lp_filter[N_COEFF+4];
extern Int16 lp_filter_poly[M_FACTOR][N_COEFF_P];

#endif /* VEZBA9_SIM_FILTER_COEFF_H_ */

