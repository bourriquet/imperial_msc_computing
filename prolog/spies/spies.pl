:- use_module(library(lists)).

%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
decode(Message, Decoded_Message) :-
    Decoded_Message is Message with 'bear' replaced
    by 'double' and 'cub' replaced by 'agent'
*/

decode([],[]).

decode([H1|T1], [H2|T2]) :-
    ((H1 = bear, H2 = double);
     (H1 = cub, H2 = agent)),
    decode(T1, T2).

decode([H1|T1], [H2|T2]) :-
    (H1 \= bear, H1 \= cub),
    H2 = H1,
    decode(T1,T2).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
agents(Message, Decoded_Message, ListofAgents) :-
    Decoded_Message is Message decoded and ListofAgents
    contains the names accused of being double agents
    (no duplicates and sorted)
    
    must return empty list if no agents, therefore
    cannot use setof


HELPER PREDICATE:

is_agent(Decoded_Message, Name) :-
    Name is accused of being a double agent in the
    Decoded_Message

*/

agents(Message, Decoded_Message, ListofAgents) :-
    decode(Message, Decoded_Message),
    findall(X, is_agent(Decoded_Message, X), List),
    sort(List, ListofAgents).

is_agent([Name,is,a,double,agent|_], Name).
is_agent([H|T], Name) :-
    is_agent(T, Name).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
count_word(W,L,C) :-
    C is the number of times W occurs in L
*/

count_word(W,[],0).

count_word(W,[H|T],C) :-
    H = W,
    count_word(W,T,C2),
    C is C2 + 1.

count_word(W,[H|T],C) :-
    H \= W,
    count_word(W,T,C).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 4           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
count_ag_names(Message, Ag_name_counts) :-
    Ag_name_counts is a list of names that have been
    accused of being a double agent in Message (a coded
    message)
*/

count_ag_names(Message, Count) :-
    decode(Message, Decoded),
    findall((Name,X),(is_agent(Decoded,Name),count_word(Name,Decoded,X)),List),
    sort(List,Count).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 5           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
accusation_counts(M,AC) :-
    AC is a list of (Name,Count) where Name is accused
    of being a double agent in the coded message M and
    Count is the number of times Name is accused of being
    a double agent, ordered in descending number of Count


HELPER PREDICATES:

count_sort(List,Sorted) :-
    sorts List in the form of (X,Number) in order of descending
    Number, by checking if all permutations of List are sorted

    *not the most efficient way as it computes all permutations

sort_count(List) :-
    checks if List in the form of (X,Number) is sorted by
    descending Number
*/

accusation_counts(M,AC) :-
    decode(M, Decoded),
    findall(X, is_agent(Decoded,X), List),
    findall((Y,C), (member(Y,List), count_word(Y,List,C)),AC_unsorted),
    sort(AC_unsorted,AC_namesort),
    count_sort(AC_namesort,AC).

count_sort(List,Sorted) :-
    perm(List, Sorted),
    sort_count(Sorted).

sort_count([]).
sort_count([_]).
sort_count([(X1,Y1),(X2,Y2)|T]) :-
    Y1 >= Y2,
    sort_count([(X2,Y2)|T]).
