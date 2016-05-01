#include <iostream>

using namespace std;

class Expression {

public:
  virtual int value() const = 0;
  virtual int precedence() const = 0;
  virtual void print(ostream &o) const = 0;

};

ostream &operator <<(ostream &o, const Expression &e) {
  e.print(o);
  return o << " = " << e.value();
}

class Number : public Expression {

  int _value;

public:
  Number(int value) : _value(value) {}
  int value() const {
    return _value;
  }
  virtual void print(ostream &o) const {
    o << _value;
  }
  virtual int precedence() const {
    return (_value >= 0 ? 10000 : 10);
  }

};

class LBinary : public Expression {

  Expression &_left, &_right;

protected:
  virtual int calculate(int v1, int v2) const = 0;

public:
  LBinary(Expression &left, Expression &right) : _left(left), _right(right) {}
  Expression &left() const {
    return _left;
  }
  Expression &right() const {
    return _right;
  }
  virtual const char *symbol() const = 0;
  virtual int value() const {
    int left_value = _left.value();
    int right_value = _right.value();
    int result = calculate(left_value, right_value);
    return result;
    // one-line version: return calculate(_left.value(), _right.value());                          
  }
  virtual void print(ostream& o) const {
    bool left_low = _left.precedence() < precedence();
    bool right_low = _right.precedence() <= precedence();
    if (left_low)
      o << "(";
    _left.print(o);
    if (left_low)
      o << ")";
    o << symbol();
    if (right_low)
      o << "(";
    _right.print(o);
    if (right_low)
      o << ")";
  }

};

class Addition : public LBinary {

protected:
  virtual int calculate(int v1, int v2) const {
    return v1 + v2;
  }

public:
  Addition(Expression &left, Expression &right) : LBinary(left, right) {}
  virtual const char *symbol() const {
    return "+";
  }
  virtual int precedence() const {
    return 10;
  }

};

class Multiplication : public LBinary {

protected:
  virtual int calculate(int v1, int v2) const {
    return v1 * v2;
  }

public:
  Multiplication(Expression &l, Expression &r) : LBinary(l, r) {}
  virtual const char *symbol() const {
    return "*";
  }
  virtual int precedence() const {
    return 20;
  }

};

int main() {

  Number n2(2), n3(3), n_1(-1);
  cout << n_1 << endl;

  Addition a1(n2, n_1);
  cout << a1 << endl;

  Addition a2(n_1, n3);
  cout << a2 << endl;

  Multiplication m1(n3, a1);
  cout << m1 << endl;

  Addition a3(m1, a1);
  cout << a3 << endl;

  Addition a4(a1, m1);
  cout << a4 << endl;

}
