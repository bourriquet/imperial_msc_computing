#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] == target) {
        r = i;
        c = j;
        return true;
      }
    }
  }

  r = -1;
  c = -1;

  return false;
}

char get_symbol_for_station_or_line(const char* name) {

  ifstream in;
  char line[40];
  char* name2;

  in.open("stations.txt");

  while (!in.fail()) {
    in.getline(line, 40);

    if (strlen(line) == 0)
      break;

    name2 = (line + 2);

    if (strcmp(name2, name) == 0)
      return line[0];
  }
  in.close();
  
  in.open("lines.txt");

  while (!in.fail()) {
    in.getline(line, 40);

    if (strlen(line) == 0)
      break;

    name2 = (line + 2);

    if (strcmp(name2, name) == 0)
      return line[0];
  }
  in.close();

  return ' ';
}

int validate_route(char** map, int height, int width, const char* start_station, const char\
* route, char* destination) {


  int len = strlen(route);

  char traverse[len];
  int count = 0;

  int row, col;
  char start;
  char end;

  int change_count = 0;

  char next_dir[3];
  char prev_dir[3];
  strcpy(prev_dir, "");

  strcpy(destination, "");

  start = get_symbol_for_station_or_line(start_station);
  if (start == ' ' || !(isalnum(start)))
    return ERROR_START_STATION_INVALID;

  traverse[count] = start;

  get_symbol_position(map, height, width, start, row, col);
  
    for (int i = 0; i < len; i++) {
    int dir = 0;

    next_dir[0] = route[i];
    dir++;

    if (route[i+1] != ',') {
      next_dir[1] = route[i+1];
      i++;
      dir++;
    }

    next_dir[dir] = '\0';
    i++;

    if (is_opposite(prev_dir, next_dir)) {
      if (!(isalnum(map[row][col])))
        return ERROR_BACKTRACKING_BETWEEN_STATIONS;

    }

    int next = string_to_direction(next_dir);

    switch(next) {

    case(0):
      row--;
      break;
    case(1):
      row++;
      break;
    case(2):
      col--;
      break;
    case(3):
      col++;
      break;
    case(4):
      row--;
      col++;
      break;
    case(5):
      row--;
      col--;
      break;
    case(6):
      row++;
      col++;
      break;
    case(7):
      row++;
      col--;
      break;
    default:
      return ERROR_INVALID_DIRECTION;
    }

    if (row < 0 || row > height || col < 0 || col > width)
      return ERROR_OUT_OF_BOUNDS;

    count++;
    traverse[count] = map[row][col];

    // if a line                                                                            
    if (!isalnum(traverse[count])) {
      // if previous is also a line and not equal                                           
      if (!isalnum(traverse[count-1]) && (traverse[count] != traverse[count-1]))
        return ERROR_LINE_HOPPING_BETWEEN_STATIONS;

      if (isalnum(traverse[count-1]) && (!isalnum(traverse[count-2])) && count > 1)
        change_count++;
    }
    strcpy(prev_dir, next_dir);

  }

  end = map[row][col];

  if (!isalnum(end))
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;

  count++;
  traverse[count] = '\0';


  return change_count;

}

bool is_opposite(const char* forwards, const char* backwards) {
  if ((strcmp(forwards,"N") == 0) && (strcmp(backwards,"S") == 0))
    return true;
  if ((strcmp(forwards,"E") == 0) && (strcmp(backwards,"W") == 0))
    return true;
  if ((strcmp(forwards,"S") == 0) && (strcmp(backwards,"N") == 0))
    return true;
  if ((strcmp(forwards,"W") == 0) && (strcmp(backwards,"W") == 0))
    return true;
  if ((strcmp(forwards,"NE") == 0) && (strcmp(backwards,"SW") == 0))
    return true;
  if ((strcmp(forwards,"SE") == 0) && (strcmp(backwards,"NW") == 0))
    return true;
  if ((strcmp(forwards,"SW") == 0) && (strcmp(backwards,"NE") == 0))
    return true;
  if ((strcmp(forwards,"NW") == 0) && (strcmp(backwards,"SE") == 0))
    return true;

  return false;
}
