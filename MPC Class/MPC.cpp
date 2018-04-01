#include "MPC.h"
void MPC::begin(float theta0[3],float r0, float a0, float dt0) {
  for(int i=0;i<3;i++){
    theta[i]=theta0[i];
    osi.theta[i]=0;
  }
  osi.theta[3]=0;
  dt=dt0;
  r=r0;
  a=a0;
  GetLaguerre(a,L);
  GetSS(theta,dt,A,B,C);
  // LQR(P,A,B,C,r,100,1,Kx);
  Laguerre_MPC(A,B,C,r,L,Kx);
}

void MPC::move(float y, float u) {
  for (int i = NData - 1; i > 0; i--) {
    Outputs[i] = Outputs[i - 1];
    Inputs[i] = Inputs[i - 1];
  }
  Outputs[0] = y;
  Inputs[0] = u;
}

void MPC::move_ref(float ref){
  for (int i = NData - 1; i > 0; i--) {
    References[i] = References[i - 1];
  }
  References[0] = ref;
}

void MPC::get(int N) {
  // LQR(P,A,B,C,r,N,1,Kx);
  Laguerre_MPC(A,B,C,r,L,Kx);
}

void MPC::estimate_disturbance(){
  dist = alpha_d * dist;
  dist += (1 - alpha_d) * (Outputs[0] - (2+theta[0]) * Outputs[1] +(1+theta[0]) * Outputs[2] - theta[1] * Inputs[0]-theta[2]*(Inputs[0]-Inputs[1]));
  saturate_disturbance();
}

void MPC::form_state() {
  X[0]=Outputs[0];
  X[1]=(Outputs[0]-Outputs[1])/dt;
  X[2] = dist/dt;
  X[3] = Inputs[0];
}

void MPC::saturate_disturbance() {
  float u_dist = dist/dt * Kx[2];
  if (u_dist > max_u_dist) {
    dist = max_u_dist*dt / Kx[2];
  }
  if (u_dist < -max_u_dist) {
    dist = -max_u_dist*dt / Kx[2];
  }
}

float MPC::compute_control_action(float ref) {
  move_ref(ref);
  float U = Inputs[0];
  for (int i = 0; i < 4 ; i++) {
    U -= Kx[i] * X[i];
  }
  U += Kx[0] * ref;
  U += Kx[1] * (References[0]-References[1])/dt;
  return U;
}

void MPC::adapt(){
  Psi[0]=Outputs[1]-Outputs[2];
  Psi[1]=Inputs[0];
  Psi[2]=0;
  Psi[3]=1;
  osi.P[10]=0;
  float y = Outputs[0]-2*Outputs[1]+Outputs[2];
  osi.run(Psi, y);
}

void MPC::update(){
  for(int i=0;i<3;i++){
    theta[i]=osi.theta[i];
  }
  GetSS(osi.theta,dt,A,B,C);
}