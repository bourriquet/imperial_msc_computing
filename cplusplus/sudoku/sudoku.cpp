/* Author: lc3311                                                                                                                                                                      
   Last Update: 09/04/2016                                                                                                                                                            
                                                                                                                                                                                       
   This sudoku.cpp implementation file contains:                                                                                                                                       
   - the pre-supplied functions provided in the skeleton files                                                                                                                         
   - the primary functions used to answer the coursework questions                                                                                                                     
   - helper functions used within the primary functions                                                                                                                                
                                                                                                                                                                                       
   Where I have created my own helper functions, these are defined at the bottom of this file */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own                                                                                                                         
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++)
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* QUESTION 1                                                                                                                                                                          
   This function returns 'true' if the Sudoku board is complete (all cells occupied by digits) and 'false' otherwise */

bool is_complete(const char board[9][9]) {

  // loop through every cell and return false if the cell contains an invalid digit                                                                                                    
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (!(board[r][c] >= '1' && board[r][c] <= '9'))
        return false;
    }
  }
  return true;
}

/* QUESTION 2                                                                                                                                                                          
   This function attempts to place a digit onto the Sudoku board. If the move is valid, the function returns 'true', else, the function returns 'false'.                               
   A move is considered invalid if:                                                                                                                                                    
    - its coordinates are out of range                                                                                                                                                 
    - the digit is < 1 or > 9                                                                                                                                                          
    - the cell is already occupied by a digit                                                                                                                                          
    - the digit already exists in the row or column                                                                                                                                    
    - the digit already exists in the 3x3 sub-board */
    
bool make_move(const char position[2], char digit, char board[9][9]) {

  // convert the position string to a row integer and a column integer                                                                                                                 
  const int row = (char) (position[0] - 'A');
  const int col = (char) (position[1] - '1');

  // check if the coordinates are in range                                                                                                                                             
  if (row < 0 || row > 8 || col < 0 || col > 8)
    return false;

  // check if the digit is in range                                                                                                                                                    
  if (digit < '1' || digit > '9')
    return false;

  // check if the cell is already occupied                                                                                                                                             
  if (!cell_empty(row,col,board))
    return false;

  // check the rows and columns to see if the digit already exists                                                                                                                     
  if (!check_row_col(row,col,digit,board))
    return false;

  // check the sub-boxes to see if the digit already exists                                                                                                                            
  if (!check_subbox(row,col,digit,board))
    return false;

  // else, the digit can be placed                                                                                                                                                     
  board[row][col] = digit;
  return true;
}

/* QUESTION 3                                                                                                                                                                          
   This function saves the board to another file and checks if the save was successful */

bool save_board(const char filename[], const char board[9][9]) {

  ofstream out_stream(filename);

  if (out_stream.fail())
    return false;

  // for every board cell, write the contents to the file                                                                                                                              
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      out_stream.put(board[r][c]);
    }
    out_stream << endl;
  }
  out_stream.close();

  if (out_stream.fail())
    return false;

  // else, the file has saved                                                                                                                                                          
  return true;
}

/* QUESTION 4                                                                                                                                                                          
   This function attempts to solve the board by testing a digit in the first empty cell of the board. It will then attempt to solve the board again.                                   
   As the function is recursive, if it encounters any errors, it can return to a previous state to remove the invalid digit */

bool solve_board(char board[9][9]) {

  int row = 0;
  int col = 0;

  // if the board is complete, the board is solved - therefore return 'true'                                                                                                           
  if (is_complete(board))
    return true;

  // find the next empty cell to place a digit in                                                                                                                                      
  find_next_empty(row, col, board);

  // try each digit in the empty cell                                                                                                                                                  
  for (int num = 1; num <= 9; num++) {
    // if the move is valid, try it                                                                                                                                                    
    if (make_move(row,col,num,board)) {
      board[row][col] = '0' + num;
      // if the digit solves the board, return 'true'                                                                                                                                  
      if (solve_board(board))
        return true;
      // else, the function will return and empty the cell again                                                                                                                       
      board[row][col] = '.';
    }
  }
  // if else, the board has no solution - every digit has been tried                                                                                                                   
  return false;
}

