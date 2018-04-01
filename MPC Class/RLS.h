#ifndef RLS_H
#define RLS_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"

extern float RLS(float P[16], const float Psi[4], float Theta[4], float Yk,
                 float k, float lambda, float r, signed char ini);
extern void RLS_initialize(void);
extern void RLS_terminate(void);

#endif
