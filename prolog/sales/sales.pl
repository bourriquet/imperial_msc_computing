% supplier, item, price
sellsFor('Peter Jones', swan123, 28).
sellsFor('Peter Jones', electrolux214, 27).
sellsFor('Peter Jones', hoover02, 60).
sellsFor('Peter Jones', electrolux09, 70).
sellsFor('Harrods', electrolux214, 31).
sellsFor('Harrods', swan123, 30).
sellsFor('Harrods', hoover02, 65).
sellsFor('Harrods', electrolux09, 80).

% supplier has item in stock
inStock('Peter Jones', electrolux214).
inStock('Peter Jones', hoover02).
inStock('Peter Jones', electrolux09).
inStock('Harrods', swan123).
inStock('Harrods', electrolux09).

% supplier located in city
locatedIn('Peter Jones', london).
locatedIn('Harrods', london).

% type of item
typeOfItem(swan123, electricKettle).
typeOfItem(electrolux214, electricKettle).
typeOfItem(hoover02, vacuum_cleaner).
typeOfItem(electrolux09, vacuum_cleaner).

% equivalent
equivalentItems(electrolux214, swan123).
equivalentItems(electrolux09, hoover02).

forall(C1,C2) :-
    \+ ((C1, \+C2)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1i              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sellsOneForLessThan(T,+MP,S,I,P) :-
    supplier S sells item I of type T at price P
    which is less than MP
*/

sellsOneForLessThan(T,MP,S,I,P) :-
    sellsFor(S,I,P),
    typeOfItem(I,T),
    P < MP.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1ii             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
equivalent(I1,I2) :-
    I1 and I2 have the same functionality
*/

equivalent(I1,I2) :-
    typeOfItem(I1,T),
    typeOfItem(I2,T),
    I1 \= I2.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1iii            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sellsEquivalentItemIn(+I,C,EI,S) :-
    supplier S is located in city C and S has item I
    in stock and EI = I, or S has an equivalent item
    in stock for no more than price of item I
*/

sellsEquivalentItemIn(I,C,EI,S) :-
    locatedIn(S,C),
    inStock(S,I),
    I = EI.

sellsEquivalentItemIn(I,C,EI,S) :-
    locatedIn(S,C),
    inStock(S,EI),
    equivalent(I,EI),
    sellsFor(S,I,P1),
    sellsFor(S,EI,P2),
    P2 =< P1.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1iv             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
neverUnderSold(S,C) :-
    there is no other supplier in city C that sells
    any item that S sells for a price less than S
*/

neverUnderSold(S,C) :-
    locatedIn(S,C), locatedIn(S2,C),
    forall((sellsFor(S,I,P1),sellsFor(S2,I,P2)), P1 < P2).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1v              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
listOfSuppliersFor(I,C,L) :-
    L is a list of (P,S), where S is a supplier in city
    C that supplies I for price P and has I in stock

    L is ordered by increasing price
*/

listOfSuppliersFor(I,C,L) :-
    setof((P,S),(inStock(S,I),sellsFor(S,I,P),locatedIn(S,C)),L).
