%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION i              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
remove_item(E,L,NewL) :-
    NewL is L with all occurrences of E removed
*/

remove_item(E,L,L) :-
    \+ member(E,L),
    !.

remove_item(E, [E|T], L) :-
    remove_item(E,T,L).

remove_item(E, [X|T], [X|L]) :-
    X \= E,
    remove_item(E,T,L).


%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION ii             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
drop_items(L,N,NewL) :-
    NewL is list L with the first N elements deleted
*/

drop_items(L,N,[]) :-
    length(L,X),
    X =< N.

drop_items(L,N,NewL) :-
    length(L,X),
    X > N,
    append(Discard,NewL,L),
    length(Discard,N).


%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION iii            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
drop_more_items(L,N,NewL) :-
    NewL removes the first N elements from L
    then removes all occurrences of these N
    elements from the rest of the list


HELPER PREDICATES:
remove_all(L1,L2,L) :-
    L is L2 with all elements of L1 removed

*/

% where N >= length of L
drop_more_items(L,N,[]) :-
    drop_items(L,N,[]),
    !.

% where N < length of L
drop_more_items(L,N,R) :-
    append(L1,L2,L),
    length(L1,N),
    remove_all(L1,L2,R).

% no more items to remove
remove_all([],L2,L2).

% remove X from L2
remove_all([X|L1],L2,L) :-
    remove_item(X,L2,NewL),
    remove_all(L1,NewL,L).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION iv               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
count(+L,Result) :-
    L is a list of elements and Result is of the form
    (I,Num) where I is an element in L and Num is the
    number of times I occurs in L (no repetitions)
*/

count(L,Result) :-
    count(L,Result,[]).

count([],Result,Result).

count([X|Y],Result,Acc) :-
    member((X,N),Acc),
    N1 is N+1,
    remove_item((X,N),Acc,NewAcc),
    count(Y,Result,[(X,N1)|NewAcc]).

count([X|Y],Result,Acc) :-
    \+ member((X,N),Acc),
    count(Y,Result,[(X,1)|Acc]).
