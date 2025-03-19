format compact ;

z = 3

Hbm = [  1  0 -1  2  1  0 -1 -1 ; ...
		 2 -1  0  1  0  0  0 -1 ; ...
		-1  2  1  0 -1 -1  0  0 ; ...
		 0  1  0  2  1 -1 -1  0 ]; 

H	= WIFI6_LDPC_ExpandH( Hbm, z )

[ m, n ] = size( H ) 
k = n - m 


i = randi( [0 1], k, 1 )  ;
[ c, A, B, T, C, D ,E ,TI ] = encodeLDPC( i, H, z ) ;

ok = isequal( mod( H * c , 2 ), zeros( m, 1 ) ) 
whos
