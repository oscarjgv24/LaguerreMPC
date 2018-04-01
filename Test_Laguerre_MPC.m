clear all
close all
clc
dt=single(0.02);
Theta=single([-0.2,0.1,0]);
[A,B,C]=GetSS(Theta,dt);
r0=single(0.1);
a=single(0.5);
L=GetLaguerre(a);
Kx=Laguerre_MPC(A,B,C,r0,L)