/*
  Filename: chessboard.cpp
  Author: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of the Chessboard class

  Corresponding header file: header/chessboard.h
*/

#include "../ChessBoard.h"

using namespace std;

/*
  CONSTRUCTOR
      Creates a new Board (map<string, Piece*>) and sets it up (adds pieces to it)
*/
ChessBoard::ChessBoard() {
  board = new Board();
  set_up_board();
}

/*
  DESTRUCTOR
*/
ChessBoard::~ChessBoard() {

}

/*
  submitMove()
      Public function to submit a move

      Process:
          - check if the game is still in progress
          - check if the move is valid - return if it isn't
	  - check if the player's King would still be safe
	  - confirm the move
	  - check if the game can continue
	  - switch players
*/
void ChessBoard::submitMove(const string source, const string destination) {
  // check if the game is still in progress
  if (end) {
    cout << "Game has ended." << endl;
    return;
  }
  
  // check if the source and destination squares are valid
  else if (!valid_squares(source,destination)) {
    cout << "Source/destination square invalid." << endl;
    return;
  }

  // check if there is a Piece at the source square
  else if (empty_source(source)) {
    cout << "There is no piece at position " << source << "!" << endl;
    return;
  }
  
  // get a pointer to the Piece at the source square
  Piece *current_piece = board->at(source);

  // check if the Piece belongs to the current player
  if (!current_player(white_turn,current_piece)) {
    cout << "It is not ";
    if (white_turn)
      cout << "Black's ";
    else 
      cout << "White's ";
    cout << "turn to move!" << endl;
    return;
  }

  // check if the move is valid (depends on the Piece)
  else if (!(current_piece->valid_move(source,destination,(board)))) {
    cout << current_piece->colour_string() << current_piece->piece_string() << "cannot move to " << destination << "!" <<  endl;
    return;
  }

  // check if the King would still be safe if the move happened
  if (king_safe(board,true) && !check_ahead(source,destination)) {
    cout << current_piece->colour_string() << current_piece->piece_string() << "cannot move to " << destination << "!" <<  endl;
    return;
  }

  // confirm the move
  confirm_move(source,destination,board);

  // if the game can't continue, the game has ended
  if (!game_continue())
    end = true;

  // switch players
  white_turn = !(white_turn);
}

/*
  resetBoard()
      Public function resets the board by cleaning it and setting up a new board
*/
void ChessBoard::resetBoard() {
  clean_board(board);
  board = new Board;
  set_up_board();
}

/*
  valid_squares()
      Returns true if the source and destination squares are valid
*/
bool ChessBoard::valid_squares(const string source, const string destination) {
  // check if the strings have two characters
  if ((source.length() != 2) || (destination.length() != 2))
    return false;

  // check if the source and destination squares are within the limits of the board
  else if (!(in_board(source) && in_board(destination)))
    return false;

  // return false if the source and destination squares are equal
  else if (source == destination)
    return false;

  return true;
}

/*
  in_board()
      Return true if the square is within the limits of the board
*/
bool ChessBoard::in_board(const string square) {
  char file = square[0];
  char rank = square[1];

  if (file < 'A' || file > 'H' || rank < '1' || rank > '8')
    return false;

  return true;
}

/*
  empty_source()
      Return true if there is no Piece at the source square
*/
bool ChessBoard::empty_source(const string source) {
  try {
    board->at(source);
  } catch (const std::out_of_range &error) {
    // there is no Piece at the source square
    return true;
  }

  return false;
}

/*
  current_player()
      Returns true if the Piece belongs to the current player
*/
bool ChessBoard::current_player(const bool white_turn, Piece* piece) {
  if (piece->white_piece() == white_turn)
    return true;

  return false;
}

