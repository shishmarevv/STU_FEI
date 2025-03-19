clear
clc
%%
p = poly([-5 4 3 2]);
r = polyint(p);
p = [0 p];
q = p + r;
roots(q)
