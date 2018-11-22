#ifndef QUANT_H_
#define QUANT_H_

extern Int16 quantB(float input, Uint16 B);
extern float reconstructB(Int16 input, Uint16 B);

extern float snr(float* signal, float* noise, Uint16 n);

extern Int16 clipB(Int16 input, Uint16 B);
extern Int16 wrapAroundB(Int16 input, Uint16 B);

#endif /*QUANT_H_*/
