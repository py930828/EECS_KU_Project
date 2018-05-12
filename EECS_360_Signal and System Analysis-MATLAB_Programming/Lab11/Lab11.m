clear all;
% part 1

% 1000 samples
figure (1);
fs1=1000;
Ts1=1/fs1;
n1=0:Ts1:8;
x=cos(60*n1);
subplot(411);
plot(n1,x);
% fft
figure(2);
y=abs(fft(x))/fs1;
f=(-(length(y)-1)/2:(length(y)-1)/2)*20/length(y);
subplot(411);
stem(f,y);

% 100 samples
figure (1);
fs1=100;
Ts1=1/fs1;
n1=0:Ts1:8;
x=cos(60*n1);
subplot(412);
plot(n1,x);
% fft
figure(2);
y=abs(fft(x))/fs1;
f=((-(length(y)-1)/2):((length(y)-1)/2))*25/length(y);
subplot(412);
stem(f,y);

% 20 samples
figure (1);
fs1=20;
Ts1=1/fs1;
n1=0:Ts1:8;
x=cos(60*n1);
subplot(413);
plot(n1,x);
% fft
figure(2);
y=abs(fftshift(fft(x)))/fs1;
f=((-(length(y)-1)/2):((length(y)-1)/2))*20/length(y);
subplot(413);
stem(f,y);

% 10 samples
figure (1);
fs1=10;
Ts1=1/fs1;
n1=0:Ts1:8;
x=cos(60*n1);
subplot(414);
plot(n1,x);
% fft
figure(2);
y=abs(fft(x))/fs1;
f=(-(length(y)-1)/2:(length(y)-1)/2)*10/length(y);
subplot(414);
stem(f,y);
