%% Shishmarev Viktor
clear
close all
clc

%% Exercise 1
A = random([1 25],[4 4]);
[S1, S2, S3, S4, S5, S6] = foo(A);
B = bar(S1, S2, S3, S4, S5, S6);
isequal(A', B)

%% Exercise 2
[A, E, F] = testRandom();
isequal(F, A*E)

%% Exercise 3
[A11, A12, A21, A22] = genA();
A = [A11 A12; A21 A22];
[B11, B21] = genB();
B = [B11; B21];
C = A*B;
[C11, C21] = mulPP(A11, A12, A21, A22, B11, B21);
C2 = [C11; C21];
isequal(C, C2)

%% Functions

function [S1, S2, S3, S4, S5, S6] = foo(A)
    S1 = A(1, 1:3);
    S2 = A(2:4, 4);
    S3 = A(2:3, 2:3);
    S4 = A(2:4, 1);
    S5 = A(4, 2:3);
    S6 = A(1, 4);
end

function B = bar(S1, S2, S3, S4, S5, S6)
    B = zeros(4);
    B(1:3, 1) = S1';
    B(4, 2:4) = S2';
    B(2:3, 2:3) = S3';
    B(1, 2:4) = S4';
    B(2:3, 4) = S5';
    B(4, 1) = S6';
end

function R = random(interval, dimensions)
    R = floor((interval(2) - interval(1) + 1)*(rand(dimensions)) + interval(1));
end

function [A, E, F] = testRandom()
    A = random([1 10], [4 4]);
    b = random([1 3], [4 1]);
    c = random([3 6], [4 1]);
    d = random([6 9], [4 1]);
    B = A*b;
    C = A*c;
    D = A*d;
    F = [B C D];
    E = [b c d];
end

function [A11, A12, A21, A22] = genA()
    A11 = ones(3, 4);
    A12 = 2*ones(3, 2);
    A21 = 3*ones(2, 4);
    A22 = 4*ones(2);
end

function [B11, B21] = genB()
    B11 = 5*ones(4, 3);
    B21 = 6*ones(2, 3);
end

function [C11, C21] = mulPP(A11, A12, A21, A22, B11, B21)
    C11 = A11*B11 + A12*B21;
    C21 = A21*B11 + A22*B21;
end