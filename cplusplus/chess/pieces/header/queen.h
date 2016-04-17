/*
  Filename: queen.h
  Author: lc3311
  Last updated: 13/12/15

  This header file contains the declarations of the Queen class

  Corresponding implementation file: ../queen.cpp
*/

#ifndef QUEEN_H
#define QUEEN_H

#include <map>
#include <string>

#include "piece.h"

using namespace std;

class Queen : public Piece {

  /*
    Public methods:
        Queen() (constructor)
	~Queen() (destructor)
	copy() (copies a Queen and returns a pointer to it)
	piece_string() (returns the Queen as a string)
	valid_move() (returns true if the Queen can move from the source to the destination)
   */

 public:
  Queen(bool _white);
  ~Queen();
  Queen* copy();
  string piece_string();
  bool valid_move(const string source, const string destination, const map<string, Piece*>* board);

};

#endif
