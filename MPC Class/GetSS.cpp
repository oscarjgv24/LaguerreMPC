#include "GetSS.h"

void GetSS(const float Theta[3], float dt, float A[16], float B[4], float C[4])
{
  int i;
  signed char I[16];
  for (i = 0; i < 16; i++) {
    I[i] = 0;
  }

  for (i = 0; i < 4; i++) {
    I[i + (i << 2)] = 1;
  }

  for (i = 0; i < 16; i++) {
    A[i] = I[i];
  }

  for (i = 0; i < 4; i++) {
    B[i] = 0.0F;
    C[i] = 0.0F;
  }

  A[4] = dt * (1.0F + Theta[0]);
  A[8] = dt;
  A[5] = 1.0F + Theta[0];
  A[9] = 1.0F;
  B[0] = Theta[1] + Theta[2];
  B[1] = (Theta[1] + Theta[2]) / dt;
  B[3] = 1.0F;
  A[12] = Theta[1];
  A[13] = Theta[1] / dt;
  C[0] = 1.0F;
}

void GetSS_initialize(void)
{
}

void GetSS_terminate(void)
{
}
