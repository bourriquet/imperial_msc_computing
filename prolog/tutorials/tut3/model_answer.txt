% 1 (a) - (e)

mysort(L,SL) :- setof(U,member(U,L),SL).

rev([],[]).
rev([H|T],R) :- rev(T,RT), append(RT,[H],R).

followedBy(X,Y,L) :- append(_,[X,Y|_],L).

nextTo(X,Y,L) :- followedBy(X,Y,L); 
		 followedBy(Y,X,L).

sumList([],0).
sumList([N|L],S) :- sumList(L,SumL), S is N+SumL.


% 2
 
last(X,[X]).
last(X,[Y,Z|W]) :- last(X, [Z|W]).

% 3 (a)

edge(a,b).
edge(a,e).
edge(b,c).
edge(c,d).
edge(e,f).
edge(f,c).
edge(f,d).
				
% 3 (b) 

path(X,Y):- edge(X,Y).
path(X,Y):- edge(X,Z), path(Z,Y).

% 3 (c) 

path(X,Y, [X,Y]):- edge(X,Y).
path(X,Y, [X|W]):- edge(X,Z), path(Z,Y,W).

% 4

max(X,[X]).
max(X, [Y,Z|W]) :- Y=<Z, max(X,[Z|W]).
max(X, [Y,Z|W]) :- Y>Z, max(X,[Y|W]).

% 5

max_of_all(E, [L|Ls]) :- max(X, L), find_max(E,Ls,X).

% find_max(E,Ls,X)  : E is the max element of all the sublists, given that X is the max % found so far  with the lists processed.

find_max(E, [], E).
find_max(E,[L|Ls],X) :- max(Y,L), bigger_of(X,Y,Z), find_max(E,Ls,Z).


% bigger_of(X,Y,Z) : Z is the bigger of X and Y

bigger_of(X,Y,X) :- X>=Y.
bigger_of(X,Y,Y) :- X<Y.