/*
  capture_piece()
      Returns a pointer to the Piece in the destination square and moves the Piece from source square to destination square
*/
Piece* ChessBoard::capture_piece(const string source, const string destination, Board* board) {
  // pointer to the Piece to be moved
  Piece *source_piece = board->at(source);
  // pointer to the piece that will be captured
  Piece *destination_piece;

  try {
    destination_piece = board->at(destination);
    board->at(destination) = source_piece;
  } catch (const std::out_of_range &error) {
    // no Piece at the destination square - move the Piece at source and return NULL
    destination_piece = NULL;
    board->insert(map<string,Piece*>::value_type(destination,source_piece));
  }
  // remove the Piece at the source square
  board->erase(source);

  return destination_piece;
}

/*
  find_king()
      Returns a string of the square that a King is at
      Whether this is the player's King or the opposition's King is determined by own
*/
string ChessBoard::find_king(const Board* board, const bool own) {
  Board::const_iterator ii;

  // loop through every square with a Piece in it
  for (ii = board->cbegin(); ii != board->cend(); ii++) {
    string square = ii->first;
    Piece *piece = ii->second;
    // return the square
    if (own == false && (piece->white_piece() != white_turn) && (piece->king_piece() == true))
      return square;
    else if (own == true && (piece->white_piece() == white_turn) && (piece->king_piece() == true))
      return square;
  }

  return NULL;
}

/*
  king_safe()
      Return true if the King is safe
      Whether this is the player's King or the opposition's King is determined by own

*/
bool ChessBoard::king_safe(const Board* chessboard, const bool own) {

  // find the location of the King
  string king_square = find_king(chessboard, own);

  map<string,Piece*>::const_iterator ii;

  // loop through every square with a Piece in it
  for (ii = chessboard->begin(); ii != chessboard->end(); ii++) {
    string square = ii->first;
    Piece *piece = ii->second;

    // check if there are any moves to take the King
    if ((own == false) && (piece->white_piece() == white_turn) && (piece->valid_move(square, king_square, chessboard)))
      return false;
    else if ((own == true) && (piece->white_piece() != white_turn) && (piece->valid_move(square,king_square,chessboard)))
      return false;
  }

  return true;
}

/*
  copy_board()
      Copies a Board and returns a pointer to it
*/
Board* ChessBoard::copy_board(Board* board) {
  Board* copy = new Board;

  map<string,Piece*>::iterator ii;

  // loop through every square with a Piece in it
  for (ii = board->begin(); ii != board->end(); ii++) {
    copy->insert(map<string,Piece*>::value_type(ii->first,ii->second->copy()));
  }

  return copy;
}


/*
  confirm_move()
      Perform the move on the board (as it is already valid)
*/
void ChessBoard::confirm_move(const string source, const string destination, Board* board) {

  Piece *move = board->at(source);
  string taking = "";

  try {
    Piece* destination_piece = board->at(destination);
    // if here, a piece is being captured
    taking = " taking " + destination_piece->colour_string() + destination_piece->piece_string();
    delete destination_piece;
    board->at(destination) = move;
  } catch (const std::out_of_range &error) {
    // the move does not result in a Piece being captured
    board->insert(map<string,Piece*>::value_type(destination,move));
  }

  // check the move number of the Piece that has moved
  move->move();
  
  // remove the source piece from the map
  board->erase(source);

  // tentatively not in check
  check = false;
  
  cout << move->colour_string() <<  move->piece_string() << "moves from " << source << " to " << destination << taking << endl;
}

/*
  game_continue()
      Returns true if the game can continue
*/
bool ChessBoard::game_continue() {

  // get the string of the other player's colour
  string other = (white_turn) ? "Black " : "White ";

  // if the other King is not safe, the game is in check
  if (!king_safe(board,false) ) {
    check = true;
  }

  // check for valid moves if the game is in check
  if (valid_move_left()) {
    if (check)
      cout << other << "is in check" << endl;
  }
  if (!valid_move_left()) {
    if (check)
      cout << other << "is in checkmate" << endl;
    else
      cout << other << "is in stalemate" << endl;
    return false;
  }

  return true;
}

