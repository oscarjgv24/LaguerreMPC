#ifndef LQR_H
#define LQR_H
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"

extern void LQR(float P[16], const float A[16], const float B[4], const float q
                [4], float R, unsigned char N, unsigned char ini, float Kx[4]);
extern void LQR_initialize(void);
extern void LQR_terminate(void);

#endif
