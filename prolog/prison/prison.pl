% compile the Prison Database

:- ensure_loaded(prisonDB).

forall(C1,C2) :-
	\+ (C1, \+ C2).

cell(N) :-
   cells(Cells),
   in_range(1,Cells,N).

%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION a          %
%%%%%%%%%%%%%%%%%%%%%%%

/*
in_range(Min,Max,N) :-
    generates integers N between (inclusive) Min and Max
*/

in_range(Min,Max,Min) :-
    Min =< Max.

in_range(Min,Max,N) :-
    Min < Max,
    NewMin is Min + 1,
    in_range(NewMin,Max,N).


%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION b          %
%%%%%%%%%%%%%%%%%%%%%%%

/*
empty_cell(Cell) :-
    one clause definition, Cell has no prisoner
*/

empty_cell(Cell) :-
    \+prisoner(_,_,Cell,_,_,_).


%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION c          %
%%%%%%%%%%%%%%%%%%%%%%%

/*
all_female_cell(Cell) :-
    Cell is a non-empty cell containing only female prisoners
*/

all_female_cell(Cell) :-
    cell(Cell),
    \+ empty_cell(Cell),
    forall(prisoner(_,F,Cell,_,_,_), female_name(F)).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION d           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
female_prisoners(N) :-
    N is the number of female prisoners in the prison
*/

female_prisoners(N) :-
    findall((F,L),(prisoner(L,F,_,_,_,_),female_name(F)),List),
    length(List,N).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION e           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
cell_occupancy(Cell, N) :-
    N is the number of prisoners in Cell
*/

cell_occupancy(Cell,N) :-
    cell(Cell),
    findall((F,L),prisoner(F,L,Cell,_,_,_),List),
    length(List,N).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION f           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
fullest_cell(Cell) :-
    there is no other cell in the prison with more prisoners
    than Cell
*/

fullest_cell(Cell) :-
    cell_occupancy(Cell,N),
    \+ (cell_occupancy(OtherCell,OtherN), OtherN > N).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION g           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
worst_psychopath(S,F,Crime,T) :-
    (S,F) is a psychopath serving a length of T years for
    Crime, and there is no other pscyhopath serving a
    sentence longer than T
*/

worst_psychopath(S,F,Crime,T) :-
    prisoner(S,F,_,Crime,T,_),
    psychopath(S,F),
    \+ (prisoner(S2,F2,_,_,T2,_), psychopath(S2,F2), T2 > T).


%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION h           %
%%%%%%%%%%%%%%%%%%%%%%%%

/*
criminals(Crime,N) :-
    N is the number of prisoners that have been
    convicted of Crime
*/

criminals(Crime,N) :-
    crimes(Crimes),
    member(Crime,Crimes),
    findall((S,F),prisoner(S,F,_,Crime,_,_),List),
    length(List,N).
