%Skupina C Shishmarev 04/11
function [y] = funkcia_iter(xtime)
    i = 0;
    for t = xtime
        i = i + 1;
        y(i) = exp(t);
    end
end