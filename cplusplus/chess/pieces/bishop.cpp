/*
  Filename: bishop.cpp
  User: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of functions of the Bishop class

  Corresponding header file: header/bishop.h
*/

#include "header/bishop.h"

using namespace std;

/*
  CONSTRUCTOR
      Calls the Piece constructor and sets king to false
*/
Bishop::Bishop(bool _white) : Piece(_white) {
  king = false;
}

/*
  DESTRUCTOR
*/
Bishop::~Bishop() {

}

/*
  copy()
      Public function creates a new Bishop with the same properties and returns a pointer to it
*/
Bishop* Bishop::copy() {
  return new Bishop(this->white);

}

/*
  valid_move()
      Public function returns true if the Bishop can move from the source square to the destination square

      A Bishop's valid moves:
          - Any direction along a diagonal
	  - Any number of squares
	  - Cannot jump over any pieces
*/
bool Bishop::valid_move(const string source, const string destination, const map<string, Piece*>* board) {

  // check if the move is along a diagonal
  if (!same_diagonal(source,destination))
    return false;

  // check for obstructions
  else if (!no_diagonal_obstruction(source,destination,board))
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
string Bishop::piece_string() {
  return "Bishop ";
}
