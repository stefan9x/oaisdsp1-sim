#ifndef VEZBA2_SIM_GEN_SINUS_H_
#define VEZBA2_SIM_GEN_SINUS_H_

extern void gen_sinus(int n, float a, float f, float ph, float buffer[]);

extern void gen_sinus_table(int n, float a, float f, float ph, float buffer[]);

extern void gen_sinus_table_mod(int n, float a, float f, float ph, float buffer[]);

extern void gen_sinus_multiton(int n, float a, float f0, float df, float ph, float buffer[]);

extern void gen_lin_sweep(int n, float a, float f1, float f2, float ph, float buffer[]);

extern void gen_log_sweep(int n, float a, float f1, float f2, float ph, float buffer[]);

extern void gen_square(int n, float a, float f, float D, float buffer[]);

#endif /* VEZBA2_SIM_GEN_SINUS_H_ */
