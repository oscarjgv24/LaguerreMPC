#include "OSI.h"

void OSI::begin(float k, float q, float r){
  k0=k;
  q0=q;
  r0=r;
  float psi[4]={0,0,0,0};
  float Yk=0;
  trace=RLS(P,psi,theta,Yk,k0,q0,r0,1);
}

void OSI::tune(float parameters[3]){
  k0=parameters[0];
  q0=parameters[1];
  if(q0<0.99)q0=0.99;
  if(q0>1)q0=1;
  r0=parameters[2];
}

void OSI::run(float psi[4],float Yk){
  //Execution rules (information related)
  if(abs(psi[0])>3)trace=RLS(P,psi,theta,Yk,k0,q0,r0,0);
  //Parameter rule (time constant)
  if(theta[0]>0)theta[0]=0;
  if(theta[0]<-0.7)theta[0]=-0.7;
  //Parameter rule (gain)
  if(theta[1]>0.3)theta[1]=0.3;
  if(theta[1]<0.001)theta[1]=0.001;
  //Parameter rule (gain)
  if(theta[2]>0.3)theta[2]=0.3;
  if(theta[2]<0)theta[2]=0;
}
