% child_mother(C, M) means C is a child of mother M.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

child_mother(amy, mary).
child_mother(arthur, mary).
child_mother(angel, jane).
child_mother(anton, rita).
child_mother(alan, rita).
child_mother(axel, susan).
child_mother(ann, tina).


% age(C, A) means C is of age A.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

age(amy, 6).
age(arthur, 15).
age(angel, 16).
age(anton, 4).
age(alan, 8).
age(axel, 16).
age(ann, 4).


% employed(X) means X is employed.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

employed(susan).
employed(rita).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1i              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
ecb(M) :-
    M is a mother entitled to child benefit

    M is entitled to benefit if she has a child who
    is 14 years or younger, or if she is not employed
    and has a child who is older than 14 but not older
    than 16
*/

ecb(M) :-
    child_mother(Child, M),
    age(Child, X),
    ((X =< 14);
     (\+ employed(M), X > 14, X =< 16)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1ii             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
mother_of_the_youngest(M) :-
    M is the mother of the youngest child

    if there is more than one child with the youngest
    age, M is mother whose name comes first alphabetically
*/

mother_of_the_youngest(M) :-
    child_mother(Child, M),
    age(Child, X),
    \+ (age(Child2, Y), Y < X),
    \+ (child_mother(Child3,M2), age(Child3, X), M2 @< M).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1iii            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
mothers_of_young(LM) :-
    LM is the list of mothers who have a child of 10 or
    younger

    LM is sorted with no repetition
*/

mothers_of_young(LM) :-
    setof(M, Child^X^(child_mother(Child, M), age(Child, X), X =< 10), LM).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2i              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
merge(L1, L2, L) :-
    L is an ordered list resulting from merging L1 and L2

    L1 and L2 are already sorted lists
*/

% if both lists are empty, no merging needed
merge([],[],L).

% if one list is empty, the merged list is the other list
merge([],L1,L1).
merge(L2,[],L2).

% if the head element of the first list is smaller, add to merged
merge([H1|T1], [H2|T2], [H1|T]) :-
    H1 =< H2,
    merge(T1, [H2|T2], T).

% if the head element of the second list is smaller, add to merged
merge([H1|T1], [H2|T2], [H2|T]) :-
    H2 < H1,
    merge([H1|T1], T2, T).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2ii             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
findElement(+N, +L, E) :-
    E is the Nth element in list L
*/

findElement(1, [E|T], E).

findElement(N, [H|T], E) :-
    N > 1,
    length(T, X),
    N < X,
    N2 is N - 1,
    findElement(N2, T, E).
