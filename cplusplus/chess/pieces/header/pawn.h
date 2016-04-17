/*
  Filename: pawn.h
  Author: lc3311
  Last updated: 13/12/15

  This header file contains the declarations of the Pawn class

  Corresponding implementation file: ../pawn.cpp
*/

#ifndef PAWN_H
#define PAWN_H

#include <string>
#include <map>

#include "piece.h"

using namespace std;

class Pawn : public Piece {

  /*
    Public methods:
        Pawn() (constructor)
	~Pawn() (destructor)
	copy() (copies a Pawn and returns a pointer to it)
	piece_string() (returns the Piece as a string)
	valid_move() (returns true if the Pawn can move from the source to the destination
  */

 public:
  Pawn(bool _white);
  ~Pawn();
  Pawn* copy();
  string piece_string();
  bool valid_move(const string source, const string destination, const map<string, Piece*>* board);

  /*
    Private methods:
        adjacent_file() (returns true if the source and destination are in adjacent files)
  */

 private:
  bool adjacent_file(const string source, const string destination);

};

#endif
