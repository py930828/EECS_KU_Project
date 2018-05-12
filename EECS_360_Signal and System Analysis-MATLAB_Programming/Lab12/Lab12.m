clear all;
% part 1
figure(1);
a = [1 5];
b = [1 2 3];
xs = roots(b);
ys = roots(a);
pzmap(xs, ys);
% 2
figure(2);
a = [2 5 12];
b = [1 2 10];
xs = roots(b);
ys = roots(a);
pzmap(xs, ys);
% 3
figure(3);
a = [2 5 12];
b = [1 4 14 20];
xs = roots(b);
ys = roots(a);
pzmap(xs, ys);

% part 2
figure(4);
a = [1 2 17];
b = [1 4 104];
w = linspace(-20, 20, 200);
H = freqs(a, b, w);
subplot(211);
plot(w, abs(H));
subplot(212);
plot(w, angle(H));

figure(5);
sigma = linspace(-5, 5, 200);
[sigma, w] = meshgrid(sigma, w);
s = sigma + j*w;
H1 = polyval(a, s)./polyval(b, s);
mesh(sigma, w, 10*log10(abs(H1)));