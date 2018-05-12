clear all;
% part a);
figure (1);
t=-1:0.01:1;
x=exp(4*pi*j*t)+exp(-4*pi*j*t);
y=(exp(4*pi*j*t)-exp(-4*pi*j*t))/1i;
plot(t,x); 
hold on;
plot(t,y);
legend('y','z');
xlabel('t');

% part b);

t=-1:0.001:1;
figure (2);
z1=8*cos(2*pi*t-pi/2);
z2=8*cos(2*pi*t-pi);
z3=8*cos(2*pi*t-3*pi/2);
plot(t,z1,'*');
hold on;
plot(t,z2,'d');
hold on;
plot(t,z3,'o');
legend('z1','z2','z3');
xlabel('t');

% part c)
figure (3);
p=-1:0.001:1;
p1=3*cos(8*pi*p-pi/2);
p2=3*cos(8*pi*p-pi);
p3=3*cos(8*pi*p-3*pi/2);
plot(p,p1,'*');
hold on;
plot(p,p2,'d');
hold on;
plot(p,p3,'o');
legend('p1','p2','p3');
xlabel('p');

% Exercise 5.2
% (4/pi)*(1/(2n+1))cos((2n+1)*t-pi/2)
%  cos(2nt)
% ((1/(2n+1)).^2)*cos((2n+1)*t

% Exercise 5.3
figure (4);
% subplot 1
t=-8:0.01:8;
x1=(4/pi)*cos(t-pi/2);
subplot(321);
legend('x1');
plot(t,x1);
% subplot 2
subplot(322);
plot(t,x1); hold on;
x2=(4/(3*pi))*cos(3*t-pi/2);
plot(t,x2); hold on;
sx2=x1+x2;
plot(t,sx2);
legend('x1','x2','sx2');
% subplot 3
subplot(323);
plot(t,x1); hold on;
x2=(4/3*pi)*cos(3*t-pi/2);
plot(t,x2); hold on;
x3=(4/5*pi)*cos(5*t-pi/2);
plot(t,x3); hold on;
sx3=x1+x2+x3;
plot(t,sx3);
legend('x1','x2','x3','sx3');
% subplot 4
sx4=0;
m=10;
for n=0:m
    sx4=(4/pi)*(1/(2*n+1))*cos((2*n+1)*t-pi/2)+sx4;
end;
subplot(324);
plot(t,sx4);
legend('sx4');
% subplot 5
sx5=0;
m=25;
for n=0:m
    sx5=(4/pi)*(1/(2*n+1))*cos((2*n+1)*t-pi/2)+sx5;
end;
subplot(325);
plot(t,sx5);
legend('sx5');
% subplot 6
sx6=0;
m=50;
for n=0:m
    sx6=(4/pi)*(1/(2*n+1))*cos((2*n+1)*t-pi/2)+sx6;
end;
subplot(326);
plot(t,sx6);
legend('sx6');


% y function graphing
% Exercise 5.3
figure (5);
% subplot 1
t=-8:0.01:8;
y1=cos(t);
subplot(321);
plot(t,y1);
legend('y1');
% subplot 2
subplot(322);
plot(t,y1); hold on;
y2=cos(2*t);
plot(t,y2); hold on;
sy2=y1+y2;
plot(t,sy2);
legend('y1','y2','sy2');
% subplot 3
subplot(323);
plot(t,y1); hold on;
y2=cos(2*t);
plot(t,y2); hold on;
y3=cos(3*t);
plot(t,y3); hold on;
sy3=y1+y2+y3;
plot(t,sy3);
legend('y1','y2','y3','sy3');
% subplot 4
sy4=0;
m=10;
for n=0:m
    sy4=cos((n+1)*t)+sy4;
end;
subplot(324);
plot(t,sy4);
legend('sy4');
% subplot 5
sy5=0;
m=25;
for n=0:m
    sy5=cos((n+1)*t)+sy5;
end;
subplot(325);
plot(t,sy5);
legend('sy5');
% subplot 6
sx6=0;
m=50;
for n=0:m
    sx6=cos((n+1)*t)+sx6;
end;
subplot(326);
plot(t,sx6);
legend('sy6');

% z function graphing
% Exercise 5.3
figure (6);
% subplot 1
t=-8:0.01:8;
y1=cos(t);
subplot(321);
plot(t,y1);
legend('z1');
% subplot 2
subplot(322);
plot(t,y1); hold on;
y2=(1/9)*cos(3*t);
plot(t,y2); hold on;
sy2=y1+y2;
plot(t,sy2);
legend('z1','z2','sz2');
% subplot 3
subplot(323);
plot(t,y1); hold on;
plot(t,y2); hold on;
y3=(1/25)*cos(5*t);
plot(t,y3); hold on;
sy3=y1+y2+y3;
plot(t,sy3);
legend('z1','z2','z3','sz3');
% subplot 4
sy4=0;
m=10;
for n=0:m
    sy4=((1/(2*n+1)).^(2))*cos((2*n+1)*t)+sy4;
end;
subplot(324);
plot(t,sy4);
legend('sz4');
% subplot 5
sy5=0;
m=25;
for n=0:m
    sy5=((1/(2*n+1)).^(2))*cos((2*n+1)*t)+sy5;
end;
subplot(325);
plot(t,sy5);
legend('sz5');
% subplot 9
sx6=0;
m=50;
for n=0:m
    sx6=((1/(2*n+1)).^(2))*cos((2*n+1)*t)+sx6;
end;
subplot(326);
plot(t,sx6);
legend('sz6');