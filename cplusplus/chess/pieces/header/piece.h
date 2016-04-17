/*
  Filename: piece.h
  Author: lc3311
  Last updated: 13/12/15
  
  This header file contains the declarations of the (abstract) Piece class

  Corresponding implementation file: ../piece.cpp
*/

#ifndef PIECE_H
#define PIECE_H

#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

class Piece {

  /*
    Public methods:
       Piece() (constructor)
       ~Piece() (destructor - pure virtual)
       Piece* copy() (copies a Piece and returns a pointer to it - pure virtual)
       white_piece() (returns true if the Piece is white)
       king_piece() (returns true if the Piece is a King)
       valid_move() (returns true if the Piece can move from the source to the destination - pure virtual)
       move() (changes the value of first_move)
       colour_string() (returns the colour of the Piece as a string)
       piece_string() (returns the Piece as a string - pure virtual)
  */

 public:
  Piece (bool _white);
  virtual ~Piece() = 0;
  virtual Piece* copy() = 0;
  bool white_piece();
  bool king_piece();
  virtual bool valid_move(const string source, const string destination, const map<string, Piece*>* board) = 0;
  void move();
  string colour_string();
  virtual string piece_string() = 0;

  /*
    Protected attributes and methods:
       white (true if the Piece is white)
       king (true if the Piece is a King)
       first_move (true if the Piece hasn't moved yet)
       same_colour() (returns true if other_piece is of the same colour as this)
       same_file() (returns true if source square and destination square have the same file)
       same_rank() (returns true if source square and destination square have the same rank)
       same_diagonal() (returns true if source square and destination square are on the same diagonal)
       no_vertical_obstruction() (returns true if no obstructions between the source square and the destination square)
       no_horizontal_obstruction() (           ""          )
       no_diagonal_obstruction() (           ""           )
       other_piece() (returns true if there is another piece in the destination square)
  */

 protected:
  bool white;
  bool king;
  bool first_move;
  bool same_colour(Piece* other_piece);
  bool same_file(const string source, const string destination);
  bool same_rank(const string source, const string destination);
  bool same_diagonal(const string source, const string destination);
  bool no_vertical_obstruction(const string source, const string destination, const map<string, Piece*>* board);
  bool no_horizontal_obstruction(const string source, const string destination, const map<string, Piece*>* board);
  bool no_diagonal_obstruction(const string source, const string destination, const map<string, Piece*>* board);
  bool other_piece(const string destination, const map<string, Piece*>* board);

};

#endif
