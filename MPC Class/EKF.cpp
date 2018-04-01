#include "EKF.h"

float EKF(float P[16], const float Psi[4], float Theta[4], float Yk, float k,
          float q, float r, signed char ini)
{
  float k_tr;
  int b_k;
  float max_diag;
  signed char I[16];
  float f0;
  float B;
  float b_Psi[4];
  int i0;
  float K[4];
  float b_P[16];
  float b_K[16];
  int i1;
  if (ini == 1) {
    for (b_k = 0; b_k < 16; b_k++) {
      I[b_k] = 0;
    }

    for (b_k = 0; b_k < 4; b_k++) {
      I[b_k + (b_k << 2)] = 1;
    }

    for (b_k = 0; b_k < 16; b_k++) {
      P[b_k] = I[b_k];
    }
  }

  max_diag = 0.0F;
  for (b_k = 0; b_k < 4; b_k++) {
    if (P[b_k + (b_k << 2)] > max_diag) {
      max_diag = P[b_k + (b_k << 2)];
    }
  }

  f0 = 0.0F;
  for (b_k = 0; b_k < 4; b_k++) {
    B = P[b_k + (b_k << 2)] / max_diag;
    P[b_k + (b_k << 2)] += q * (B * B);
    f0 += Psi[b_k] * Theta[b_k];
  }

  max_diag = Yk - f0;
  f0 = 0.0F;
  for (b_k = 0; b_k < 4; b_k++) {
    b_Psi[b_k] = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      b_Psi[b_k] += Psi[i0] * P[i0 + (b_k << 2)];
    }

    f0 += b_Psi[b_k] * Psi[b_k];
  }

  B = r + f0;
  for (b_k = 0; b_k < 4; b_k++) {
    f0 = 0.0F;
    for (i0 = 0; i0 < 4; i0++) {
      f0 += P[b_k + (i0 << 2)] * Psi[i0];
    }

    K[b_k] = f0 / B;
    Theta[b_k] += K[b_k] * max_diag;
    for (i0 = 0; i0 < 4; i0++) {
      b_K[b_k + (i0 << 2)] = K[b_k] * Psi[i0];
    }

    for (i0 = 0; i0 < 4; i0++) {
      f0 = 0.0F;
      for (i1 = 0; i1 < 4; i1++) {
        f0 += b_K[b_k + (i1 << 2)] * P[i1 + (i0 << 2)];
      }

      b_P[b_k + (i0 << 2)] = P[b_k + (i0 << 2)] - f0;
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
    B = k / k_tr;
    for (b_k = 0; b_k < 16; b_k++) {
      P[b_k] *= B;
    }
  }

  return k_tr;
}

void EKF_initialize(void)
{
}

void EKF_terminate(void)
{
}
