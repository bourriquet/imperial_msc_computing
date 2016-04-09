#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */

  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << endl << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << endl << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Testing a known valid move... Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << endl << "Testing a move where the coordinates are out of range... Putting '5' into J2 is ";
  if (!make_move("J2", '5', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << endl << "Testing a move where the digit out of range... Putting '0' into B4 is ";
  if (!make_move("B4", '0', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << endl << "Testing a move where the cell is already occupied... Putting '6' into A7 is ";
  if (!make_move("A7", '6', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << endl << "Testing a move where the digit already exists in row/col... Putting '9' into D1 is ";
  if (!make_move("D1", '9', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << endl << "Testing a move where the digit already exists in sub-box... Putting '5' into C6 is ";
  if (!make_move("C6", '5', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  cout << endl << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (save_board("medium-copy.dat", board))
    cout << "Save board to 'medium-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  load_board("mystery1.dat", board);
  if (save_board("mystery1-copy.dat", board))
    cout << "Save board to 'mystery1-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  load_board("mystery2.dat", board);
  if (save_board("mystery2-copy.dat", board))
    cout << "Save board to 'mystery2-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  load_board("mystery3.dat", board);
  if (save_board("mystery3-copy.dat", board))
    cout << "Save board to 'mystery3-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << endl << "====================== Question 4 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery1.dat", board);                                                                                                                       
  if (solve_board(board)) {                                                                                                         
    cout << "The 'mystery1' board has a solution:" << endl;                                                                      
    display_board(board);                                                                                                             
  } else                                                                                                            
    cout << "A solution cannot be found." << endl;                                                                                  
  cout << endl; 

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << endl << "====================== Question 5 ======================" << endl << endl;

  cout << "Here, the difficulty of the puzzle is determined by computing a 'constrained score' and a 'backwards recursion score'." << endl << endl;
  cout << "The constrained score is a direct measure of how many 'valid moves' there are at the start of the puzzle, where a 'valid move' satsifies the Boolean make_move function." << endl;
  cout << "The backwards recursion score is a cumulative counter of how many times the solve_board function backwardly recursed i.e. removed a digit from a cell as it was incorrect." << endl << endl;

  load_board("easy.dat", board);
  int count = 0;
  cout << "Constrained score: " << constrain(board) << endl;
  solve_board(board,count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("medium.dat", board);
  count = 0;
  cout << "Constrained score: " << constrain(board) << endl;
  solve_board(board,count);
  cout << "Backwards recursion score: " << count << endl << endl;
  
  load_board("mystery1.dat", board);
  count = 0;
  cout << "Constrained score: " << constrain(board) << endl;
  solve_board(board,count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("mystery2.dat", board);
  count = 0;
  cout << "Constrained score: " << constrain(board) << endl;
  solve_board(board,count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("mystery3.dat", board);
  count = 0;
  cout << "Constrained score: " << constrain(board) << endl;
  solve_board(board,count);
  cout << "Backwards recursion score: " << count << endl << endl;

  return 0;
}