/* QUESTION 5                                                                                                                                                                          
   This function is a polymorph of the solve_board function in question 4 - it counts how many times the function has backwardly recursed */

bool solve_board(char board[9][9], int& count) {

  int row, col;

  if (is_complete(board))
    return true;

  find_next_empty(row, col, board);

  for (int num = 1; num <= 9; num++) {

    if (make_move(row,col,num,board)) {
      board[row][col] = '0' + num;

      if (solve_board(board, count))
        return true;

      // the function has backwardly recursed, hence increase the counter                                                                                                              
      count++;
      board[row][col] = '.';
    }
  }
  return false;
}

/* This function computes the 'constrained score' of the board i.e. how many valid moves are there */
int constrain(char board[9][9]) {

  // initialise the valid move count                                                                                                                                                   
  int valid_num = 0;

  // for every board cell, count the number of valid moves                                                                                                                             
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      for (int i = 1; i < 10; i++) {
        if (make_move(r,c,i,board))
          valid_num++;
      }
    }
  }
  // return the total number of valid moves                                                                                                                                            
  return valid_num;
}


/* HELPER FUNCTIONS */

/* This function returns 'true' if the cell is empty (contains a '.') and false otherwise */
bool cell_empty(int row, int col, const char board[9][9]) {
  // if the cell contains a '.', it is considered empty                                                                                                                                
  if (board[row][col] == '.')
    return true;
  return false;
}

/* This function checks the rows and columns of a cell and returns 'false' if the digit already exists */
bool check_row_col(int row, int col, char digit, const char board[9][9]) {
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == digit)
      return false;
    if (board[i][col] == digit)
      return false;
  }
  return true;
}

/* This function checks the sub-box of a cell and returns 'false' if the digit already exists */
bool check_subbox(int row, int col, char digit, const char board[9][9]) {
  // the 'remainders' of a row and column when divided by 3, gives a cell its relative position within a sub-box... this can be manipulated to check its sub-box for a digit           
  int row_remainder = row % 3;
  int col_remainder = col % 3;

  int row_low = row - row_remainder;
  int row_high = row - row_remainder + 2;
  int col_low = col - col_remainder;
  int col_high = col - col_remainder + 2;

  // if any of the other cells in the sub-box contain the digit, return 'false'                                                                                                        
  for (int r = row_low; r <= row_high; r++) {
    for (int c = col_low; c <= col_high; c++) {
      if (board[r][c] == digit)
        return false;
    }
  }
  // else, digit can be placed in that cell                                                                                                                                            
  return true;
}

/* This function is a polymorph of the make_move function in question 2, so that integer rows, columns and digits can be passed in                                                     
   This function does not make the move */
bool make_move(int row, int col, int digit, const char board[9][9]) {

  char dig = '0' + digit;

  // check if the coordinates are in range                                                                                                                                             
  if (row < 0 || row > 8 || col < 0 || col > 8)
    return false;

  // check if the digit is in range                                                                                                                                                    
  if (dig < '1' || dig > '9')
    return false;

  // check if the cell is already occupied                                                                                                                                             
  if (!cell_empty(row,col,board))
    return false;

  // check the rows and columns to see if the digit already exists                                                                                                                     
  if (!check_row_col(row,col,dig,board))
    return false;

  // check the sub-box to see if the digit already exists                                                                                                                              
  if (!check_subbox(row,col,dig,board))
    return false;

  //else, the digit can be placed                                                                                                                                                      
  return true;
}

/* This function finds the next empty cell in the board - alters row and col initialised in the main function so that they reflect the empty cell */
void find_next_empty(int& row, int& col, const char board[9][9]) {

  // loop through every cell in the board, if its empty then return its coordinates                                                                                                    
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (cell_empty(r,c,board)) {
        row = r;
        col = c;
        return;
      }
    }
  }
}
