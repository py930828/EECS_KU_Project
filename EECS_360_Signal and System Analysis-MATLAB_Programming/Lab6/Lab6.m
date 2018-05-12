% Task 1
clear all;
fs=6283.2;
T=1/fs;
t=0:T:0.01;
f=100;
x=sin(2*pi*f*t);
soundsc(x,fs);
% subplot 2
subplot(222);
f1=1000;
x1=sin(2*pi*f1*t);
soundsc(x1,fs);
% subplot 3
subplot(223);
f2=2000;
x2=sin(2*pi*f2*t);
soundsc(x2,fs);
subplot(221);
plot(t,x);
subplot(222);
plot(t,x1);
subplot(223);
plot(t,x2);

% Task 2

% part a
fs=44100;
t=0:1/fs:0.5;
mat=zeros(8,length(t));
f1=261.626;
f2=293.665;
f3=329.628;
f4=349.228;
f5=391.995;
f6=440;
f7=493.883;
f8=0;
mat(1,:)=sin(2*pi*f1*t);
mat(2,:)=sin(2*pi*f2*t);
mat(3,:)=sin(2*pi*f3*t);
mat(4,:)=sin(2*pi*f4*t);
mat(5,:)=sin(2*pi*f5*t);
mat(6,:)=sin(2*pi*f6*t);
mat(7,:)=sin(2*pi*f7*t);
mat(8,:)=sin(2*pi*f8*t);
for n=1:7;
    soundsc(mat(n,:),fs);
    pause(0.5);
end;

list=[1,1,5,5,6,6,5,8,4,4,3,3,2,2,1];
for n=1:length(list);
    soundsc(mat(list(n),:),fs);
    pause(0.5);
end;

% part b
mat1=zeros(8,length(t)+500);
mat1(1,:)=[sin(2*pi*f1*t), zeros(1, 500)];
mat1(2,:)=[sin(2*pi*f2*t), zeros(1, 500)];
mat1(3,:)=[sin(2*pi*f3*t), zeros(1, 500)];
mat1(4,:)=[sin(2*pi*f4*t), zeros(1, 500)];
mat1(5,:)=[sin(2*pi*f5*t), zeros(1, 500)];
mat1(6,:)=[sin(2*pi*f6*t), zeros(1, 500)];
mat1(7,:)=[sin(2*pi*f7*t), zeros(1, 500)];
mat1(8,:)=[sin(2*pi*f8*t), zeros(1, 500)];
for n=1:length(list);
    soundsc(mat1(list(n),:),fs);
    pause(0.5);
end;

% Task 3
figure (2);
[p,fs]=audioread('Five_Columns_Long.wav');
subplot(211);
plot(p);
title('Five Columns_Long');
[p,fs]=audioread('Going_Home.wav');
subplot(212);
plot(p);
title('Going Home');
