/*
  Filename: bishop.h
  Author: lc3311
  Last updated: 13/12/15

  This header file contains the declarations of the Bishop class

  Corresponding implementation file: ../bishop.cpp
*/

#ifndef BISHOP_H
#define BISHOP_H

#include <map>
#include <string>

#include "piece.h"

using namespace std;

class Bishop : public Piece {

  /*
    Public methods:
        Bishop() (constructor)
	~Bishop() (destructor)
	copy() (copies a Bishop and returns a pointer to it)
	piece_string() (returns the Bishop as a string)
	valid_move() (returns true if the Bishop can move from the source to the destination)
  */
  
 public:
  Bishop(bool _white);
  ~Bishop();
  Bishop* copy();
  string piece_string();
  bool valid_move(const string source, const string destination, const map<string, Piece*>* board);

};

#endif
