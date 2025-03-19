function [ Rx ] = random(Lim, Si, flag) 
    if nargin < 3
        flag = "uniform";
    end
    if strcmp(flag, "uniform")
       Rx = Lim(1) + (Lim(2) - Lim(1))*rand(Si(1), Si(2));
    elseif strcmp(flag, "normal")
       Rx = Lim(1) + sqrt(Lim(2))*randn(Si(1), Si(2));
    else
       error('Incorrect flag');
    end
end