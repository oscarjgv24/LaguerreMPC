function [Kx]=Laguerre_MPC(A,B,C,r0,L)
%Initialize Variables
Na=4;
Npfix=int16(50);
G=single(zeros(50,4));
H=single(zeros(50,50));
G(1,1:Na)=C*A;
H(1,1)=C*B;
%Propagate first column
for i=2:Npfix
    G(i,1:Na)=G(i-1,1:Na)*A;
    H(i,1)=G(i-1,1:Na)*B;
end
%Duplicate other columns
for i=2:Npfix
    H(i:Npfix,i)=H(1:Npfix-i+1,1);
end
%Embedd Laguerre
Hl=H*L;
%Compute Hessian
E=Hl'*Hl;
for i=1:2
        E(i,i)=E(i,i)+r0;
end
% %Perform Inversion
% Ei=inv(E(1:N,1:N));
%Calculate Required matrices
Eta=E\Hl'*G;
Kr=sum(L(1,:)*inv(E)*Hl')
Kx=L(1,:)*Eta;
end