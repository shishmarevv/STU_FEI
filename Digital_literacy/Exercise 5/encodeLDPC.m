%Shishmarev Viktor Lab7
function [ Codeword, A, B, T, C, D ,E ,TI ] = encodeLDPC( U, H, Z )
% Perform LDPC direct encoding procedure as specified in the 
% IEEE 802.16e standard Annex G.
% Input arguments:
%	U is the data word - the data bits
%	H is a sparse large binary parity check matrix of size m x n
% Return value:
%	Codeword - the systematic codeword
%	various interesting submatrices of H for debugging
if nargin == 3
	z = Z ;
end

[ m, n ] = size( H ) ;
k		= n - m ;

if ~exist('z','var') || isempty( z )
	z = n / 24 ;
end

% Exercise: complete the code to obtain required functionality
% Note: Don't forget the GF(2) (aka boolean) arithmetic approximation

%partition  the matrix according to Annex G.6 Method 2

A = mod(H(1:(m-z), 1:k), 2);
B = mod(H(1:(m-z), k+1:k+z), 2);
T = mod(H(1:(m-z), k+z+1:n), 2);
C = mod(H(m-z+1:end, 1:k), 2);
D = mod(H(m-z+1:end, k+1:k+z), 2);
E = mod(H(m-z+1:end, k+z+1:n), 2);


TI = mod(inv(T), 2);% Inverse of T over GF(2)


%test GF(2) inverse of double diagonal matrix
test	= mod( T * TI, 2 ) ;
if ~isequal( test, eye( m - z ) )
	error('Matrix inversion GF(2) failed.') ;
end


P1 = mod((C + E*TI*A)*U, 2);
P2 = mod(TI*(A*(U)+B*P1), 2);

Codeword = [ U ; P1 ; P2 ] ;
end
