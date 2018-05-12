clear all;
% Task 1
fs=1000;
f=1;
t=0:1/fs:2;
xsquare=square(2*pi*f*t);

% Task 2
figure (1);
xs=0;
for n=-10:10
    xs=xs+(2/pi)*(1/(2*n-1))*cos((2*n-1)*(2*pi*f)*t-(pi/2));
end;
subplot(221);
plot(t,xsquare); hold on;
plot(t,xs)
subplot(222);
plot(t,xsquare-xs);

% Task 3
for m=1:10
    figure(m+1);
    xs=0;
    for n=m*(-50):m*50
        xs=xs+(2/pi)*(1/(2*n-1))*cos((2*n-1)*(2*pi*f)*t-(pi/2));
    end;
    subplot(221);
    plot(t,xsquare); hold on;
    plot(t,xs)
    legend('xsquare','x(t)')
    subplot(222);
    plot(t,xsquare-xs);
    legend('error')
end;

% Task 4
arr=[50,100,150,200,250,300,350,400,450,500];
count = 0;
list = zeros(10);
alist = 1;
sum = 0;
sum1 = 0;
for N=50:50:500;
    for n=-N:N
        sum=sum+(2/pi)*(1/(2*n-1))*cos((2*n-1)*(2*pi*f)*t-(pi/2));
    end;
    arx=(xsquare-sum).^2;
    for i=1:2000
        sum1 = sum1 +arx(i);
    end
    sum1 = sum1/2000;
    list(alist) = sum1;
    alist = alist + 1;
    sum = 0;
    sum1 = 0;
end
figure(12);
plot(arr, list);
        
