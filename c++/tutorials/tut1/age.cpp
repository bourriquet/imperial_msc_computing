#include <iostream>

using namespace std;

int main() {

  int year_now, age_now, another_year;
  int month_now, month_born, another_month;
  int now_months, extra_months, total_months, total_years;

  // user inputs
  cout << "Enter the current year then press RETURN." << endl;
  cin >> year_now;

  cout << "Enter the current month (a number from 1 to 12)." << endl;
  cin >> month_now;

  cout << "Enter your current age in years." << endl;
  cin >> age_now;

  cout << "Enter the month in which you were born (a number from 1 to 12)." << endl;
  cin >> month_born;

  cout << "Enter the year for which you wish to know your age." << endl;
  cin >> another_year;

  cout << "Enter the month in this year" << endl;
  cin >> another_month;

  // calculate the user's current age in months
  now_months = (age_now * 12) + (month_now - month_born);

  // add 12 months if the user hasn't had their birthday this year yet
  if ((month_now - month_born) < 0)
    now_months += 12;

  // calculate how many months have passed (or will pass)
  extra_months = ((another_year * 12) + another_month) - ((year_now * 12) + month_now);

  // calculate how old the user will be
  total_months = now_months + extra_months;
  total_years = total_months / 12;

  // output a message depending on the user's age
  if (total_years > 150) {
    cout << "Sorry, but you'll probably be dead by ";
    cout << another_year << endl;
  }
  else if (total_months >= 0) {
    cout << "Your age in " << another_month << "/" << another_year << ": ";
    cout << total_years << " year";
    if (total_years != 1)
      cout << "s";
    cout << " and " << (total_months % 12) << " month";
    if ((total_months % 12) != 1)
      cout << "s";
    cout << "." << endl;
  }
  else {
    cout << "You weren't born in ";
    cout << another_month << "/" << another_year << "!" << endl;
  }

  return 0;
}
