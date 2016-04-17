/*
  Filename: rook.cpp
  User: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of functions of the Rook class

  Corresponding header file: header/rook.h
*/

#include "header/rook.h"

using namespace std;

/*
  CONSTRUCTOR
      Calls the Piece constructor and sets king to false
*/
Rook::Rook(bool _white) : Piece(_white) {
  king = false;
}

/*
  DESTRUCTOR
*/
Rook::~Rook() {

}

/*
  copy()
      Public function creates a new Rook with the same properties and returns a pointer to it
*/
Rook* Rook::copy() {
  return new Rook(this->white);
}

/*
  valid_move()
      Public function returns true if the Rook can move from the source square to the destination square

      A Rook's valid moves:
          - Any direction along a vertical or horizontal
	  - Any number of squares
	  - Cannot jump over any pieces
*/
bool Rook::valid_move(const string source, const string destination, const map<string, Piece *>* board) {

  // check if the Rook is moving in the same file or rank (vertically or horizontal)
  if (!(same_rank(source,destination) || same_file(source,destination)))
    return false;

  // check for obstructions
  else if ((same_file(source,destination) && !no_vertical_obstruction(source,destination,board)) ||
	   (same_rank(source,destination) && !no_horizontal_obstruction(source,destination,board)))
    return false;

  // return false if there is a piece of the same colour in the destination square
  else if (other_piece(destination,board))
    return false;

  return true;
}

/*
  piece_string()
      Returns the Piece name as a string
*/
string Rook::piece_string() {
  return "Rook ";
}
