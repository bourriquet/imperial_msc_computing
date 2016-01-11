%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1a            %
%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
mysort(L,SL) :-
    SL is L sorted with all duplicates removed, NOT
    using sort/2
*/

mysort(L,SL) :-
    setof(X, member(X,L), SL).


%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1b            %
%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
rev(L,RevL) :-
    RevL is L with the order of its elements reversed,
    NOT using reverse/2
*/

rev([],[]).

rev([H|T], Rev) :-
    rev(T, NewRev),
    append(NewRev,[H],Rev).


%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1c            %
%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
followedBy(X,Y,L) :-
    X is followed by Y in list L
*/

followedBy(X,Y,L) :-
    append(_,[X,Y|_],L).


%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1d            %
%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
nextTo(X,Y,L) :-
    X and Y are next to each other on the list
*/

nextTo(X,Y,L) :-
    followedBy(X,Y,L);
    followedBy(Y,X,L).


%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1e            %
%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sumList(L,S) :-
    S is the sum of all integers in list L
*/

sumList([],0).

sumList([H|T],S) :-
    sumList(T,S1),
    S is H + S1.


%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2             %
%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
last(E,L) :-
    E is the last element in list L
*/

last(X,[X]).

last(E, [H|T]) :-
    last(E,T).


%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3a           %
%%%%%%%%%%%%%%%%%%%%%%%%%

edge(a,b).
edge(a,e).
edge(b,c).
edge(c,d).
edge(e,f).
edge(f,c).
edge(f,d).


%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3b           %
%%%%%%%%%%%%%%%%%%%%%%%%%

path(X,Y) :-
    edge(X,Y).

path(X,Y) :-
    edge(X,Z),
    path(Z,Y).


%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3c           %
%%%%%%%%%%%%%%%%%%%%%%%%%

path(X,Y,[X,Y]) :-
    edge(X,Y).

path(X,Y,[X|W]) :-
    edge(X,Z),
    path(Z,Y,W).


%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 4            %
%%%%%%%%%%%%%%%%%%%%%%%%%

/*
max(E,L) :-
    element E is the maximum element in list L
*/

max(X,[X]).

max(E,[X,Y|T]) :-
    X < Y,
    max(E, [Y|T]).

max(E,[X,Y|T]) :-
    Y =< X,
    max(E, [X|T]).


%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 5            %
%%%%%%%%%%%%%%%%%%%%%%%%%

/*
max_of_all(E,Ls) :-
    E is the max of all lists Ls

HELPER PREDICATES:

max_sub(E,Ls,X) :-
    X is the max of all sublists in Ls

larger(X,Y,Z) :-
    Z is the larger of X and Y
*/

max_of_all(E,[L|Ls]) :-
    max(X,L),
    max_sub(E,Ls,X).

max_sub(E,[],E).
max_sub(E,[L|Ls],X) :-
    max(Y,L),
    larger(X,Y,Z),
    max_sub(E,Ls,Z).

larger(X,Y,X) :-
    X >= Y.
larger(X,Y,Y) :-
    X < Y.

