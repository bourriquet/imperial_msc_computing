%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
subList(L1, L2) :-
    every element in list L1 is also in list L2
*/

subList([],_).

subList([H|T],L2) :-
    member(H,L2),
    subList(T,L2).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
difference(+L1, +L2, L) :-
    L consists of the elements in L1 that are not in L2
*/

difference(L1, L2, L) :-
    findall(X, (member(X,L1), nonmember(X,L2)), L).

/*
%ACCUMULATOR VERSION

difference(L1, L2, L) :-
    difference(L1, L2, [], L).

difference([],_,L,L).

difference([H|T],L2,Acc,L) :-
    member(H,L2),
    difference(T,L2,Acc,L).

difference([H|T],L2,Acc,L) :-
    nonmember(H,L2),
    append([H],Acc,NewAcc),
    difference(T,L2,NewAcc,L).
*/


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sift(+L,+N,Result) :-
    Result is list L but with elements > N removed
*/

sift(L,N,Result) :-
    sift(L,N,[],Result).

sift([],_,Result,Result).

sift([H|T],N,Acc,Result) :-
    H > N,
    sift(T,N,Acc,Result).

sift([H|T],N,Acc,Result) :-
    H =< N,
    append([H],Acc,NewAcc),
    sift(T,N,NewAcc,Result).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 4                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
common(+L1,+L2,I) :-
    I is the list of common elements of lists L1 and L2

    I has no repeated elements and should be empty if L1
    and L2 have no common elements (so cannot use setof)
*/

common(L1,L2,I) :-
    findall(X, (member(X,L1),member(X,L2)), List),
    sort(List,I).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 5                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
delete(L,Result) :-
    Result is list L with every other element deleted
*/

delete([],[]).
delete([X],[X]).

delete([X,_|T1],[X|T2]) :-
    delete(T1,T2).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 6                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
process(+L1,+L2,Consistent,Inconsistent) :-
    L1 is a list of the form (Name,Number)
    L2 is a list of the form (Name,Number,MoreInfo)
    Consistent is the items in L2 that agree with L1
    Inconsistent is items left over from L2
*/

process(L1,L2,C,I) :-
    process(L1,L2,[],C,[],I).

process([],[],C,C,I,I).

% C and I finished if L2 is empty
process(_,[],C,C,I,I).

process(L1,[(X,Y,Z)|T],Acc1,C,Acc2,I) :-
    member((X,Y),L1),
    process(L1,T,[(X,Y,Z)|Acc1],C,Acc2,I).

process(L1,[(X,Y,Z)|T],Acc1,C,Acc2,I) :-
    nonmember((X,Y),L1),
    process(L1,T,Acc1,C,[(X,Y,Z)|Acc2],I).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 7                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
split(+L,+N,L1,L2) :-
    splits a list L into L1 and L2, such that the length
    of L1 is N
*/

split(L,0,[],L).

split([H|T],N,L1,L2) :-
    N > 0,
    NewN is N - 1,
    split(T,NewN,NewL,L2),
    append([H],NewL,L1).
    

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 8                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
drop(+L,+N,Result) :-
    drop every Nth element from the list L
*/

% make a copy of N for decrementing
drop(L,N,Result) :-
    drop(L,N,Result,N).

% if L is exhausted, set Result to an empty list
drop([],_,[],_).

% if K = 1 (time to drop), lose the element in L
drop([_|T1],N,Y,1) :-
    drop(T1,N,Y,N).

% if K > 1 (not time to drop), keep the element in L
drop([X|T1],N,[X|T2],K) :-
    K > 1,
    K1 is K - 1,
    drop(T1,N,T2,K1).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 9                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
enrolment(+L, +Student, Degree) :-
    L is a list of the form (Degree, ListofStudents)
*/

enrolment(L,Student,Degree) :-
    Enrol = (Degree,Students),
    member(Enrol,L),
    member(Student,Students).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 10               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
student_list(L,Meng,MSc) :-
    L is a list of the form (Degree, ListofStudents)
    Meng is a list of students with Degree = meng
    MSc is a list of students with Degree = msc
*/

student_list([],[],[]).

student_list([(Degree,List)|T],Meng,MSc) :-
    Degree = meng,
    student_list(T,Meng2,MSc),
    append(List,Meng2,Meng).

student_list([(Degree,List)|T],Meng,MSc) :-
    Degree = msc,
    student_list(T,Meng,MSc2),
    append(List,MSc2,MSc).
