clear all
close all
clc
%Load Data
Data=load('FlightData_6_Mar_2018_5.txt');
[nd,md]=size(Data);
Nd=[1:nd];
%Select axis to work
sel=1;              %(1=roll, 2=pitch, 3=yaw)
%Select IMU data
Nimu=[1:9];
IMU_Data=Data(Nd,Nimu);
%Select Motors Data and allocate them
Nu=[10:13];
MOT_Data=Data(Nd,Nu);
L=1/4*(MOT_Data(:,2)+MOT_Data(:,4)-MOT_Data(:,1)-MOT_Data(:,3));
M=1/4*(MOT_Data(:,3)+MOT_Data(:,4)-MOT_Data(:,1)-MOT_Data(:,2));
N=1/4*(MOT_Data(:,1)+MOT_Data(:,4)-MOT_Data(:,2)-MOT_Data(:,3));
%Select References Data
Nref=[14:19];
REF_Data=Data(Nd,Nref);
%Select Roll Parameters
Npar_roll=[20:23];
ParaRoll=Data(Nd,Npar_roll);
%Select Pitch Parameters
Npar_pitch=[24:27];
ParaPitch=Data(Nd,Npar_pitch);
%Select Yaw Parameters
Npar_yaw=[28:31];
ParaYaw=Data(Nd,Npar_yaw);
%Select Roll Gains    
Ngain_roll=[32:35];
GainRoll=Data(Nd,Ngain_roll);
%Select Pitch Gains
Ngain_pitch=[36:39];
GainPitch=Data(Nd,36:39);
%Select Yaw Gains
Ngain_yaw=[40:43];
GainYaw=Data(Nd,40:43);
switch sel
    case 1
        Y=IMU_Data(:,4);
        U=L;
        R=REF_Data(:,4);
        Title='Roll Rate Tracking';        
        YSignal='Roll Rate (deg/s)';
        USignal='Virtual Moment Signal';
        Parameters=ParaRoll;
        TitleParam='Roll Parameters';  
    case 2
        Y=IMU_Data(:,5);
        U=M;
        R=REF_Data(:,5);
        Title='Pitch Response';
        YSignal='Pitch Rate (deg/s)';
        USignal='Pitch Throttle Signal';        
        Parameters=ParaPitch;
        TitleParam='Pitch Parameters';
    case 3
        Y=IMU_Data(:,6);
        U=N;
        R=REF_Data(:,6);
        Title='Yaw Response';
        YSignal='Yaw Rate (deg/s)';
        USignal='Yaw Throttle Signal';        
        Parameters=ParaYaw;
        TitleParam='Yaw Parameters';
end

%Generate timing vector
dt=0.02;
t=dt*(Nd-Nd(1));

%Select Data to Process
figure(1);
hold off
subplot(2,1,1);
stairs(t,Y);
hold on
stairs(t,R,'-.');
title(Title);
ylabel(YSignal);
subplot(2,1,2);
stairs(t,U);
ylabel(USignal);
xlabel('Time (s)');
[x,y]=ginput(2);               %Select 2 points from graph
n1=round(x(1)/dt);
n2=round(x(2)/dt);
range=(n1:n2);
R=R(range);
Y=Y(range);
U=U(range);

%Alterate timing vector and replot
t=dt*(Nd(range)-Nd(range(1)));
close all
figure();
subplot(2,1,1);
stairs(t,Y);
hold on
stairs(t,R,'-.');
lim=axis;
axis([t(1),t(end),lim(3:4)]);
title(Title);
ylabel(YSignal);
% legend('Roll Rate Output (p)','Roll Rate Reference (p_r)')
subplot(2,1,2);
stairs(t,U);
lim=axis;
axis([t(1),t(end),lim(3:4)]);
ylabel(USignal);
legend('L');
xlabel('Time (s)');

%Plot Angles
figure();
stairs(t,IMU_Data(range,1:3))
title('Angles Data');
ylabel('Angles (degs)');
xlabel('Time (s)');
legend('Roll','Pitch','Yaw');

%Plot Rates
figure();
stairs(t,IMU_Data(range,4:6));
title('Angular Velocity Data');
ylabel('Rates (deg/s)');
xlabel('Time (s)');
legend('Roll Rate','Pitch Rate','Yaw Rate');

%Plot Accelerations
figure();
stairs(t,IMU_Data(range,7:9));
title('Acceleration Data');
ylabel('Accelerations (m/s^2)');
xlabel('Time (s)');
legend('a_x','a_y','a_z');

%Plot Motors
figure();
stairs(t,MOT_Data(range,:));
title('Motors Data');
ylabel('Input Signal');
xlabel('Time (s)');
legend('M_1','M_2','M_3','M_4');

%Plot Moments
figure();
stairs(t,L(range,:));
hold on
stairs(t,M(range,:));
stairs(t,N(range,:));
title('Moments Data');
ylabel('Moments Signal');
xlabel('Time (s)');
legend('L','M','N');

%Plot Angle References
figure();
stairs(t,REF_Data(range,1:3));
title('Angle References Data');
ylabel('Angles (degs)');
xlabel('Time (s)');
legend('Roll Rate Ref','Pitch Rate Ref','Yaw Rate Ref');

%Plot Rates References
figure();
stairs(t,REF_Data(range,4:6));
title('Rates References Data');
ylabel('Rates (degs/s)');
xlabel('Time (s)');
legend('Roll Rate Ref','Pitch Rate Ref','Yaw Rate Ref');

%Plot Parameters
figure();
stairs(t,ParaRoll(range,1),'b');
hold on
stairs(t,ParaRoll(range,2),'r');
stairs(t,ParaRoll(range,3),'g');
title('Roll Axis - Estimated Parameters');
ylabel('Parameters');
xlabel('Time (s)');
plot(t,0*ones(length(t),1),'--b');
plot(t,-0.7*ones(length(t),1),'--b');
plot(t,0.3*ones(length(t),1),'--r');
plot(t,0.05*ones(length(t),1),'--r');
lim=axis;
axis([t(1),t(end),-1,0.5]);
legend('a','b');
% figure();
% stairs(t,ParaPitch(range,3:4));
% title('Pitch Parameters');
% ylabel('Parameters');
% legend('a','b');
% xlabel('Time (s)');
% figure();
% stairs(t,ParaYaw(range,3:4));
% title('Yaw Parameters');
% ylabel('Parameters');
% legend('a','b');
% xlabel('Time (s)');

%Plot Gains
figure();
stairs(t,GainRoll(range,:));
lim=axis;
axis([t(1),t(end),lim(3:4)]);
title('Roll Axis - Control Gains');
ylabel('Gains');
xlabel('Time (s)');
legend('K_x(1)','K_x(2)','K_x(3)','K_x(4)');
% figure();
% stairs(t,GainPitch(range,[1:2,4]));
% title('Pitch Gains');
% xlabel('Time (s)');
% figure();
% stairs(t,GainYaw(range,[1:2,4]));
% title('Yaw Gains');
% xlabel('Time (s)');