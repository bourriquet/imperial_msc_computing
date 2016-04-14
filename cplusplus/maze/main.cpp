/*
PROVIDED FILE
*/

#include <iostream>
#include <cassert>
#include "maze.h"

using namespace std;

int main() {

  /* this section illustrates the use of the pre-supplied functions */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  char **maze;
  int height, width;

  cout << "Loading simple maze...";
  /* loads the maze from the file "simple.txt" and sets height and width */
  maze = load_maze("simple.txt", height, width);
  assert(maze);
  cout << " done (height = " << height << ", width = " << width << ")." << endl << endl;

  cout << "Printing simple maze:" << endl;
  /* prints the maze with row and column numbers */
  print_maze(maze,height,width);
  cout << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  int row = 0, column = 0;
  cout << "Finding the entrance:" << endl;
  find_marker('>', maze, height, width, row, column);
  cout << "The entrance is at row " << row << " column " << column << endl << endl;

  cout << "Finding the exit:" << endl;
  find_marker('X', maze, height, width, row, column);
  cout << "The exit is at row " << row << " column " << column << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  cout << "The move sequence 'EEEEESEENN' is ";
  if (!valid_solution("EEEEESEENN", maze, height, width))
    cout << "NOT ";
  cout << "a solution to the maze" << endl << endl;

  cout << "The move sequence 'EEEEEEEESSSSSS' is ";
  if (!valid_solution("EEEEEEEESSSSSS", maze, height, width))
    cout << "NOT ";
  cout << "a solution to the maze" << endl << endl;

  cout << "The move sequence 'ESSSSSSEEEEEEE' is ";
  if (!valid_solution("ESSSSSSEEEEEEE", maze, height, width))
    cout << "NOT ";
  cout << "a solution to the maze" << endl << endl;

  cout << "====================== Question 3 ======================" << endl << endl;

  /* an easy example with a known solution */
  cout << "A path through the maze from '>' to 'X' is: " << endl;
  cout << find_path(maze, height, width, '>', 'X') << endl << endl;

  cout << "The path is shown below: " << endl;
  print_maze(maze, height, width);
  cout << endl;

  deallocate_2D_array(maze, height);

  /* an impossible example - should return "no solution" */ 
  maze = load_maze("simple.txt", height, width);
  assert(maze);

  cout << "A path through the maze from '>' to 'U' is: " << endl;
  cout << find_path(maze, height, width, '>', 'U') << endl << endl;

  deallocate_2D_array(maze, height);
  
  cout << "=================== Bonus Question =====================" << endl << endl;

  /* find the path from the entrance to the middle of the Hatfield House maze */
  maze = load_maze("hatfield.txt", height, width);
  assert(maze);

  cout << "And now the Hatfield House maze:" << endl;
  print_maze(maze, height, width);
  cout << endl;
  
  cout << "A path through the maze from '>' to 'M' is: " << endl;
  cout << find_path(maze, height, width, '>', 'M') << endl << endl;

  cout << "The path is shown below: " << endl;
  print_maze(maze, height, width);
  cout << endl;

  deallocate_2D_array(maze, height);

  /* find the path from the middle to the exit of the Hatfield House maze */
  maze = load_maze("hatfield.txt", height, width);
  assert(maze);

  cout << "A path through the maze from 'M' to 'X' is: " << endl;
  cout << find_path(maze, height, width, 'M', 'X') << endl << endl;
  
  cout << "The path is shown below: " << endl;
  print_maze(maze, height, width);
  cout << endl;
  
  deallocate_2D_array(maze, height);

  cout << "======================= The End ========================" << endl << endl;

  return 0;
}