/*
  valid_move_left()
      Returns true if there are valid moves left for the other player
*/
bool ChessBoard::valid_move_left() {

  map<string,Piece*>::iterator ii;

  // loop through every square with a Piece
  for (ii = board->begin(); ii != board->end(); ii++) {
    string source = ii->first;
    Piece* piece = ii->second;

    // if the Piece is of the opposite colour
    if (piece->white_piece() != white_turn) {
      for (char i = 'A'; i <= 'H'; i++) {
        for (char j = '1'; j <= '8'; j++) {
          string destination = string() + i + j;

	  // if the Piece has a valid move left, check if the King would still be safe
          if (piece->valid_move(source,destination,board)) {

            Board* copy = copy_board(board);
            Piece* captured_piece = capture_piece(source,destination,copy);

            bool valid = king_safe(copy, false);

            delete captured_piece;
            clean_board(copy);

            if (valid) {
              return true;
	    }
          }
        }
      }
    }
  }
  return false;
}

/*
  clean_board()
      Cleans a board by deleting every Piece on it
*/
void ChessBoard::clean_board(Board* board) {

  map<string,Piece*>::iterator ii;

  // loop through every square with a Piece in it
  for (ii = board->begin(); ii != board->end(); ii++) {
    delete ii->second;
  }
  delete board;
}

/*
  set_up_board()
      Sets up the board by creating new Pieces and mapping them
*/
void ChessBoard::set_up_board() {

  // initial conditions - the game hasn't ended, is not in check and it's White's turn
  end = false;
  check = false;
  white_turn = true;

  char front_char = '2';
  char back_char = '7';

  string front;
  string back;

  // create Pawns
  for (char i = 'A'; i <= 'H'; i++) {
    front = string() + i + front_char;
    board->insert(map<string,Piece*>::value_type(front,new Pawn(true)));

    back = string() + i + back_char;
    board->insert(map<string,Piece*>::value_type(back,new Pawn(false)));
  }

  // create other Pieces
  board->insert(map<string,Piece*>::value_type("A1",new Rook(true)));
  board->insert(map<string,Piece*>::value_type("B1",new Knight(true)));
  board->insert(map<string,Piece*>::value_type("C1",new Bishop(true)));
  board->insert(map<string,Piece*>::value_type("D1",new Queen(true)));
  board->insert(map<string,Piece*>::value_type("E1",new King(true)));
  board->insert(map<string,Piece*>::value_type("F1",new Bishop(true)));
  board->insert(map<string,Piece*>::value_type("G1",new Knight(true)));
  board->insert(map<string,Piece*>::value_type("H1",new Rook(true)));

  board->insert(map<string,Piece*>::value_type("A8",new Rook(false)));
  board->insert(map<string,Piece*>::value_type("B8",new Knight(false)));
  board->insert(map<string,Piece*>::value_type("C8",new Bishop(false)));
  board->insert(map<string,Piece*>::value_type("D8",new Queen(false)));
  board->insert(map<string,Piece*>::value_type("E8",new King(false)));
  board->insert(map<string,Piece*>::value_type("F8",new Bishop(false)));
  board->insert(map<string,Piece*>::value_type("G8",new Knight(false)));
  board->insert(map<string,Piece*>::value_type("H8",new Rook(false)));

  cout << "A new chess game is started!" << endl;

}

/*
  check_ahead()
      Returns true if moving a Piece would still keep the player's King safe

*/
bool ChessBoard::check_ahead(const string source, const string destination) {

  // test the move on a copy of the board
  Board *copy = copy_board(board);
  Piece *move = copy->at(source);

  try {
    Piece* destination_piece = copy->at(destination);
    // if here, there is a Piece to be captured
    delete destination_piece;
    copy->at(destination) = move;
  } catch (const std::out_of_range &error) {
    // no Piece to be captured - insert the source Piece
    copy->insert(map<string,Piece*>::value_type(destination,move));
  }
  copy->erase(source);

  // return false if the player's King will no longer be safe
  if (!king_safe(copy,true)) {
    clean_board(copy);
    return false;
  }

  // delete the copied board
  clean_board(copy);
  return true;

}
