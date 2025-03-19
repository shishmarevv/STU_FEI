function [res] = mystery_fcn(n)
    for i=1:n
        r = sqrt(2);
        phi = (1+r)^i;
        psi = (1-r)^i;
        mystery_val = (phi - psi)/(2*r);
    end
    res = mystery_val;
end
% 1 2 5 12 29 70 169 408 985 2.3780e+03