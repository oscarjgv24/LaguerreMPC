function [L]=GetLaguerre(a)
N=2;
Np=50;
v=single(zeros(N,1));
L0=single(zeros(N,1));
A=single(zeros(N,N));
v(1,1)=a;
L0(1,1)=single(1);
for k=2:N
    v(k,1)=(-a)^(k-2)*(1-a^2);
    L0(k,1)=(-a).^(k-1);
end
L0(1:N,1)=single(sqrt((1-a^2))*L0(1:N,1));
A(1:N,1)=v(1:N,1);
for i=2:N
    A(1:N,i)=[zeros(i-1,1);v(1:N-i+1,1)];
end
L=single(zeros(N,Np));
L(1:N,1)=L0(1:N,1);
for i=2:Np
    L(1:N,i)=A(1:N,1:N)*L(1:N,i-1);
end
L=L';
end