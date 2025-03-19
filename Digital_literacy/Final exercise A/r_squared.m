function Rsq = r_squared( Y, Yf )
% Implement the body of this function to perform the calculation 
% of the coefficient of determination R^2 as defined in eq. (6).
% Only use the MATLAB built-in functions in your implementation. 
% The use of any tooolbox functions OR CYCLES is explicitly prohibited.
    r = Y - Yf;
    Rsq = 1 - sum(r.^2)/sqrt(var(Y));
end
