close all
clear
%%
N = 15
u = (0:N-1)'
v = N:2*N-1
w = 3:2:(1+2*N)
%%
v*u
v.*u'
%%
m = 4;
A = double(floor(10*rand(m)))
%%
rank(A)
det(A)
%%
sum(A)
sum(A, 2)
sum(A, 'all')
%%
flipH = fliplr(A)
flipV = flipud(A)
rot = rot90(A)'
A'
%%
vA = A(:, 2)
uA = A(1, :)
wA = A(end, :)
A1 = A(:, 1:(end/2))
A2 = A((end/2+1):end, :)
%%
V1 = A(:)'
V2 = A(:)
%%
C = zeros(m)
C(A>5) = A(A>5)