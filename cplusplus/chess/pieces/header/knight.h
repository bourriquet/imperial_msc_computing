/*
  Filename: knight.h
  Author: lc3311
  Last updated: 13/12/15

  This header file contains the declarations of the Knight class

  Corresponding implementation file: ../knight.cpp
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include <map>
#include <string>

#include "piece.h"

using namespace std;

class Knight : public Piece {

  /*
    Public methods:
        Knight() (constructor)
	~Knight() (destructor)
	copy() (copies a Knight and returns a pointer to it)
	piece_string() (returns the Knight as a string)
	valid_move() (returns true if the Knight can move from the source to the destination
  */

 public:
  Knight(bool _white);
  ~Knight();
  Knight* copy();
  string piece_string();
  bool valid_move(const string source, const string destination, const map<string, Piece*>* board);

  /*
    Private methods:
        L_shape() (returns true if the Knight is moving in an L-shape)
  */

 private:
  bool L_shape(const string source, const string destination);

};

#endif
