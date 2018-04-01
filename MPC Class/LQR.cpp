#include "LQR.h"

void LQR(float P[16], const float A[16], const float B[4], const float q[4],
         float R, unsigned char N, unsigned char ini, float Kx[4])
{
  int k;
  float Q[16];
  signed char I[16];
  unsigned char i;
  float c;
  float b_B[4];
  int i0;
  float b_c[4];
  float c_B[4];
  float b_A[4];
  float c_A[16];
  float d_A[16];
  int i1;
  if (ini == 1) {
    for (k = 0; k < 16; k++) {
      I[k] = 0;
    }

    for (k = 0; k < 4; k++) {
      I[k + (k << 2)] = 1;
    }

    for (k = 0; k < 16; k++) {
      P[k] = I[k];
    }
  }

  memset(&Q[0], 0, sizeof(float) << 4);
  for (k = 0; k < 4; k++) {
    Q[k + (k << 2)] = q[k];
  }

  for (i = 1; i <= N; i++) {
    c = 0.0F;
    for (k = 0; k < 4; k++) {
      b_B[k] = 0.0F;
      for (i0 = 0; i0 < 4; i0++) {
        b_B[k] += B[i0] * P[i0 + (k << 2)];
      }

      c += b_B[k] * B[k];
    }

    c = 1.0F / (R + c);
    for (k = 0; k < 4; k++) {
      b_c[k] = 0.0F;
      b_B[k] = 0.0F;
      for (i0 = 0; i0 < 4; i0++) {
        c_A[k + (i0 << 2)] = 0.0F;
        d_A[k + (i0 << 2)] = 0.0F;
        for (i1 = 0; i1 < 4; i1++) {
          c_A[k + (i0 << 2)] += A[i1 + (k << 2)] * P[i1 + (i0 << 2)];
          d_A[k + (i0 << 2)] += A[i1 + (k << 2)] * P[i1 + (i0 << 2)];
        }

        b_c[k] += d_A[k + (i0 << 2)] * B[i0];
        b_B[k] += B[i0] * P[i0 + (k << 2)];
      }

      b_A[k] = b_c[k] * c;
    }

    for (k = 0; k < 4; k++) {
      c_B[k] = 0.0F;
      for (i0 = 0; i0 < 4; i0++) {
        d_A[k + (i0 << 2)] = 0.0F;
        for (i1 = 0; i1 < 4; i1++) {
          d_A[k + (i0 << 2)] += c_A[k + (i1 << 2)] * A[i1 + (i0 << 2)];
        }

        c_B[k] += b_B[i0] * A[i0 + (k << 2)];
      }
    }

    for (k = 0; k < 4; k++) {
      for (i0 = 0; i0 < 4; i0++) {
        c_A[k + (i0 << 2)] = b_A[k] * c_B[i0];
      }
    }

    for (k = 0; k < 4; k++) {
      for (i0 = 0; i0 < 4; i0++) {
        P[i0 + (k << 2)] = (d_A[i0 + (k << 2)] - c_A[i0 + (k << 2)]) + Q[i0 + (k
          << 2)];
      }
    }
  }

  c = 0.0F;
  for (k = 0; k < 4; k++) {
    b_B[k] = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      b_B[k] += B[i0] * P[i0 + (k << 2)];
    }

    c += b_B[k] * B[k];
  }

  c = 1.0F / (R + c);
  for (k = 0; k < 4; k++) {
    b_B[k] = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      b_B[k] += c * B[i0] * P[i0 + (k << 2)];
    }
  }

  for (k = 0; k < 4; k++) {
    b_c[k] = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      b_c[k] += b_B[i0] * A[i0 + (k << 2)];
    }

    Kx[k] = b_c[k];
  }
}

void LQR_initialize(void)
{
}

void LQR_terminate(void)
{
}
