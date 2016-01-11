
%Solutions to Prolog Tutorial 4, 2014

%1. 

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
noun([cows]).

verb([eats]).
verb([chews]).
verb([kicks]).
verb([sings]).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%2a. 

better_sentence(S):- noun_phrase(NP, SP), verb_phrase(VP, SP), append(NP, VP, S). 

noun_phrase(NP, SP):- article(A, SP), noun(N, SP), append(A, N, NP). 

verb_phrase(V, SP):- verb(V, SP).
verb_phrase(VP, SP):- verb(V, SP), noun_phrase(NP, SP1), append(V, NP, VP).

% The Lexicon:

article([the], singular).
article([the], plural).
article([a], singular).
article([an], singular).

noun([grass], singular).
noun([cow], singular).
noun([girl], singular).
noun([boy], singular).
noun([apple], singular).
noun([song], singular).

noun([cows], plural).
noun([girls], plural).
noun([boys], plural).
noun([apples], plural).
noun([songs], plural).


verb([eats], singular).
verb([chews], singular).
verb([kicks], singular).
verb([sings], singular).

verb([eat],  plural).
verb([chew], plural).
verb([kick], plural).
verb([sing], plural).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%2(b)
even_better_sentence(S):- noun_phrase(NP, SP, N), verb_phrase(VP, SP, V), 
			match(N, V), append(NP, VP, S). 

noun_phrase(NP, SP, N):- article(A, SP), noun(N, SP), append(A, N, NP). 

verb_phrase(V, SP, V):- verb(V, SP).
verb_phrase(VP, SP, V):- verb(V, SP), noun_phrase(NP, SP1), append(V, NP, VP).


match(Noun, Verb) :- animate(Noun), active(Verb).

% could also add a match for inanimate nouns and inactive verbs.


animate([cow]).
animate([girl]).
animate([boy]).

active([eats]).
active([chews]).
active([kicks]).
active([sings]).






