#include "GetLaguerre.h"

void GetLaguerre(float a, float L[100])
{
  int i0;
  float v[2];
  float A[4];
  float L0[2];
  float x;
  float b_L[100];
  int i;
  int i1;
  for (i0 = 0; i0 < 4; i0++) {
    A[i0] = 0.0F;
  }

  v[0] = a;
  L0[0] = 1.0F;
  v[1] = (float)pow(-a, 0.0) * (1.0F - a * a);
  L0[1] = -a;
  x = (float)sqrt(1.0F - a * a);
  for (i0 = 0; i0 < 2; i0++) {
    A[i0] = v[i0];
    L0[i0] *= x;
  }

  A[2] = 0.0F;
  A[3] = a;
  memset(&b_L[0], 0, 100U * sizeof(float));
  for (i0 = 0; i0 < 2; i0++) {
    b_L[i0] = L0[i0];
  }

  for (i = 0; i < 49; i++) {
    for (i0 = 0; i0 < 2; i0++) {
      v[i0] = 0.0F;
      for (i1 = 0; i1 < 2; i1++) {
        v[i0] += A[i0 + (i1 << 1)] * b_L[i1 + (i << 1)];
      }
    }

    for (i0 = 0; i0 < 2; i0++) {
      b_L[i0 + ((i + 1) << 1)] = v[i0];
    }
  }

  for (i0 = 0; i0 < 2; i0++) {
    for (i1 = 0; i1 < 50; i1++) {
      L[i1 + 50 * i0] = b_L[i0 + (i1 << 1)];
    }
  }
}

void GetLaguerre_initialize(void)
{
}

void GetLaguerre_terminate(void)
{
}
