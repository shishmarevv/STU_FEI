function [ a, b ] = linterpCoef( P1, P2 )
    %both points are vectors [x,y]
    x1 = P1(1); x2 = P2(1); y1 = P1(2); y2 = P2(2);
    a = (y2 - y1)/(x2 - x1);
    b = y1 - a*x1;
end

