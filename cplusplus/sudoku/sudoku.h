/* Author: lc3311                                                                                                                                                                      
   Last Update: 09/04/2016                                                                                                                                                             
                                                                                                                                                                                       
   This sudoku.h header file declares the pre-supplied functions, as well as the functions used to answer the coursework questions, split into primary and helper functions */

// declarations of pre-supplied functions                                                                                                                                              
void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);

// declarations of primary functions used to answer the coursework questions                                                                                                           
bool is_complete(const char board[9][9]);
bool make_move(const char position[2], char digit, char board[9][9]);
bool save_board(const char filename[], const char board[9][9]);
bool solve_board(char board[9][9]);
bool solve_board(char board[9][9], int& count);
int constrain(char board[9][9]);

//declarations of helper functions                                                                                                                                                     
bool cell_empty(int row, int col, const char board[9][9]);
bool check_row_col(int row, int col, char digit, const char board[9][9]);
bool check_subbox(int row, int col, char digit, const char board[9][9]);
bool make_move(int row, int col, int digit, const char board[9][9]);
void find_next_empty(int& row, int& col, const char board[9][9]);
