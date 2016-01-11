sells(usa, grain, japan).
sells(S, P, R) :- produces(S, P), needs(R, P).

produces(oman, oil).
produces(iraq, oil).
produces(japan, computers).
produces(germany, cars).
produces(france, iron).

needs(germany, iron).
needs(britain, cars).
needs(japan, cars).
needs(C, computers) :- country(C). % question 2
needs(C, oil) :- needs(C, cars).

%%%%%%%%%%%%%%%%%%%%
% QUESTION 3       %
%%%%%%%%%%%%%%%%%%%%

country(britain).
country(japan).
country(germany).
country(france).


%%%%%%%%%%%%%%%%%%%%
% QUESTION 4       %
%%%%%%%%%%%%%%%%%%%%

needs(britain, coal).
needs(japan, coal).
needs(japan, diamonds).


%%%%%%%%%%%%%%%%%%%%
% QUESTION 5       %
%%%%%%%%%%%%%%%%%%%%

/*
nat_res(C,I) :-
    C has item I as a natural resource
*/

nat_res(france, coal).
nat_res(britain, coal).
nat_res(south_africa, diamonds).


%%%%%%%%%%%%%%%%%%%%
% QUESTION 6       %
%%%%%%%%%%%%%%%%%%%%

/*
ce(C,I) :-
    it is cost-effective to mine item I in country C
*/

ce(france, coal).
ce(south_africa, diamonds).


%%%%%%%%%%%%%%%%%%%%
% QUESTION 7       %
%%%%%%%%%%%%%%%%%%%%

/*

a) needs(C,I), nat_res(C,I).

b) produces(C,iron), ce(C,I), needs(japan,I).

c) needs(C,oil), needs(C,coal).

d) needs(C,I), ce(south_africa,I).

*/


%%%%%%%%%%%%%%%%%%%%
% QUESTION 8a      %
%%%%%%%%%%%%%%%%%%%%

/*
mines(C,I) :-
    a country C mines its natural resource I if it can
    do so cost-effectively
*/

mines(C,I) :-
    nat_res(C,I),
    ce(C,I).


%%%%%%%%%%%%%%%%%%%%
% QUESTION 8b      %
%%%%%%%%%%%%%%%%%%%%

/*
exports(C1,I,C2) :-
    country C1 exports item I to country C2 if C1 produces
    or mines it and C2 needs it
*/

exports(C1,I,C2) :-
    (produces(C1,I); mines(C1,I)),
    needs(C2,I).


%%%%%%%%%%%%%%%%%%%%
% QUESTION 8c      %
%%%%%%%%%%%%%%%%%%%%

/*
in_competition(C1,C2,I) :-
    countries C1 and C2 are in competition if they export
    the same item
*/

in_competition(C1,C2,I) :-
    exports(C1,I,_),
    exports(C2,I,_),
    C1 \= C2.


%%%%%%%%%%%%%%%%%%%
% QUESTION 8d     %
%%%%%%%%%%%%%%%%%%%

/*
lower_price(I) :-
    if there are two countries in competition over item I,
    its price will be lowered
*/

lower_price(I) :-
    in_competition(_,_,I).


%%%%%%%%%%%%%%%%%%%
% QUESTION 9      %
%%%%%%%%%%%%%%%%%%%

/*

a) mines(C,I).

b) exports(C,I1,_), exports(C,I2,_), I1 \= I2.

c) in_competition(C1,C2,oil).

d) in_competition(C1,C2,I), exports(C1,I,britain), exports(C1,I,japan),
    exports(C2,I,britain), exports(C2,I,japan).

e) exports(germany,I1,C1), needs(C1,I2), exports(C2,I2,_), mines(C2,diamonds).

f) needs(C1,I), needs(C2,I), C1 \= C2, lower_price(I).

*/


