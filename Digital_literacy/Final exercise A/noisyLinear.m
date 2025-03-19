function [ x, y ] = noisyLinear( alpha, beta, Xl, step, v )
    x = Xl(1):step:Xl(2);
    y = polyval([alpha beta], x) + random([0, v], [size(x) 1], "normal");
end