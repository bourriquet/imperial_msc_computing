/*
  Filename: rook.h
  Author: lc3311
  Last updated: 13/12/15

  This header file contains the declarations of the Rook class

  Corresponding implementation file: ../rook.cpp
*/

#ifndef ROOK_H
#define ROOK_H

#include <map>
#include <string>

#include "piece.h"

using namespace std;

class Rook : public Piece {

  /*
    Public methods:
        Rook() (constructor)
	~Rook() (destructor)
	copy() (copies a Rook and returns a pointer to it)
	piece_string() (returns the Rook as a string)
	valid_move() (returns true if the Rook can move from the source to the destination)
  */

 public:
  Rook(bool _white);
  ~Rook();
  Rook* copy();
  string piece_string();
  bool valid_move(const string source, const string destination, const map<string, Piece*>* board);

};

#endif
