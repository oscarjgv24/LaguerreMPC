#ifndef GETSS_H
#define GETSS_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"

extern void GetSS(const float Theta[3], float dt, float A[16], float B[4], float
                  C[4]);
extern void GetSS_initialize(void);
extern void GetSS_terminate(void);

#endif
