sells(usa, grain, japan).
sells(S, P, R) :-  produces(S, P), needs(R, P).

produces(oman, oil).
produces(iraq, oil).
produces(japan, computers).
produces(germany, cars).
produces(france, iron).

needs(germany, iron).
needs(britain, cars).
needs(japan, cars).

needs(X, computers) :-  country(X).

needs(C, oil) :- needs(C, cars).

needs(britain, coal).
needs(japan, coal).
needs(japan, diamonds).


country(X) :- X=britain; X=japan; X=germany ; X=france.

nat_res(france, coal). 
nat_res(britain, coal).  
nat_res(south_africa, diamonds).    

ce(france, coal). 
ce(south_africa, diamonds). 

%%%%%%%%%%%%%%%%%%%
%%  Part (8)

mines(C, I) :- nat_res(C, I), ce(C, I).

exports(C1,I,C2) :- (produces(C1, I); mines(C1, I)),needs(C2, I).

in_competition(C1,C2,I) :- exports(C1,I,_), exports(C2,I,_), C1 \=C2.

lower_price(I) :- in_competition(C1,C2,I).


