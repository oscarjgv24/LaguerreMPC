#ifndef LAGUERRE_MPC_H
#define LAGUERRE_MPC_H
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"

extern void Laguerre_MPC(const float A[16], const float B[4], const float C[4],
  float r0, const float L[100], float Kx[4]);
extern void Laguerre_MPC_initialize(void);
extern void Laguerre_MPC_terminate(void);

#endif
