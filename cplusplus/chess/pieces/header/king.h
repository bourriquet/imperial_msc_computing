/*
  Filename: king.h
  Author: lc3311
  Last updated: 13/12/15

  This header file name contains the declarations of the King class

  Corresponding implementation file: ../king.cpp
*/

#ifndef KING_H
#define KING_H

#include <map>
#include <string>

#include "piece.h"

using namespace std;

class King : public Piece {

  /*
    Public methods:
        King() (constructor)
	~King() (destructor)
	copy() (copies a King and returns a pointer to it)
	piece_string() (returns the King as a string)
	valid_move() (returns true if the King can move from the source to the destination)
  */

 public:
  King(bool _white);
  ~King();
  King* copy();
  string piece_string();
  bool valid_move(const string source, const string destination, const map<string, Piece*>* board);

  /*
    Private methods:
        adjacent_square() (returns true if the destination square is adjacent to the source square)
  */

 private:
  bool adjacent_square(const string source, const string destination);

};

#endif
