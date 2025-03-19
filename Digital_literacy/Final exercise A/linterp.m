function [ X, Y ] = linterp( a, b, Xl, n )
% LINTERP  Interpolate by linear function.
%   [ X, Y ] = linterp( a, b, Xl, n )
%
%     a, b: scalar coeficients of the linear function f(x) = a * x + b
%     Xl:   interval of x values [xmin, xmax]
%     n:    number of subintervals into which to divite Xl
%           n >= 1
%
%   See also LINTERPCOEF, POLYVAL.

	if nargin == 0
		unit_test() ;
		return ;
	end

	%implement the exercise code here:
    X = linspace(Xl(1),Xl(2), n + 1);
    Y = polyval([a b], X);
end

%leave these test functions alone

function LI_test( a, b, Xlim, n )
	[ X, Y ] = linterp( a, b, Xlim, n ) ;
	Y2 = polyval( [ a b ], X ) ;
	if isequal( Y, Y2 )
		disp(['Test PASSED']) ;
	else
		% DO -or- DO NOT put error statement here ???
		disp(['Test FAILED. Results: ' num2str( Y ) ' ~= ' num2str(Y2)]) ;
	end
end

function unit_test()
	LI_test( 1, 0, [0 1], 2 )
	LI_test( 2, 1, [0 10], 10 )
	LI_test( .5, 1, [0 10], 10 )
end
