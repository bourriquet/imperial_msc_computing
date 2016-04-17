#include <iostream>
#include <cstring>

#define TEAMSIZE 4

using namespace	std;

class University {

private:
  string name;

public:
  University(string n) {
    name = n;
  }
  string getName() {
    return name;
  }
};


class Member {

private:
  string name;
  int age;
  bool captain;
  bool registered;
  University *uni;

public:
  Member(string n, University &u, int a, bool r, bool c = false) {
    name = n;
    age = a;
    captain = c;
    registered = r;
    uni = &u;
  }
  int getAge() {
    return age;
  }
  bool isCaptain() {
    return captain;
  }
  bool isValid(string t) {
    return (age >= 18 && age <= 40 && registered && t == uni->getName());
  }
  void changeUni(University &newU) {
    uni = &newU;
  }
  void graduate() {
    uni = NULL;
    registered = false;
  }
};

class Team {

private:
  int member_count;
  Member *members[TEAMSIZE];
  University *uni;

public:
  Team(University &u) {
    uni = &u;
    member_count = 0;
    for (int i = 0; i < TEAMSIZE; i++) {
      members[i] = NULL;
    }
  }
  bool addMember(Member &m) {
    if (member_count >= TEAMSIZE) {
      return false;
    }
    members[member_count] = &m;
    member_count++;
    return true;
  }
  double avgAge() {
    double avg = 0;
    for (int i = 0; i < member_count; i++) {
      avg += members[i]->getAge();
    }
    return avg /= member_count;
  }
  bool isValid() {
    if (member_count != TEAMSIZE)
      return false;
    else if (avgAge() >= 25.0) {
      return false;
    }

    int cap = 0;
    for (int i = 0; i < TEAMSIZE; i++) {
      if (!members[i]->isValid(uni->getName()))
        return false;
      if (members[i]->isCaptain())
        cap++;
    }
    return (cap == 1);
  }
};

int main() {

  University imperial("imperial");
  Team imp(imperial);

  Member ivor("Ivor Bigbrain", imperial, 20, true);
  Member prezza("Prezza Buzza", imperial, 18, true);
  Member ivonna("Ivonna Singh", imperial, 25, true, true);
  Member yuman("Yuman Google", imperial, 32, true);

  imp.addMember(ivor);
  imp.addMember(prezza);
  imp.addMember(ivonna);
  imp.addMember(yuman);

  cout << "Imperial's team is ";
  if (!imp.isValid())
    cout << "not ";
  cout << "a valid team" << endl;

  prezza.graduate();

  cout << "Imperial's team is ";
  if (!imp.isValid())
    cout << "not ";
  cout << "a valid team" << endl;

  return 0;
}
