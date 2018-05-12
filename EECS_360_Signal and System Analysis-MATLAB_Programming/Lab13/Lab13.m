clear all;
% part 1
w = linspace(-20, 20, 200);
figure(1);
a = [1 1];
b = [1 -0.9 0.81];
xs = roots(b);
ys = roots(a);
zplane(xs, ys);
% freqz
figure(5);
H = freqz(b, a, w);
subplot(211);
plot(w, abs(H));
title('figure 1 magnitude');
subplot(212);
plot(w, angle(H));
title('figure 1 phase');

% 2
figure(2);
a = [2 5 12];
b = [1 2 10];
xs = roots(b);
ys = roots(a);
zplane(xs, ys);
% freqz
figure(6);
H = freqz(b, a, w);
subplot(211);
plot(w, abs(H));
title('figure 2 magnitude');
subplot(212);
plot(w, angle(H));
title('figure 2 phase');

% 3
figure(3);
a = [2 5 12];
b = [1 4 14 20];
xs = roots(b);
ys = roots(a);
zplane(xs, ys);
% freqz
figure(7);
H = freqz(b, a, w);
subplot(211);
plot(w, abs(H));
title('figure 3 magnitude');
subplot(212);
plot(w, angle(H));
title('figure 3 phase');

% 4
figure(4);
a = [2 0.49 0.7];
b = [1 0.079 -0.0365 -0.099];
xs = roots(b);
ys = roots(a);
zplane(xs, ys);
% freqz
figure(8);
H = freqz(b, a, w);
subplot(211);
plot(w, abs(H));
title('figure 4 magnitude');
subplot(212);
plot(w, angle(H));
title('figure 4 phase');

