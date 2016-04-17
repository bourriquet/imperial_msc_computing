/*
  Filename: pawn.cpp
  User: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of functions of the Pawn class

  Corresponding header file: header/pawn.h
*/

#include "header/pawn.h"

using namespace std;

/*
  CONSTRUCTOR
      Calls the Piece constructor and sets king to false
*/
Pawn::Pawn(bool _white) : Piece(_white) {
  king = false;
}

/*
  DESTRUCTOR
*/
Pawn::~Pawn() {

}

/*
  copy()
      Public function creates a new Pawn with the same properties and returns a pointer to it
*/
Pawn* Pawn::copy() {
  return new Pawn(this->white);
}

/*
  valid_move()
      Public function returns true if the Pawn can move from the source square to the destination square

      A Pawn's valid moves:
          - Forward 1 square
	  - Forward 2 squares if it is the first move
	  - Diagonally forward 1 square if capturing a piece of the opposite colour
	  - Cannot jump over any pieces
*/
bool Pawn::valid_move(const string source, const string destination, const map<string, Piece*>* board) {

  // calculate how many positions forwards the Pawn wants to move
  char source_rank = source[1];
  char destination_rank = destination[1];
  int forwards = white ? destination_rank - source_rank : source_rank - destination_rank;

  // check conditions for moving within the same file
  if (same_file(source,destination)) {
    if (forwards == 2) {
      // Pawn can only move forwards 2 squares on its first move
      if (!first_move)
        return false;
      // check for vertical obstructions
      else if (!no_vertical_obstruction(source,destination,board))
        return false;
    }
    // Pawn can only move forwards 1 or 2 squares
    else if (forwards < 1 || forwards > 2)
      return false;
    // check if a Piece is in the destination square
    try {
      board->at(destination);
      // if here, a Piece is in the destination square
      return false;
    } catch (const std::out_of_range &error) {
      // no Piece in destination square - do nothing 
    }
    return true;
  }
  // check conditions for moving into an adjacent file
  else if (adjacent_file(source,destination) && forwards == 1) {
    // check if there is a piece in the destination square and if it is of the same colour
    try {
      board->at(destination);
      if (other_piece(destination,board)) {
	// the Piece is of the same colour
        return false;
      }
    } catch (const std::out_of_range& error) {
      // no Piece in destination square - move is false
      return false;
    }
    // the Piece is of a different colour - the move is valid 
    return true;
  }

  return false;
}

/*
  adjacent_file()
      Returns true if the source and destination squares are in adjacent files
*/
bool Pawn::adjacent_file(const string source, const string destination) {
  char source_file = source[0];
  char destination_file = destination[0];

  return abs(destination_file - source_file) == 1;
}

/*
  piece_string()
      Public function returns the Piece name as a string
*/
string Pawn::piece_string() {
  return "Pawn ";
}
