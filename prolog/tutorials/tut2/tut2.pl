%%%%%%%%%%%%%%%%%%%%
% QUESTION 1       %
%%%%%%%%%%%%%%%%%%%%

% inputs

input1(g1,1).
input2(g1,0).

input1(g2,X) :-
    output(g1,X).
input2(g2,1).

input1(g3,1).
input2(g3,X) :-
    output(g1,X).

input1(g4,1).
input2(g4,0).

input1(g5,X) :-
    output(g3,X).
input2(g5,X) :-
    output(g4,X).

% gate types
xorgate(g1).
xorgate(g2).
andgate(g3).
andgate(g4).
orgate(g5).

% results by gate

andresult(0,X,0).
andresult(X,0,0).
andresult(1,1,1).

orresult(0,0,0).
orresult(1,X,1).
orresult(X,1,1).

xorresult(0,0,0).
xorresult(X1,X2,1) :-
    X1 \= X2.

% outputs

output(G,X) :-
    (input1(G,I1), input2(G,I2)),
    ((andgate(G), andresult(I1,I2,X));
     (orgate(G), orresult(I1,I2,X));
     (xorgate(G), xorresult(I1,I2,X))).


%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2         %
%%%%%%%%%%%%%%%%%%%%%%

fib(1,1).
fib(2,1).

fib(N, X) :-
    N > 2,
    N1 is N - 1,
    N2 is N - 2,
    fib(N1, X1),
    fib(N2, X2),
    X is (X1 + X2).
