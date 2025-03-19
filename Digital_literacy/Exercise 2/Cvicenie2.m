close all
%%
a = 2*pi;
v = 1:8; %v = [1 2 3 4 5 6 7 8];
A = [5 7; 9 0];
b = a; u = v; B = A;
c = a+2*b;
w = v + 2*u;
C = A + 2*B;%}
%%
p = [1/2 1/4 1/4];
H = - sum(p.*log2(p));
%%
e = 0.00000000000000022204;
eps
e == eps
%%
sin(pi) == 0
isapprox(sin(pi), 0) % abs(sin(pi) - 0) <= eps
tan(pi/2) == inf
%%
B = [ 16 2+1i 3-2i ; 5 11 10];
C = B';
D = B.';
E = conj(B);
%%
linsolve([3 2 -1; 2 -2 4; -1 1/2 -1], [1; -2; 0])