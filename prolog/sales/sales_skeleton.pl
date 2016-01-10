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
