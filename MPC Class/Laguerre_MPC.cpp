#include "Laguerre_MPC.h"

static void mldivide(const float A[4], const float B[100], float Y[100]);
static void mldivide(const float A[4], const float B[100], float Y[100])
{
  int r1;
  int r2;
  float a21;
  float a22;
  int k;
  if ((float)fabs(A[1]) > (float)fabs(A[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  a21 = A[r2] / A[r1];
  a22 = A[2 + r2] - a21 * A[2 + r1];
  for (k = 0; k < 50; k++) {
    Y[1 + (k << 1)] = (B[r2 + (k << 1)] - B[r1 + (k << 1)] * a21) / a22;
    Y[k << 1] = (B[r1 + (k << 1)] - Y[1 + (k << 1)] * A[2 + r1]) / A[r1];
  }
}

void Laguerre_MPC(const float A[16], const float B[4], const float C[4], float
                  r0, const float L[100], float Kx[4])
{
  float G[200];
  float H[2500];
  float f0;
  int i0;
  short i;
  int b_i;
  float b_G[4];
  float H_data[49];
  float Hl[100];
  int i1;
  float E[4];
  float b_Hl[100];
  float fv0[8];
  memset(&G[0], 0, 200U * sizeof(float));
  memset(&H[0], 0, 2500U * sizeof(float));
  f0 = 0.0F;
  for (i0 = 0; i0 < 4; i0++) {
    G[50 * i0] = 0.0F;
    for (b_i = 0; b_i < 4; b_i++) {
      G[50 * i0] += C[b_i] * A[b_i + (i0 << 2)];
    }

    f0 += C[i0] * B[i0];
  }

  H[0] = f0;
  for (i = 0; i < 49; i++) {
    for (i0 = 0; i0 < 4; i0++) {
      b_G[i0] = 0.0F;
      for (b_i = 0; b_i < 4; b_i++) {
        b_G[i0] += G[i + 50 * b_i] * A[b_i + (i0 << 2)];
      }
    }

    for (i0 = 0; i0 < 4; i0++) {
      G[(i + 50 * i0) + 1] = b_G[i0];
    }

    f0 = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      f0 += G[i + 50 * i0] * B[i0];
    }

    H[i + 1] = f0;
  }

  for (i = 0; i < 49; i++) {
    b_i = 49 - i;
    for (i0 = 0; i0 < b_i; i0++) {
      H_data[i0] = H[i0];
    }

    b_i = 49 - i;
    for (i0 = 0; i0 < b_i; i0++) {
      H[((i + i0) + 50 * (i + 1)) + 1] = H_data[i0];
    }
  }

  for (i0 = 0; i0 < 50; i0++) {
    for (b_i = 0; b_i < 2; b_i++) {
      Hl[i0 + 50 * b_i] = 0.0F;
      for (i1 = 0; i1 < 50; i1++) {
        Hl[i0 + 50 * b_i] += H[i0 + 50 * i1] * L[i1 + 50 * b_i];
      }
    }
  }

  for (i0 = 0; i0 < 2; i0++) {
    for (b_i = 0; b_i < 2; b_i++) {
      E[i0 + (b_i << 1)] = 0.0F;
      for (i1 = 0; i1 < 50; i1++) {
        E[i0 + (b_i << 1)] += Hl[i1 + 50 * i0] * Hl[i1 + 50 * b_i];
      }
    }
  }

  for (b_i = 0; b_i < 2; b_i++) {
    E[b_i + (b_i << 1)] += r0;
  }

  for (i0 = 0; i0 < 50; i0++) {
    for (b_i = 0; b_i < 2; b_i++) {
      b_Hl[b_i + (i0 << 1)] = Hl[i0 + 50 * b_i];
    }
  }

  mldivide(E, b_Hl, Hl);
  for (i0 = 0; i0 < 2; i0++) {
    for (b_i = 0; b_i < 4; b_i++) {
      fv0[i0 + (b_i << 1)] = 0.0F;
      for (i1 = 0; i1 < 50; i1++) {
        fv0[i0 + (b_i << 1)] += Hl[i0 + (i1 << 1)] * G[i1 + 50 * b_i];
      }
    }
  }

  for (i0 = 0; i0 < 4; i0++) {
    Kx[i0] = 0.0F;
    for (b_i = 0; b_i < 2; b_i++) {
      Kx[i0] += L[50 * b_i] * fv0[b_i + (i0 << 1)];
    }
  }
}

void Laguerre_MPC_initialize(void)
{
}

void Laguerre_MPC_terminate(void)
{
}
