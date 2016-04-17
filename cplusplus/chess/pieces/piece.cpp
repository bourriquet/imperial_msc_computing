/*
  Filename: piece.cpp
  Author: lc3311
  Last updated: 13/12/15

  This implementation file contains the definitions of the methods of the (abstract) Piece class

  Corresponding header file: header/piece.h
*/

#include "header/piece.h"

/*
   CONSTRUCTOR
      Defines whether the Piece is white and sets the first_move boolean
*/
Piece::Piece(bool _white) {
  white = _white;
  first_move = true;
}

/*
  DESTRUCTOR
*/
Piece::~Piece() {

}

/*
  white_piece()
      Public function to return whether the Piece is white or not
*/
bool Piece::white_piece() {
  return white;
}

/*
  king_piece()
      Public function to return whether the Piece is a King or not
*/
bool Piece::king_piece() {
  return king;
}

/*
  move()
      Sets the first_move boolean to false (to ensure correct Pawn implementation)
      Will be called after every move
*/
void Piece::move() {
  first_move = false;
}

/*
  colour_string()
      Returns a string describing the colour of the Piece
*/
string Piece::colour_string() {
  if (white)
    return "White's ";
  else
    return "Black's ";
}

/*
  same_colour()
      Returns true if this Piece and other_piece are the same colour
*/
bool Piece::same_colour(Piece* other_piece) {
  return (this->white == other_piece->white_piece());
}

/*
  same_file()
      Returns true if the source square and destination square have the same file
*/
bool Piece::same_file(const string source, const string destination) {
  return (source[0] == destination[0]);
}

/*
  same_rank()
      Returns true if the source square and destination square have the same rank
*/
bool Piece::same_rank(const string source, const string destination) {
  return (source[1] == destination[1]);
}

/*
  same_diagonal()
      Returns true if the source square and destination square are on the same diagonal
*/
bool Piece::same_diagonal(const string source, const string destination) {
  int file_change = abs(source[0] - destination[0]);
  int rank_change = abs(source[1] - destination[1]);

  // same diagonal iff the change in the file is equal to the change in rank
  return (file_change == rank_change);
}

/*
  no_vertical_obstruction()
      Returns true if there are no obstructions between the source square and the destination square
*/
bool Piece::no_vertical_obstruction(const string source, const string destination, const map<string, Piece*>* board) {
  char source_file = source[0];
  char source_rank = source[1];
  char destination_rank = destination[1];
  char rank_low = (source_rank < destination_rank) ? source_rank : destination_rank;
  char rank_high = (source_rank < destination_rank) ? destination_rank : source_rank; 

  // loop through every square between rank_low and rank_high (exclusively) and check if there are any
  // entries in the Board map
  for (char i = rank_low + 1; i < rank_high; i++) {
    string check_obstructions = string() + source_file + i;
    try {
      board->at(check_obstructions);
      // if here, there is another Piece obstructing
      return false;
    } catch (const std::out_of_range &error) {
      // there is no piece obstructing - do nothing
    }
  }
  return true;
}

/*                                        
  no_horizontal_obstruction()                                                
      Returns true if there are no obstructions between the source square and the destination square
*/
bool Piece::no_horizontal_obstruction(const string source, const string destination, const map<string, Piece*>* board) {
  char source_file = source[0];
  char source_rank = source[1];
  char destination_file = destination[0];
  char file_low = (source_file < destination_file) ? source_file : destination_file;
  char file_high = (source_file < destination_file) ? destination_file : source_file;

  // loop through every square between file_low and file_high (exclusively) and check if there are
  // any entries in the Board map
  for (char i = file_low + 1; i < file_high; i++) {
    string check_obstructions = string() + i + source_rank ;
    try {
      board->at(check_obstructions);
      // if here, there is another Piece obstructing
      return false;
    } catch (const std::out_of_range &error) {
      // there is no piece obstructing - do nothing
    }
  }
  return true;
}

/*                                
  no_horizontal_obstruction()                                                     
      Returns true if there are no obstructions between the source square and the destination square
*/
bool Piece::no_diagonal_obstruction(const string source, const string destination, const map<string, Piece*>* board) {
  char source_file = source[0];
  char source_rank = source[1];
  char destination_file = destination[0];
  char destination_rank = destination[1];

  char file_low = (source_file < destination_file) ? source_file : destination_file;
  char file_high = (source_file < destination_file) ? destination_file : source_file;
  char rank_low = (source_rank < destination_rank) ? source_rank : destination_rank;
  char rank_high = (source_rank < destination_rank) ? destination_rank : source_rank;

  // return true if the diagonal is positive
  bool positive = (destination_file - source_file) == (destination_rank - source_rank);
  string check_obstructions;

  // loop through every square on the diagonal
  for (int i = 1; i < (file_high - file_low); i++) {
    if (positive) {
      check_obstructions = string() + (char) (file_low + i) + (char) (rank_low + i);
    } else {
      check_obstructions = string() + (char) (file_low + i) + (char) (rank_high - i);
    }
    try {
      board->at(check_obstructions);
      // if here, there is another Piece obstructing
      return false;
    } catch (const std::out_of_range &error) {
      // there is no piece obstructing - do nothing
    }
  } 
  return true;
}

/*
  other_piece()
      Returns true if there is another Piece of the same colour at the destination square
      If another Piece of the other colour, return false
*/
bool Piece::other_piece(const string destination, const map<string, Piece*>* board) {
  try {
    if (same_colour(board->at(destination))) {
      // there is another Piece of the same colour
      return true;
    }
  } catch (const std::out_of_range &error) {
    // there is no Piece at the destination square
  }
  return false;
}

