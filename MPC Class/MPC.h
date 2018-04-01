#ifndef _MPC
#define _MPC
#include "GetSS.h"
#include "LQR.h"
#include "OSI.h"
#include "GetLaguerre.h"
#include "Laguerre_MPC.h"
const int Ndata=5;
class MPC{
  public:  
  float dt;
  float max_u_dist;
  float alpha_d;
  int NData=Ndata;
  float theta[3];
  float P[16];
  float A[16];
  float B[4];
  float C[4];
  float L[100];
  float r,a;
  float Kx[4];
  float X[4];
  float dist=0;
  float Outputs[Ndata];
  float Inputs[Ndata];
  float References[Ndata];
  OSI osi;
  float Psi[4];
  void begin(float theta[3],float r0, float a0, float dt0);  
  void get(int N);
  void move(float y,float u);
  void move_ref(float ref);
  void estimate_state();
  void form_state();
  void estimate_disturbance();
  void saturate_disturbance();
  float compute_control_action(float ref);
  void adapt();
  void update();
};
#endif