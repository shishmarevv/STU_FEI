clear
clc
%Skupina C Shishmarev 04/11
tic
i = 0;
for t = 0:.01:150
    i = i + 1;
    y(i) = exp(t);
end
toc
% Elapsed time is 0.015422 seconds.
% Total time 0.009