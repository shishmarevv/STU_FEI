%Shishmarev Viktor Lab7
function M = cyclicShiftMatrix( Size, Shift )
% Generate a square permutation matrix if size Size.
% The permutation is a right rotation (cyclic shift) - the ROR operation.
% That is the right-multiplication of a row-vector by this matrix performs 
% a cyclic shift of vector's position - the ROR operation.
% The scalar shift specifies how many positions to rotate
% if negative, a ROL operation is performed.

M = rotateRight(eye(Size), Shift);
end

