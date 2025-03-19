%% Exercise 1:
%	Write a function that performs cyclic shift of vector's position 
%	- the ROR operation known from computer science.
%	Should performs horizontal ROR, if a matrix is supplied, rotate all rows.
%	The scalar shift specifies how many positions to rotate
%	if negative, a ROL operation should performed.
vector		= [1:1:10] ;
shift		= 3 ;
rvector		= rotateRight( vector, shift ) ;
revvector	= rotateRight( rvector, -shift ) ; 
rv2vector	= rotateRight( rvector, size( vector, 2 ) - shift ) ;
if( ~isequal( vector, revvector ) || ~isequal( vector, rv2vector ) )
	error 'Vector rotation failed.' ;
else
	disp(['All OK']) ;
end

%% Exercise 2:
% Generate a square permutation matrix if size Size.
% The permutation is a right rotation - the ROR operation.
% That is the right-multiplication of a vector by this matrix performs 
% a cyclic shift of vector's position - the ROR operation.
% The scalar shift specifies how many positions to rotate
%	if negative, a ROL operation is performed.

ROR			= cyclicShiftMatrix( size( vector, 2 ), shift ) ;
rvector		= vector * ROR	;	% right-multiply with row vector
crvector	= ROR' * vector' ;	% left-multiply with column vector

revvector	= ROR * rvector' ;

if ~isequal( crvector', rvector ) || ... 
	~isequal( revvector', vector ) 
	error 'Matrix formulation of vector rotation failed.' ;
end

%% Exercise 3:
% Expand integer model matrix Hbm to large sparse binary parity check
% matrix H

R = 3/4		%valid values are: 1/2, 2/3, 3/4, 5/6
n = 1944 	%valid values are: 648, 1296, 1944

code = loadWIFI6_LDPC( R, n )

% Modify the body of the following function to implement the expansion procedure
H = WIFI6_LDPC_ExpandH( code.Hbm, code.z ) ;
whos H

%optionally call this to see a graphical H matrix visualisation:
displayBinaryMatrix( H, code.z ) ;

%% Exercise 4: LDPC direct encoding
% Implement a function, that performs LDPC direct encoding procedure 
% as specified in the IEEE 802.16e standard Annex G.
% Input arguments:
%	U is the data word - the data bits in a column vector
%	H is a sparse large binary parity check matrix of size m x n
U			= randi( [ 0 1 ], code.K, 1 ) ;
Codeword	= encodeLDPC( U, H ) ;
Syndrome	= mod( H * Codeword, 2) ;

if( ~isequal( Codeword( 1 : code.K ), U ) || sum( Syndrome ) ~= 0 )
	error 'Encoding failed.' ;
else
	disp( 'Encoding OK' ) ;
end
