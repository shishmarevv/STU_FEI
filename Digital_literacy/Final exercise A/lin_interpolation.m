clear
clc

%% test finding linear interpolation coefficients

LC_test( [ 0 0 ],[ 1 1 ],[ 1 0 ]) ;
LC_test( [ 1 0 ],[ 2 1 ],[ 1 -1 ]) ;
LC_test( [ 0 1 ],[ 1 2 ],[ 1 1 ]) ;
LC_test( [ 1 2 ],[ 0 1 ],[ 1 1 ]) ;
LC_test( [ 2 1 ],[ 1 0 ],[ 1 -1 ] ) ;

%% testing the linear interpolation function

LI_test( 1, 0, [0 1], 2 )
LI_test( 2, 1, [0 10], 10 )

%% built-in unit test

linterp()

[ X, Y ] = linterp( 2,3, [1 10], 9)

%% local functions must be located at the end of the script:

function LC_test( P1, P2, R )
	[ a, b ] = linterpCoef( P1, P2 ) ;
	if isequal( [ a, b ], R )
		disp(['Test PASSED']) ;
	else
		disp(['Test FAILED. Results: ' num2str([a,b]) ' ~= ' num2str(R)]) ;
	end
end

function LI_test( a, b, Xlim, n )
	[ X, Y ] = linterp( a, b, Xlim, n ) ;
	Y2 = polyval( [ a b ], X ) ;
	if isequal( Y, Y2 )
		disp(['Test PASSED']) ;
	else
		disp(['Test FAILED. Results: ' num2str( Y ) ' ~= ' num2str(Y2)]) ;
	end
end

