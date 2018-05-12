%Chen Long 
%EECS 3

clear all;
k=10;
result=0;
for m=1:k
    fac=1;
    for n=1: m
        fac=fac*n;
    end
    result=result+fac;
end
disp(result);