clear
clc
p = [4 -19 0 120]
q = [1 1]
r = conv(p,q)
polyval(r, 1)
roots(r)