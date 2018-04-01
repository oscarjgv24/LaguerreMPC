#ifndef _OSI
#define _OSI
#include "EKF.h"
#include "RLS.h"
class OSI{
  public:
  float trace;
  float k0=10;
  float r0=1;
  float q0=0.995;
  float P[16];
  float theta[4];
  void begin(float k,float q, float r);
  void run(float psi[4],float y);
  void tune(float parameters[3]);
};
#endif