/*
  Filename: knight.cpp
  User: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of functions of the Knight class

  Corresponding header file: header/knight.h
*/

#include "header/knight.h"

using namespace std;

/*
  CONSTRUCTOR
      Calls the Piece constructor and sets king to false
*/
Knight::Knight(bool _white) : Piece(_white) {
  king = false;
}

/*
  DESTRUCTOR
*/
Knight::~Knight() {

}

/*
  copy()
      Public function creates a new Knight with the same properties and return a pointer to it
*/
Knight* Knight::copy() {
  return new Knight(this->white);
}

/*
  valid_move()
      Public function returns true if the Knight can move from the source square to the destination square

      A Knight's valid moves:
          - Any direction along an L-shape
*/
bool Knight::valid_move(const string source, const string destination, const map<string, Piece *>* board) {

  // check if the Knight will be moving along an L-shape
  if (!L_shape(source,destination))
    return false;

  // returns false if there is a piece of the same colour in the destination square
  else if (other_piece(destination,board))
    return false;

  return true;
}

/*
  L_shape()
      Returns true if the Knight would be moving in an L-shape
*/
bool Knight::L_shape(const string source, const string destination) {
  char source_file = source[0];
  char source_rank = source[1];
  char destination_file = destination[0];
  char destination_rank = destination[1];

  return ((abs(source_file - destination_file) * abs(source_rank - destination_rank)) == 2);
}

/*
  piece_string()
      Public function returns the Piece name as a string
*/
string Knight::piece_string() {
  return "Knight ";
}
