# listpractice

Past exam (?) found for Prolog list manipulation, used as preparation for the Prolog component of _550 Integrated Programming Laboratory_. All predicates tested using _SICStus 4.3.2_.

### i) remove_item(E, L, NewL).

NewL is L with all occurrences of E removed.

```prolog
remove_item(E,L,L) :-
  \+ member(E,L),
  !.

remove_item(E, [E|T], L) :-
  remove_item(E,T,L).

remove_item(E, [X|T], [X|L]) :-
  X \= E,
  remove_item(E,T,L).
```

### ii) drop_items(L, N, NewL).

NewL is L with the first N elements deleted.

```prolog
drop_items(L,N,[]) :-
  length(L,X),
  X =< N.

drop_items(L,N,NewL) :-
  length(L,X),
  X > N,
  append(Discard,NewL,L),
  length(Discard,N).
```

### iii) drop_more_items(L, N, NewL).

NewL is L with the first N elements deleted, with all occurrences of the first N elements also removed.

```prolog
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
```

### iv) count(L, Result).

Result is a list of (I, Num) where I is an element in L and Num is the number of times I occurs in L, with no repetitions.

```prolog
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
```
