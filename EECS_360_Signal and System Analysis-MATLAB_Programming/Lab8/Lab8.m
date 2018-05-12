clear all;
T=1.28;
t=0:0.01:T;
fo=1/T;
tau=0.01;
M=T/tau;
m=0;
f=-50:fo:50;
n=f/fo;
sum=0;
xf=1./(1+(j*2*pi*f));
for m=0:M-1
sum=sum+(exp(-1*tau*m)*exp((-j*2*pi*n*m)/M));
end
sum=tau*sum;
figure(1);
subplot(211);
plot(f,abs(sum));
subplot(212);
plot(f,abs(xf));
% Figure angle
figure(5);
subplot(211);
plot(f,abs(sum)); hold on;
plot(f,abs(xf));
subplot(212);
plot(f,angle(sum)); hold on;
plot(f,angle(xf));

% T = 0.1
figure(2);
sum = 0;
T=0.1;
fo=1/T;
f=-50:fo:50;
tau=0.01;
M=T/tau;
n=f/fo;
sum=0;
xf=1./(1+(j*2*pi*f));
for m=0:M-1
    sum=sum+(exp(-1*tau*m)*exp((-j*2*pi*n*m)/M));
end
sum=tau*sum;
subplot(211);
plot(f,abs(sum));
subplot(212);
plot(f,abs(xf));
figure(6);
subplot(211);
plot(f,abs(sum)); hold on;
plot(f,abs(xf));
subplot(212);
plot(f,angle(sum)); hold on;
plot(f,angle(xf));

% T = 5.12
figure(3);
sum = 0;
T=5.12;
t=0:0.01:T;
fo=1/T;
f=-50:fo:50;
tau=0.01;
M=T/tau;
n=f/fo;
xf=1./(1+(j*2*pi*f));
for m=0:M-1
    sum=sum+(exp(-1*tau*m)*exp((-j*2*pi*n*m)/M));
end
sum=tau*sum;
subplot(211);
plot(f,abs(sum));
subplot(212);
plot(f,abs(xf));
figure(7);
subplot(211);
plot(f,abs(sum)); hold on;
plot(f,abs(xf));
subplot(212);
plot(f,angle(sum)); hold on;
plot(f,angle(xf));

% T = 12.8
figure(4);
sum = 0;
T=12.8;
t=0:0.01:T;
fo=1/T;
f=-50:fo:50;
tau=0.01;
M=T/tau;
n=f/fo;
xf=1./(1+(j*2*pi*f));
for m=0:M-1
sum=sum+(exp(-1*tau*m)*exp((-j*2*pi*n*m)/M));
end
sum=tau*sum;
subplot(211);
plot(f,abs(sum));
subplot(212);
plot(f,abs(xf));
figure (8);
subplot(211);
plot(f,abs(sum)); hold on;
plot(f,abs(xf));
subplot(212);
plot(f,angle(sum)); hold on;
plot(f,angle(xf));
