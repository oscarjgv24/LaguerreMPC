#include "RLS.h"

float RLS(float P[16], const float Psi[4], float Theta[4], float Yk, float k,
          float lambda, float r, signed char ini)
{
  float k_tr;
  float y;
  int b_k;
  static const signed char b[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    1 };

  float e_k;
  float B;
  float b_Psi[4];
  int i0;
  float K[4];
  float b_P[16];
  float b_K[16];
  int i1;
  if (ini == 1) {
    y = k / 4.0F;
    for (b_k = 0; b_k < 16; b_k++) {
      P[b_k] = y * (float)b[b_k];
    }
  }

  y = 0.0F;
  for (b_k = 0; b_k < 4; b_k++) {
    y += Psi[b_k] * Theta[b_k];
  }

  e_k = Yk - y;
  y = 0.0F;
  for (b_k = 0; b_k < 4; b_k++) {
    b_Psi[b_k] = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      b_Psi[b_k] += Psi[i0] * P[i0 + (b_k << 2)];
    }

    y += b_Psi[b_k] * Psi[b_k];
  }

  B = r + y;
  for (b_k = 0; b_k < 4; b_k++) {
    y = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      y += P[b_k + (i0 << 2)] * Psi[i0];
    }

    K[b_k] = y / B;
    Theta[b_k] += K[b_k] * e_k;
    for (i0 = 0; i0 < 4; i0++) {
      b_K[b_k + (i0 << 2)] = K[b_k] * Psi[i0];
    }

    for (i0 = 0; i0 < 4; i0++) {
      y = 0.0F;
      for (i1 = 0; i1 < 4; i1++) {
        y += b_K[b_k + (i1 << 2)] * P[i1 + (i0 << 2)];
      }

      b_P[b_k + (i0 << 2)] = (P[b_k + (i0 << 2)] - y) / lambda;
    }
  }

  for (b_k = 0; b_k < 4; b_k++) {
    for (i0 = 0; i0 < 4; i0++) {
      P[i0 + (b_k << 2)] = b_P[i0 + (b_k << 2)];
    }
  }

  k_tr = 0.0F;
  for (b_k = 0; b_k < 4; b_k++) {
    k_tr += P[b_k + (b_k << 2)];
  }

  if (k_tr > k) {
    y = k / k_tr;
    for (b_k = 0; b_k < 16; b_k++) {
      P[b_k] *= y;
    }
  }

  return k_tr;
}

void RLS_initialize(void)
{
}

void RLS_terminate(void)
{
}
