sentence(S):- noun_phrase(NP), verb_phrase(VP), append(NP, VP, S).
 
noun_phrase(NP):- article(A), noun(N), append(A, N, NP). 

verb_phrase(V):- verb(V).
verb_phrase(VP):- verb(V), noun_phrase(NP), append(V, NP, VP).

% The Lexicon:

article([the]).
article([a]).
article([an]).

noun([grass]).
noun([cow]).
noun([girl]).
noun([boy]).
noun([apple]).
noun([song]).

verb([eats]).
verb([sings]).
verb([chews]).
verb([kicks]).

adverb([slowly]).
adverb([deliberately]).
adverb([merrily]).
adverb([sweetly]).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1a              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
count_sentences(Text, Count) :-
   Count is the number of sentences in Text, where Text
   is a ground conjunction of sentences

   find how many 'and's there are in Text, then add 1
*/

count_sentences([], 0) :-
    !.
count_sentences(Text, Count) :-
    findall(and, member(and, Text), Ands),
    length(Ands, X),
    Count is X + 1.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1b              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
actions(Actor, Text, As) :-
   As is the list of actions that Actor does in Text


HELPER PREDICATE:

followed_by(X, Y, List) :-
   X is followed by Y in List
*/

actions(Actor, Text, As) :-
    findall(A, (followed_by(Actor, A, Text), A \= and), As).

followed_by(X, Y, List) :-
    append(_, [X,Y|_], List). 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
noun_phrase_better(NPB) :-
   improves on noun_phrase/1 so that the article matches
   the noun in noun phrases (in terms of first vowel of the noun)


HELPER PREDICATES:

atoms(Atom, Chars) :-
    performs atom_chars/2 on Atom, returning Chars

first_vowel(Word) :-
    checks if the first letter of Word is vowel
*/

noun_phrase_better(NPB) :-
    article(A),
    noun(N),
    atoms(N, W),
    ((first_vowel(W), A = [an]);
     (\+ first_vowel(W), A = [a]);
     (A = [the])),
    append(A, N, NPB).

atoms([H|_], W) :-
    atom_chars(H, W).

first_vowel([H|T]) :-
    member(H, [a,e,i,o,u]).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3a,b             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
cadvs(L) :-
    L is a conjuction of adverbs

    accumulator version loops infinitely (need to put check on 4 adverbs)
*/   

%list of 1 adverb
cadvs(List) :-
    adverb(List).

%list of 2 adverbs
cadvs(List) :-
    adverb(A),
    addAnd(A, List),
    checkReps(List).

%list of 3 adverbs
cadvs(List) :-
    adverb(A),
    addAnd(A, A2),
    addComma(A2, List),
    checkReps(List).

%list of 4 adverbs
cadvs(List) :-
    adverb(A),
    addAnd(A, A2),
    addComma(A2, A3),
    addComma(A3, List),
    checkReps(List).


addAnd(List, NewList) :-
    adverb(X),
    append([and], List, NewList2),
    append(X, NewList2, NewList).

addComma(List, NewList) :-
    adverb(X),
    append([','], List, NewList2),
    append(X, NewList2, NewList).

checkReps(List) :-
    setof(X, (member(X, List), X \= ',', X \= and), Set),
    findall(X, (member(X, List), X \= ',', X \= and), All),
    length(Set, L),
    length(All, L).



/*
% ACCUMULATOR VERSION

cadvs(L) :-
    cadvs([], L).

cadvs(L,L) :-
    L \= [].

% accumulator is empty, so add an adverb
cadvs(X, L) :-
    length(X,0),
    adverb(A),
    append(A, X, X2),
    cadvs(X2, L).

% accumulator has only 1 sentence (and is not a member)
cadvs(X, L) :-
    length(L,Y),
    Y > 0,
    nonmember(and, X),
    adverb([A]),
    nonmember(A, X),
    append([A], [and], X2),
    append(X2, X, X3),
    cadvs(X3, L).

% accumulator has more than 1 sentence (and is a member)
cadvs(X, L) :-
    length(L,Y),
    Y > 0,
    member(and, X),
    adverb([A]),
    nonmember(A, X),
    append([A], [','], X2),
    append(X2, X, X3),
    cadvs(X3, L).
*/


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3c              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
verb_phrase_better(VPB) :-
   improves on verb_phrase/1 by taking adverbs into account
*/

verb_phrase_better(VPB) :-
    verb(VPB).

verb_phrase_better(VPB) :-
    verb(V),
    noun_phrase_better(NPB),
    append(V, NPB, VPB).

verb_phrase_better(VPB) :-
    cadvs(A),
    verb(V),
    append(A, V, VPB).

verb_phrase_better(VPB) :-
    cadvs(A),
    verb(V),
    noun_phrase_better(NPB),
    append(V, NPB, VP),
    append(A, VP, VPB).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3d              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sentence_better(SB) :-
   improves on sentence/1 to include noun_phrase_better/1
   and verb_phrase_better/1
*/

sentence_better(SB) :-
    noun_phrase_better(NPB),
    verb_phrase_better(VPB),
    append(NPB, VPB, SB).

