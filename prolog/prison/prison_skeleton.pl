% compile the Prison Database

:- ensure_loaded(prisonDB).

forall(C1,C2) :-
	\+ (C1, \+ C2).

cell(N) :-
   cells(Cells),
   in_range(1,Cells,N).
