%Form State Space
function [A,B,C]=GetSS(Theta,dt)
A=single(eye(4));
B=single(zeros(4,1));
C=single(zeros(1,4));
A(1,2)=dt*(1+Theta(1));
A(1,3)=dt;
A(1,4)=Theta(2);
A(2,2)=1+Theta(1);
A(2,3)=1;
A(2,4)=Theta(2)/dt;
B(1,1)=(Theta(2)+Theta(3));
B(2,1)=(Theta(2)+Theta(3))/dt;
B(4,1)=1;
C(1,1)=1;
end