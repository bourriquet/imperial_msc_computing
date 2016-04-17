OBJ = pawn.o rook.o bishop.o queen.o king.o knight.o piece.o chessboard.o ChessMain.o
EXE = chess
CXX = g++
CPPFLAGS = -Wall -g -std=c++11


$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: pieces/%.cpp
	$(CXX) $(CPPFLAGS) -c $<

pawn.o: pieces/header/pawn.h
rook.o: pieces/header/rook.h
bishop.o: pieces/header/bishop.h
queen.o: pieces/header/queen.h
king.o: pieces/header/king.h
knight.o: pieces/header/knight.h
piece.o: pieces/header/piece.h
chessboard.o: ChessBoard.h
ChessMain.o: ChessBoard.h

clean:
  rm *.o
