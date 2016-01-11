% articles
article([the]).
article([a]).
article([an]).

% nouns
noun([boy]).
noun([apple]).
noun([song]).
noun([cow]).
noun([grass]).
noun([computer]).
noun([girl]).


% verbs
verb([eats]).
verb([sings]).


%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1         %
%%%%%%%%%%%%%%%%%%%%%%

/*
noun_phrase(NP) :-
    consists of article, noun

verb_phrase(VP) :-
    consists of verb or verb, noun phrase

sentence(S) :-
    consists of noun phrase, verb phrase
*/

noun_phrase(NP) :-
    article(A),
    noun(N),
    append(A,N,NP).

verb_phrase(VP) :-
    verb(VP).

verb_phrase(VP) :-
    verb(V),
    noun_phrase(NP),
    append(V,NP,VP).

sentence(S) :-
    noun_phrase(NP),
    verb_phrase(VP),
    append(NP,VP,S).


%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2a,b      %
%%%%%%%%%%%%%%%%%%%%%%

/*
could also consider whether the noun starts with a vowel or
a consonant i.e. whether the article should be 'a' or 'an'
*/

better_article([a],s).
better_article([an],p).
better_article([the],s).
better_article([the],p).

better_noun([boy],s,a).
better_noun([boys],p,a).
better_noun([apple],s,i).
better_noun([apples],p,i).
better_noun([song],s,i).
better_noun([songs],p,i).
better_noun([cow],s,a).
better_noun([cows],p,a).
better_noun([grass],s,i).
better_noun([grass],p,i).
better_noun([computer],s,i).
better_noun([computers],p,i).
better_noun([girl],s,a).
better_noun([girls],p,a).

better_verb([eat],p,a).
better_verb([sing],p,i).
better_verb([eats],s,a).
better_verb([sings],s,i).

better_noun_phrase(NP,B,I) :-
    better_article(A,B),
    better_noun(N,B,I),
    append(A,N,NP).

better_verb_phrase(VP,B,I) :-
    better_verb(VP,B,I).

better_verb_phrase(VP,B,I) :-
    better_verb(V,B,I),
    better_noun_phrase(NP,B,I),
    append(V,NP,VP).

better_sentence(S) :-
    better_noun_phrase(NP,B,I),
    better_verb_phrase(VP,B,I),
    append(NP,VP,S).
