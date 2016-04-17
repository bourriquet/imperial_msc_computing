/*
  Filename: chessboard.h
  Author: lc3311
  Last updated: 13/12/15

  This header file contains the declarations of the ChessBoard class

  Corresponding implementation file: chessboard.cpp
*/

#include <map>
#include <iostream>
#include <string>

#include "pieces/header/pawn.h"
#include "pieces/header/rook.h"
#include "pieces/header/bishop.h"
#include "pieces/header/knight.h"
#include "pieces/header/queen.h"
#include "pieces/header/king.h"

using namespace std;

typedef map<string, Piece *> Board;

class ChessBoard {

  /*
    Public methods:
        Chessboard() (constructor)
	~Chessboard() (destructor)
	submitMove() (submits the move, checks if its valid, alters Board)
	resetBoard() (cleans a Board and sets up a new Board)
  */

 public:
  ChessBoard();
  ~ChessBoard();
  void submitMove(const string source, const string destination);
  void resetBoard();

  /*
    Protected attributes and methods:
        white_turn (true if it's White's turn)
	check (true if the game is in check)
	end (true if the game has ended)
	valid_squares (returns true if the source and destination are valid squares)
	in_board (returns true if square is within the board)
	empty_source (returns true if there is no Piece in the source square)
	current_player (returns true if the Piece belongs to the current player)
	capture_piece (returns a pointer to the Piece to be captured - may be NULL)
	find_king (finds the square of the King belonging to own)
	king_safe (returns true if own's King is safe)
	copy_board (returns a pointer to a copy of the Board)
	confirm_move() (confirms the move on the Board)
	game_continue() (returns true if the game can continue)
	valid_move_left() (returns true if there are still valid moves on the Board)
	clean_board() (deletes all Pieces from the Board)
	set_up_board() (inserts new Pieces onto a Board)
	check_ahead() (checks if a move would still keep the player's King safe)
  */

 private:
  Board *board;
  bool white_turn;
  bool check;
  bool end;
  bool valid_squares(const string source, const string destination);
  bool in_board(const string square);
  bool empty_source(const string source);
  bool current_player(const bool white_turn, Piece* piece);
  Piece* capture_piece(const string source, const string destination, Board* board);
  string find_king(const Board* chessboard, const bool own);
  bool king_safe(const Board* chessboard, const bool own);
  Board* copy_board(Board *board);
  void confirm_move(const string source, const string destination, Board* board);
  bool game_continue();
  bool valid_move_left();
  void clean_board(Board* board);
  void set_up_board();
  bool check_ahead(const string source, const string destination);

};
