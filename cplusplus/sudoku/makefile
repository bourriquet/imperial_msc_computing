OBJ = main.o sudoku.o
EXE = sudoku
CXX = g++
CPPFLAGS = -Wall -g

$(EXE): $(OBJ)
        $(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
        $(CXX) $(CPPFLAGS) -c $<

main.o: sudoku.h
sudoku.o: sudoku.h
