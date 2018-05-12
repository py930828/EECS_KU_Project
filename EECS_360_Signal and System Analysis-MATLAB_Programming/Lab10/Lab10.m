clear all;
% part 2
Ts=0.01;
n=0:Ts:1;
x1=cos(20*pi*n);
subplot(311);
stem(n,x1);
% Ts=0.05
Ts=0.05;
n=0:Ts:1;
x1=cos(20*pi*n);
subplot(312);
stem(n,x1);
% Ts=0.1
Ts=0.1;
n=0:Ts:1;
x1=cos(20*pi*n);
subplot(313);
stem(n,x1);

% part 3
% rectpuls
figure(2);
ta=0:0.001:1;
Ts1=0.01;
n1=0:Ts1:1;
Fs=1/Ts1;
N=length(n1);
x=cos(20*pi*n1);
yrect1=zeros(N,length(ta));
for i=1:N
    yrect1(i,:)=x(i)*rectpuls(Fs*ta-i+1);
end 
subplot(311);
plot(ta, sum(yrect1));
% T=0.05
Ts1=0.05;
n1=0:Ts1:1;
Fs=1/Ts1;
N=length(n1);
x=cos(20*pi*n1);
yrect1=zeros(N,length(ta));
for i=1:N
    yrect1(i,:)=x(i)*rectpuls(Fs*ta-i+1);
end 
subplot(312);
plot(ta, sum(yrect1));
% T=0.1
ta=0:0.001:1;
Ts1=0.1;
n1=0:Ts1:1;
Fs=1/Ts1;
N=length(n1);
x=cos(20*pi*n1);
yrect1=zeros(N,length(ta));
for i=1:N
    yrect1(i,:)=x(i)*rectpuls(Fs*ta-i+1);
end 
subplot(313);
plot(ta, sum(yrect1));


% sinc
ta=0:0.001:1;
figure(3);
% T=0.001
Ts1=0.01;
n2=0:Ts1:1;
t=n2;
Fs=1/Ts1;
N=length(n2);
xa=cos(20*pi*t);
for i=1:N;
ysinc7(i,:)=xa*sinc(Fs*(ones(length(t),1)*ta-t'*ones(1,length(ta))));
end
subplot(311);
plot(ta, ysinc7);
% T=0.05
Ts2=0.05;
n2=0:Ts2:1;
t=n2;
Fs=1/Ts2;
N=length(n2);
xa=cos(20*pi*t);
for i=1:N;
ysinc72(i,:)=xa*sinc(Fs*(ones(length(t),1)*ta-t'*ones(1,length(ta))));
end
subplot(312);
plot(ta, ysinc72);
% T=0.1
Ts3=0.1;
n2=0:Ts3:1;
t=n2;
Fs=1/Ts3;
N=length(n2);
xa=cos(20*pi*t);
for i=1:N;
ysinc73(i,:)=xa*sinc(Fs*(ones(length(t),1)*ta-t'*ones(1,length(ta))));
end
subplot(313);
plot(ta, ysinc73);
% spline
figure(4);
% T=0.01
ts=0.01;
n4=0:ts:1;
ys10=spline(n4,cos(20*pi*n4),ta);
subplot(311);
plot(ta, ys10);
% T=0.05
ts2=0.05;
n4=0:ts2:1;
ys10=spline(n4,cos(20*pi*n4),ta);
subplot(312);
plot(ta, ys10);
% T=0.1
ts3=0.1;
n4=0:ts3:1;
ys10=spline(n4,cos(20*pi*n4),ta);
subplot(313);
plot(ta, ys10);