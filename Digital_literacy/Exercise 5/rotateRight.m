%Shishmarev Viktor Lab7
function rotated = rotateRight(M, shift)
    % Performs cyclic shift of vector's position - the ROR operation.
    % Performs horizontal ROR, if a matrix is supplied, rotate all rows.
    % The scalar shift specifies how many positions to rotate
    %   if negative, a ROL operation is performed.
    [~, cols] = size(M);
    shift = mod(shift, cols);
    if shift < 0
        shift = cols + shift;
    end
    rotated = [M(:, end-shift+1:end), M(:, 1:end-shift)];
end
