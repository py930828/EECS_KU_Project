clear all;
% 1.a)
[area_Circle,perimeter_Circle]=Circle(2)

% 1.b)
[Ta,Tp]=Triangle(3, 5, 2, 2)
[Pa,Pb]=Pentagon(9)

% 2.a)
prompt='what shape do you want?';
shape=input(prompt,'s')
if(strcmp(shape,'circle')==1||strcmp(shape,'Circle')==1)
    prompt='what radius do you want?';
    a=input(prompt)
    [area_Circle,perimeter_Circle]=Circle(a)
end
if(strcmp(shape,'Triangle')==1||strcmp(shape,'triangle')==1)
    prompt='what a do you wish?';
    a=input(prompt)
    prompt='what b do you wish?';
    b=input(prompt)
    prompt='what c do you wish?';
    c=input(prompt)
    prompt='what h do you wish?';
    h=input(prompt)
    [Ta,Tp]=Triangle(a, b, c, h)
end
if(strcmp(shape,'pentagon')==1||strcmp(shape,'Pentagon')==1)
    prompt='what a do you want?';
    a=input(prompt)
    [Pa,Pb]=Pentagon(a)
end

% 3.a)
[name]=UMatrix(a)
[Rname]=RMatrix(a)

% 4.a)
A=(5+4j)*(4-5j);
% part b;
B=sqrt(20*(24/7)-12^4)+exp(1.32);
% part c;
C=cos(pi)+sin(pi);
% part d;
t=[1,2,3,4];
X=[1,2,3,4;5,6,7,8];
D=t*X';
% part e;
%A*B shows the matrix multiplication, A.*B do the multiplecation
% on each spot in the matrix, for this one, it is 1*5,2*6...
arrayA=[1,2;3,4];
arrayB=[5,6;7,8];
E1=arrayA+arrayB;
E2=arrayA-arrayB;
E3=arrayA*arrayB;
E4=arrayA.*arrayB;
% Define vector x function y and z
x = [-pi:pi/8:pi];
y = sin(x);
z = cos(x);

subplot(221);
plot(y); % plot y only.
% subplot 2
% subplot 1
subplot(221);
plot(y); % plot y only.
xlabel('x'), ylabel('y');
title('plot y')
% subplot 2
subplot(222);
plot(x,y), hold on; % plot y versus x, and hold
plot(x,z,'r--'), hold off; % plot z versus x with
legend('y','z')
xlabel('x'), ylabel('y');
title('plot x,y')
% subplot 3
subplot(223);
stem(x,y); % plot y versus x in discrete sequence
xlabel('x'), ylabel('y');
title('Y stem plot') % add title to the plot
% subplot 4
subplot(224), bar(x,z); % plot z versus x using bar chart
xlabel('x'), ylabel('y'); % add labels to the figure
title('plot bar')
grid on; % add grids to the figure

