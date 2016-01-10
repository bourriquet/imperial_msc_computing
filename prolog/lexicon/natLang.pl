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
   improves on noun_phrase(NP) so that the article matches
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
    
