%Skupina C Shishmarev 04/11
function [b, B] = MATICA(A)
    b = sum(A');
    B = inv(A);
end