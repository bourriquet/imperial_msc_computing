/*
  Filename: king.cpp
  User: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of functions of the King class

  Corresponding header file: header/king.h
*/

#include "header/king.h"

using namespace std;

/*
  CONSTRUCTOR
      Calls the Piece constructor and sets king to true
*/
King::King(bool _white) : Piece(_white) {
  king = true;
}

/*
  DESTRUCTOR
*/
King::~King() {

}

/*
  copy()
      Public function creates a new King with the same properties and returns a pointer to it
*/
King* King::copy() {
  return new King(this->white);
}

/*
  valid_move()
      Public function returns true if the King can move from the source square to the destination square

      A King's valid moves:
          - Any direction along a horizontal, vertical or diagonal
	  - One square only
*/
bool King::valid_move(const string source, const string destination, const map<string, Piece*>* board) {

  // check if the King wants to move to an adjacent square
  if (!adjacent_square(source,destination))
    return false;

  // returns false if there is a piece of the same colour in the destination square
  else if (other_piece(destination,board))
    return false;

  return true;
}

/*
  adjacent_square()
      Returns true if the source and destination squares are adjacent (whether horizontal, vertical or diagonal)
*/
bool King::adjacent_square(const string source, const string destination) {
  char source_file = source[0];
  char source_rank = source[1];
  char destination_file = destination[0];
  char destination_rank = destination[1];
  
  return (max(abs(source_file - destination_file), abs(source_rank - destination_rank)) == 1);
}

/*
  piece_string()
      Returns the Piece name as a string
*/
string King::piece_string() {
  return "King ";
}
