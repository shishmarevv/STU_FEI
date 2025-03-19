clear
clc
%Skupina C Shishmarev 04/11
x = (-pi:pi:0)'
y = cos(x)
B = [x y]
[z, ~] = MATICA(B);
sum(z)