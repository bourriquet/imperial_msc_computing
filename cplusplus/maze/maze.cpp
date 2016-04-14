#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (maze[i][j] == ch) {
        row = i;
        column = j;
        return true;
      }
    }
  }
  row = -1;
  column = -1;
  return false;
}

char next_pos(int& row, int& col, char dir, char** maze, int height, int width) {

  switch(dir) {
  case 'N':
    row--;
    break;
  case 'S':
    row++;
    break;
  case 'E':
    col++;
    break;
  case 'W':
    col--;
    break;
  }
  if (!valid_move(maze, row, col, height, width))
    return '.';

  return maze[row][col];

}

bool valid_solution(const char* path, char** maze, int height, int width) {

  int row = 0;
  int col = 0;

  find_marker('>', maze, height, width, row, col);

  for (unsigned int i = 0; i < strlen(path); i++) {
    if (next_pos(row, col, path[i], maze, height, width) == '.')
      return false;

    if ((maze[row][col] == ' ') && (path[i+1] == '\0'))
      return false;

    if ((maze[row][col] == 'X') && (path[i+1] != '\0'))
      return false;
  }
  return true;
}

std::string find_path(char** maze, int height, int width, char start, char end) {

  int row = 0;
  int col = 0;

  int max_path = height * width;
  char path[max_path];
  char pos;
  strcpy(path, "");

  find_marker(start, maze, height, width, row, col);
  pos = maze[row][col];

  if (!find_marker(start,maze, height, width, row, col))
    return "can't find start";

  if (!free_path(maze, pos, row, col, 0, start, end, path, height, width))
    return "no solution";

  string solution = path;

  return solution;

}

const char* free_directions(char** maze, int row, int col, int height, int width) {

  char dir[4];
  strcpy(dir, "");

  if (valid_move(maze, row-1, col, height, width))
    strcat(dir, "N");

  if (valid_move(maze, row+1, col, height, width))
    strcat(dir, "S");

  if (valid_move(maze, row, col-1, height, width))
    strcat(dir, "W");

  if (valid_move(maze, row, col+1, height, width))
    strcat(dir, "E");

  const char* str = dir;

  return str;
}

bool free_path(char** maze, char pos, int row, int col, int length, char start, char end\
, char* path, int height, int width) {

  // found the end position                                                              
  if (pos == end) {
    path[length] = '\0';
    return true;
  }

  char dir[4];
  strcpy(dir, free_directions(maze, row, col, height, width));

  if (strcmp(dir, "") == 0) {

    // tried everything                                                                  
    if (pos == start || strcmp(path, "") == 0)
      return false;

    // been there                                                                        
    maze[row][col] = '.';

    // go back one                                                                       
    pos = next_pos(row, col, opposite(path[length-1]), maze, height, width);

    // edit path                                                                         
    path[length-1] = '\0';
    length--;
    return free_path(maze, pos, row, col, length, start, end, path, height, width);

  }

  if (maze[row][col] == ' ')
    maze[row][col] = '#';

  pos = next_pos(row, col, dir[0], maze, height, width);

  path[length] = dir[0];
  length++;

  return free_path(maze, pos, row, col, length, start, end, path, height, width);

}

bool valid_move(char** maze, int row, int col, int height, int width) {

  if ((row < 0) || (row > height) || (col < 0) || (col > width)) {
    return false;
  }
  if ((maze[row][col] != ' ') && (maze[row][col] != 'X'))
    return false;

  return true;

}

char opposite(char dir) {

  if (dir == 'N')
    return 'S';
  else if (dir == 'E')
    return 'W';
  else if (dir == 'W')
    return 'E';
  else if (dir == 'S')
    return 'N';

  return 'x';

}
