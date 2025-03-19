clear
clc
%Skupina C Shishmarev 04/11
% vytvorime si casovy vektor t
t = 0:.01:150;
% vytvorime handler (pointer) na funkcie
f_iter = @() funkcia_iter(t);
f_vekt = @() funkcia_vekt(t);
% odmerame cas vykonania funkcii
cas_vykonania_iter = timeit(f_iter)
cas_vykonania_vekt = timeit(f_vekt)
cas_vykonania_vekt > cas_vykonania_iter