

xorgate(g1).
xorgate(g2).
andgate(g3).
andgate(g4).
orgate(g5).

% Describing the inputs:

input1(g1,1).
input2(g1,0).

input1(g2,X):- output(g1,X).
input2(g2,1).

input1(g3,1).
input2(g3,X):- output(g1,X).

input1(g4,1).
input2(g4,0).

input1(g5,X):- output(g3,X).
input2(g5,X):- output(g4,X).

% Describing outputs of gates:

output(G,X):- andgate(G), input1(G,I1), input2(G,I2), andresult(I1, I2, X).
output(G,X):- orgate(G), input1(G,I1), input2(G,I2), orresult(I1, I2, X).
output(G,X):- xorgate(G), input1(G,I1), input2(G,I2), xorresult(I1, I2, X).

andresult(1,1,1).
andresult(0,X,0).
andresult(X,0,0).

orresult(0,0,0).
orresult(1,X,1).
orresult(X,1,1).

xorresult(X,X,0).
xorresult(X,Y,1):- X\=Y.

% The Prolog query

% output(g2,X), output(g5,Y)

% will compute the output of the configuration:
% X=0, Y=1.




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Fibonacci

%Example:
%		?- fib(6,R).
%		R = 8
	
fib(1,1).
fib(2,1).
fib(N,R):- 	N >= 3,
		N1 is N-1,
		N2 is N-2,
		fib(N1,R1),
		fib(N2,R2),
		R is R1+R2.
















