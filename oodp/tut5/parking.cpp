#include <iostream>
#include <cstring>

using namespace std;

class Fine {

protected:
  string date;
  string time;
  string reg;
  int code;

public:
  Fine (string d, string t, string r, int c) {
    date = d;
    time = t;
    reg = r;
    code = c;
  }
  virtual double amount() = 0;

};


class Fixed : public Fine {

protected:
  static double fine;

public:
  Fixed (string d, string t, string r, int c) : Fine(d,t,r,c) {
  }

  static void setFine(double x) {
    fine = x;
  }
  static double getFine() {
    return fine;
  }
  virtual double amount() {
    return fine;
  }

};

class Excess : public Fine {

protected:
  int overstay;

public:
  Excess (string d, string t, string r, int c, int o) : Fine(d,t,r,c) {
    overstay = o;
  }

  virtual double amount() {
    int x = 20. + (overstay * 5.);

    return (x < Fixed::getFine() ? x : Fixed::getFine());
  }
};

class Attendant {

protected:
  int badge;
  double fineCount;

public:
  Attendant (int b) {
    badge = b;
    fineCount = 0;
  }

  virtual double salary() = 0;
  void issueFine(Fine &f) {
    fineCount += f.amount();
  }
};

class JuniorAttendant : public Attendant {

public:
  JuniorAttendant (int b) : Attendant(b) {
  }

  double salary() {
    return 900. + (0.05 * fineCount);
  }
};

class SeniorAttendant : public Attendant {

public:
  SeniorAttendant (int b) : Attendant(b) {
  }

  double salary() {
    return 1200. + (0.1 * fineCount);
  }
};

double Fixed::fine = 100;

int main() {


  SeniorAttendant charon(666);
  Fixed f1("16/02/2006", "0950", "LO52RNA", 26);
  charon.issueFine(f1);

  Fixed::setFine(120);

  JuniorAttendant nelson(111);
  Excess f2("17/02/2006", "1015", "B14NCA", 14, 15);
  nelson.issueFine(f2);

  cout << nelson.salary() << endl;

  return 0;

}
