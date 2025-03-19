%% play with random signals
clear 
clc 
format compact 
close all
%% Exercise 2: See file lin_interpolation.m

%% Exercise 3:
% Using your implementation of the function [ Ru, Ri, Rn ] = random( [ a b ], [ M N ], flag ) 
% generate a matrix Ru of pseudo random values from a uniform distribution
% and a matrix Ri of pseudo random integer values from a uniform distribution
% and a matrix Rn of random values from a normal distribution.
% Let the size of all matrices be MxN.
% Let the mean value of Rn be m = 8 and variance v = 3.
% Let the values of Ru an Ri be from the interval <a,b> = <4,9>
% Run this section several times to observe that each time
% different matrices will be generated. 

M = 5 ;
N = 10 ;

m = 8 ;
v = 3 ;

a = 4 ;
b = 9 ;


Rn = random([m, v], [M, N], "normal");
Ru = random([a, b], [M, N], "uniform");
Ri = floor(random([a, b], [M, N], "uniform"));

% Calculate the sample mean and variance of all pseudo random matrices:

%   a) for each column 
%   b) for the whole matrix
Mna = mean(Rn)
Mnb = mean(Rn(:))

Vna = var(Rn)
Vnb = var(Rn(:))

Mua = mean(Ru)
Mub = mean(Ru(:))

Vua = var(Ru)
Vub = var(Ru(:))

Mia = mean(Ri)
Mib = mean(Ri(:))

Via = var(Ri)
Vib = var(Ri(:))

%% Exercise 4:
% Generate a pseudo random column vector V of varying length N
% and constant mean and variance m = 10, v = 3.
% For each vector length N calculate sample mean ms and variance vs
% and for each calculated ms and vs calculate thei relative errors in
% per cent.
% Run this section several times to observe slightly different results each
% time.

m = 10
v = 3

for N = [1 2 5 10.^[ 1 : 5 ] ]
    V = random([m, v], [N, 1], "normal");
    ms = mean(V);
    vs = var(V);
    erm = abs((ms - m)/m)*100;
    erv	= abs((vs - v)/v)*100;
	fprintf("Vector length N: %6d, mean: %10.6f, variance: %10.6f, mean error: %10.6f%%, variance error: %10.6f%% \n", N, ms, vs, erm, erv);
end

%% Exercise 5:
% Generate values of a linear function f(x) = ax + b for the x variable 
% taking on values from the interval <-4,10> with step 0.1.
% Create two noisy copies: Y1, and Y2 by adding pseudo-random noise from normal
% distribution: one with a variance v1 = 0.1, the other with v2 = 1
% Use the plot(), subplot() and scatter() function to plot three plots
% side-by-side: first the noiseless linear function f(x), second the
% scattered noisy observations Y1, and finally scattered observations
% of the more noise degraded signal Y2.

alpha	= 0.5
beta	= 2

s		= 0.5

[x, fx] = noisyLinear(alpha, beta, [-4, 10], s, 0);
[~, y1] = noisyLinear(alpha, beta, [-4, 10], s, 0.1);
[~, y2] = noisyLinear(alpha, beta, [-4, 10], s, 1);

figure()
subplot(1, 3, 1)
plot(x, fx)
subplot(1, 3, 2)
scatter(x, y1)
subplot(1, 3, 3)
scatter(x, y2)