#include <iostream>

using namespace std;


class Room {

private:
  Room *east;
  Room *west;

public:
  Room() {
  }

  void connectEast(Room *R) {
    east = R;
    R->setWest(this);
  }
  void connectWest(Room *R) {
    west = R;
    R->setEast(this);
  }
  void setEast(Room *R) {
    east = R;
  }
  void setWest(Room *R) {
    west = R;
  }
  Room* getEast() {
    return east;
  }
  Room* getWest() {
    return west;
  }

};

class Lemming {

private:
  bool DLM;
  Room *loc;

public:
  Lemming(Room *r) {
    DLM = true;                 // DLM = east                                                     
    loc = r;
  }
  void goEast() {
    loc = loc->getEast();
  }
  void goWest() {
    loc = loc->getWest();
  }
  void wakeUp() {
    if (DLM)
      goEast();
    else
      goWest();
  }
  void changeDLM() {
    DLM = !DLM;
  }

};

int main() {

  Room r0, r1, r2;

  r0.connectWest(&r1);
  r1.connectWest(&r2);
  r2.connectWest(&r0);

  Lemming lala(&r0), lilo(&r2);

  lilo.wakeUp();
  lilo.wakeUp();
  lala.wakeUp();
  lala.changeDLM();
  lilo.wakeUp();

  return 0;
}
