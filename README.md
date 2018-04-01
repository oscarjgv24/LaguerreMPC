# LaguerreMPC
This Repository contains work related to the Laguerre MPC formulation presented in the paper "Laguerre-based Adaptive MPC for Attitude Stabilization of Quad-rotor".

The Matlab code "Test_Laguerre_MPC.m" calculates a Laguerre MPC using the formulation presented in the paper.

The Matlab code "VisualizeData.m" plots the data from the flight. 
The data is separated by commas and is given in this order 
  roll,pitch,yaw,roll rate,pitch rate,yaw rate,acceleration x,acceleration y,acceleration z
  Motor 1,2,3,4
  References (roll,pitch,yaw,roll rate,pitch rate,yaw rate)
  Parameters (roll,pitch,yaw)
  Gains (roll,pitch,yaw)
  
Finally, the repository contains a an "MPC" class that implements the formulation using automatically generated
C code.
