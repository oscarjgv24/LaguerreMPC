#ifndef EKF_H
#define EKF_H
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"

extern float EKF(float P[16], const float Psi[4], float Theta[4], float Yk,
                 float k, float q, float r, signed char ini);
extern void EKF_initialize(void);
extern void EKF_terminate(void);

#endif
