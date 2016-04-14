#ifndef MAZE
#define MAZE

#include <string>

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column);
bool valid_solution(const char* path, char** maze, int height, int width);
std::string find_path(char** maze, int height, int width, char start, char end);

bool valid_move(char** maze, int row, int col, int height, int width);
const char* free_directions(char** maze, int row, int col, int height, int width);
bool free_path(char** maze, char pos, int row, int col, int length, char start, char end\
, char* path, int height, int width);
char opposite(char dir);
char next_pos(int& row, int& col, char dir, char** maze, int height, int width);

#endif
