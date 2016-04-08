#include <iostream>

using namespace std;

enum Day {Sun, Mon, Tue, Wed, Thu, Fri, Sat};

int closing_time(Day day_of_the_week);
void print_day(Day day_of_the_week, ostream& o);

int main() {

  int count;

  // output the table header
  cout.setf(ios::left);
  cout.width(17);
  cout << "DAY";
  cout << "CLOSING TIME" << endl << endl;

  // print each day in the table
  for (count = static_cast<int>(Sun); count <= static_cast<int>(Sat); count++) {
    cout.width(19);

    print_day(static_cast<Day>(count), cout);
    cout << closing_time(static_cast<Day>(count)) << "pm" << endl;
  }

  return 0;
}

// returns the closing time of day_of_the_week
int closing_time(Day day_of_the_week) {

  switch(day_of_the_week) {                          
  case Sun:                                                                               
    return 1;
    break;                                                                                
  case Mon:                                                                               
  case Tue:                                                                               
  case Thu:
  case Fri:
    return 6;
    break;                                                                                
  case Wed:                                                                               
    return 8;
    break;                                                                                
  case Sat:                                                                               
    return 5;
    break;                                                                                
  default:                                                                                
    cout << "ERROR!";                                                                     
  } 

  return -1;
}

// outputs day_of_the_week to stream o
void print_day(Day day_of_the_week, ostream& o) {

  switch(day_of_the_week) {                                                    
  case Sun:                                                                               
    o << "Sunday";                                                                     
    break;                                                                                
  case Mon:                                                                               
    o << "Monday";                                                                     
    break;                                                                                
  case Tue:                                                                               
    o << "Tuesday";                                                                    
    break;                                                                                
  case Wed:                                                                               
    o << "Wednesday";                                                                  
    break;                                                                                
  case Thu:                                                                               
    o << "Thursday";                                                                   
    break;                                                                                
  case Fri:                                                                               
    o << "Friday";                                                                     
    break;                                                                                
  case Sat:                                                                               
    o << "Saturday";                                                                   
    break;                                                                                
  default:                                                                                
    o << "ERROR!";                                                                 
  }
}

