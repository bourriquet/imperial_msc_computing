# fariba_practice

Practice questions sent by Fariba in preparation for the Prolog component of _550 Integrated Programming Laboratory_.

All predicates tested on SICStus 4.3.2.

---

### 1) subList(L1, L2).

Every element in L1 is also in L2.

```prolog
subList([],_).

subList([H|T],L2) :-
  member(H,L2),
  subList(T,L2).
```

### 2) difference(L1, L2, L).

L consists of all the elements in L1 that are not in L2.

```prolog
difference(L1, L2, L) :-
  findall(X, (member(X,L1), nonmember(X,L2)), L).
```

### 3) sift(L, N, Result).

Result is L with all the elements greater than N removed.

```prolog
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
```

### 4) common(L1, L2, I).

I is the list of common elements of L1 and L2.

```prolog
common(L1,L2,I) :-
  findall(X, (member(X,L1),member(X,L2)), List),
  sort(List,I).
```

### 5) delete(L, Result).

Result is L with every other element deleted.

```prolog
delete([],[]).
delete([X],[X]).

delete([X,_|T1],[X|T2]) :-
  delete(T1,T2).
```

### 6) process(L1, L2, Consistent, Inconsistent).

L1 is a list of (Name, Number) and L2 is a list of (Name, Number, MoreInfo). Consistent is the list of (Name, Number, MoreInfo) that L1 and L2 agree on. Inconsistent is the left over items of L2.

```prolog
process(L1,L2,C,I) :-
  process(L1,L2,[],C,[],I).

process([],[],C,C,I,I).

process(_,[],C,C,I,I).

process(L1,[(X,Y,Z)|T],Acc1,C,Acc2,I) :-
  member((X,Y),L1),
  process(L1,T,[(X,Y,Z)|Acc1],C,Acc2,I).

process(L1,[(X,Y,Z)|T],Acc1,C,Acc2,I) :-
  nonmember((X,Y),L1),
  process(L1,T,Acc1,C,[(X,Y,Z)|Acc2],I).
```

### 7) split(L, N, L1, L2).

Split L into L1 and L2 such that the length of L1 is N.

```prolog
split(L,0,[],L).

split([H|T],N,L1,L2) :-
  N > 0,
  NewN is N - 1,
  split(T,NewN,NewL,L2),
  append([H],NewL,L1).
```

### 8) drop(L, N, Result).

Result is L with every Nth element removed.

```prolog
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
```

### 9) enrolment(L, Student, Degree).

L is a list of elements of the form (Degree, List of students). Giving Student returns the corresponding Degree and vice-versa.

```prolog
enrolment(L,Student,Degree) :-
  Enrol = (Degree,Students),
  member(Enrol,L),
  member(Student,Students).
```

### 10) student_list(L, Meng, Msc).

L is a list of elements of the form (Degree, List of students). Meng is a list of MEng students and Msc is a list of MSc students.

```prolog
student_list([],[],[]).

student_list([(Degree,List)|T],Meng,MSc) :-
  Degree = meng,
  student_list(T,Meng2,MSc),
  append(List,Meng2,Meng).

student_list([(Degree,List)|T],Meng,MSc) :-
  Degree = msc,
  student_list(T,Meng,MSc2),
  append(List,MSc2,MSc).
```
