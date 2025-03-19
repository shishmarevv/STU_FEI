%% play with random signals
clear 
clc 
format compact 
close all

%% Exercise 5:
% Copy your working code from FINAL = PART A

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




%% Exercise 6: implement the linreg() function in a separate linreg.m file.

%% Exercise 7:
%  For the X coordinates and both noisy datasets Y1, Y2 from EX.4 find the
%  coeficients alpha, beta of the simple linear regression:
%   a) using your function linreg
%   b) using the MATLAB function polyfit
%   c) using the \ operator.
% 
%Insert code below: calling the linreg() function 
[alphaA1, betaA1] = linreg(x, y1)
[alphaA2, betaA2] = linreg(x, y2)
% Insert code below: using a toolbox function
B1 = polyfit(x, y1, 1)
B2 = polyfit(x, y2, 1)
% Insert code below: using the \ operator
C1 = [x', ones(length(x), 1)]\(y1')
C2 = [x', ones(length(x), 1)]\(y2')

%% Exercise 8:
% Use the polyval() function to find the data yf1 and yf2 for both noisy
% datasets y1 and y2 using the previously found linear regression 
% coefficients alpha, beta for the x vector defined in E4. 
% Use the plot(), subplot() and scatter() functions to plot
% three plots side by side:
%   1. The noisy data y1 along with the fitted linear function values yf1.
%   2. The noisy data y2 along with the fittel linear function values yf2.
%   3. The linear fitted values yf1 and yf2.
yf1 = polyval([betaA1, alphaA1], x); 
yf2 = polyval([betaA2, alphaA2], x); 

figure()
subplot(1, 3, 1)
plot(x, yf1, "r")
hold on
scatter(x, y1, "b")
subplot(1, 3, 2)
plot(x, yf2, "r")
hold on
scatter(x, y2, "b")
subplot(1, 3, 3)
plot(x, yf1, "r")
hold on
plot(x, yf2, "b")
%% Exercise 9:
% Implement the body of the function r_squared() in file r_squared.m 
% Do not modify the following code:
% 
Rsq11 = r_squared( y1, yf1 )
Rsq12 = r_squared( y1, yf2 )

if Rsq11 > Rsq12
    disp('As expected, fit1 better represents dataset 1') ;
else
    disp('fit2 better represents dataset 1. strange.')
end 
Rsq21 = r_squared( y2, yf1 )
Rsq22 = r_squared( y2, yf2 )
% 
if Rsq22 > Rsq21
    disp('As expected, fit2 better represents dataset 2') ;
else
    disp('fit1 better represents dataset 2. strange.')
end

%% Exercise 10:
% For the second fit Yf2 and know values Y2, calculate residuals and 
% plot them using the scatter() function. Also use the hist() 
% function to calculate and plot the histogram of the residuals.
r1 = y1 - yf1;
r2 = y2 - yf2;
figure()
subplot(1, 3, 1)
stem(x, r1)
subplot(1, 3, 2)
scatter(x, r2)
subplot(1, 3, 3)
histogram(r1);
%stem is better for discret residuals and scatter is better for trends
%analysis

%% Exercise 11

alpha	= 0.5
beta	= 2

s		= 0.1

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

[alphaA1, betaA1] = linreg(x, y1)
[alphaA2, betaA2] = linreg(x, y2)
% Insert code below: using a toolbox function
B1 = polyfit(x, y1, 1)
B2 = polyfit(x, y2, 1)
% Insert code below: using the \ operator
C1 = [x', ones(length(x), 1)]\(y1')
C2 = [x', ones(length(x), 1)]\(y2')

yf1 = polyval([betaA1, alphaA1], x); 
yf2 = polyval([betaA2, alphaA2], x); 

figure()
subplot(1, 3, 1)
plot(x, yf1, "r")
hold on
scatter(x, y1, "b")
subplot(1, 3, 2)
plot(x, yf2, "r")
hold on
scatter(x, y2, "b")
subplot(1, 3, 3)
plot(x, yf1, "r")
hold on
plot(x, yf2, "b")

Rsq11 = r_squared( y1, yf1 )
Rsq12 = r_squared( y1, yf2 )

if Rsq11 > Rsq12
    disp('As expected, fit1 better represents dataset 1') ;
else
    disp('fit2 better represents dataset 1. strange.')
end 
Rsq21 = r_squared( y2, yf1 )
Rsq22 = r_squared( y2, yf2 )
% 
if Rsq22 > Rsq21
    disp('As expected, fit2 better represents dataset 2') ;
else
    disp('fit1 better represents dataset 2. strange.')
end

r1 = y1 - yf1;
r2 = y2 - yf2;
figure()
subplot(1, 3, 1)
stem(x, r1)
subplot(1, 3, 2)
scatter(x, r2)
subplot(1, 3, 3)
histogram(r1);