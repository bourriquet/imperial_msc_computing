/*
  Filename: queen.cpp
  User: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of functions of the Queen class

  Corresponding header file: header/queen.h
*/

#include "header/queen.h"

using namespace std;

/*
  CONSTRUCTOR
      Calls the Piece constructor and sets king to false
*/
Queen::Queen(bool _white) : Piece(_white) {
  king = false;
}

/*
  DESTRUCTOR
*/
Queen::~Queen() {

}

/*
  copy()
      Public function creates a new Queen with the same properties and returns a pointer to it
*/
Queen* Queen::copy() {
  return new Queen(this->white);
}

/*
  valid_move()
      Public function returns true if the Queen can move from the source square to the destination square

      A Queen's valid moves:
          - Any direction along a horizontal, vertical or diagonal
	  - Any number of squares
	  - Cannot jump over any pieces
*/
bool Queen::valid_move(const string source, const string destination, const map<string, Piece *>* board) {

  // check if the move is along a horizontal, vertical or diagonal
  if (!(same_file(source,destination) ||
	     same_rank(source,destination) ||
	     same_diagonal(source,destination)))
    return false;

  // check for obstructions
  else if ((same_file(source,destination) && !no_vertical_obstruction(source,destination,board)) ||
	   (same_rank(source,destination) && !no_horizontal_obstruction(source,destination,board)) ||
	   (same_diagonal(source,destination) && !no_diagonal_obstruction(source,destination,board)))
    return false;

  // returns false if there is a piece of the same colour in the destination square
  else if (other_piece(destination,board))
    return false;

  return true;
}

/*
  piece_string()
      Returns the Piece name as a string
*/
string Queen::piece_string() {
  return "Queen ";
}
