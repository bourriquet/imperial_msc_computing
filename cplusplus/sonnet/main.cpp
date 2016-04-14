/*
PROVIDED FILE
*/

#include <iostream>

using namespace std;

#include "sonnet.h"

int main() {

  // this section illustrates the use of the pre-supplied functions                                               
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  char word[512];
  bool success = get_word("One, two, three!", 2, word);
  if (success)
    cout << "Word number 2 in \"One, two, three!\" is " << word << endl;
  else
    cout << "Word number 2 in \"One, two, three!\" does not exist." << endl;
  success = get_word("One, two, three!", 4, word);
  if (success)
    cout << "Word number 4 in \"One, two, three!\" is " << word << endl;
  else
    cout << "Word number 4 in \"One, two, three!\" does not exist." << endl;

  cout << endl;

  rhyming_letter(RESET);
  char one = rhyming_letter("AY");
  char two = rhyming_letter("ATE");
  char three = rhyming_letter("AY");
  char four = rhyming_letter("ATE");
  cout << "Rhyming letters for AY, ATE, AY and ATE are " << one << ", " << two << ", " << three << ", " << four <\
< endl;

  cout << endl;

  // Question 1                                                                                                   
  cout << "====================== Question 1 ======================" << endl << endl;

  cout << "The line \"It's  not so easy!\" contains ";
  cout << count_words("It's  not so easy!") << " words" << endl;
  cout << "The line \"\" contains ";
  cout << count_words("") << " words" << endl;
  cout << "The line \"Shall I compare thee to a Summer's day?\" contains ";
  cout << count_words("Shall I compare thee to a Summer's day?") << " words" << endl;

  cout << endl;

  // Question 2                                                                                                   
  cout << "====================== Question 2 ======================" << endl << endl;

  char phonetics[512];
  find_phonetic_ending("DAY", phonetics);
  cout << "DAY has phonetic ending " << phonetics << endl;

  find_phonetic_ending("MAY", phonetics);
  cout << "MAY has phonetic ending " << phonetics << endl;

  find_phonetic_ending("CONVICT", phonetics);
  cout << "CONVICT has phonetic ending " << phonetics << endl;

  find_phonetic_ending("PICKED", phonetics);
  cout << "PICKED has phonetic ending " << phonetics << endl;

  find_phonetic_ending("FLAWS", phonetics);
  cout << "FLAWS has phonetic ending " << phonetics << endl;

  find_phonetic_ending("PAUSE", phonetics);
  cout << "PAUSE has phonetic ending " << phonetics << endl;

  cout << endl;

  // Question 3                                                                                                   
  cout << "====================== Question 3 ======================" << endl << endl;

  char scheme[512];
  find_rhyme_scheme("shakespeare.txt", scheme);
  cout << "The rhyme scheme of shakespeare.txt is " << scheme << endl;

  find_rhyme_scheme("petrarch.txt", scheme);
  cout << "The rhyme scheme of petrarch.txt is " << scheme << endl;

  find_rhyme_scheme("spenser.txt", scheme);
  cout << "The rhyme scheme of spenser.txt is " << scheme << endl;

  cout << endl;

  // Question 4                                                                                                   
  cout << "====================== Question 4 ======================" << endl << endl;

  cout << "The sonnet spenser.txt is a(n) " <<
    identify_sonnet("spenser.txt") << " sonnet" << endl;

  cout << "The sonnet mystery.txt is a(n) " <<
    identify_sonnet("mystery.txt") << " sonnet" << endl;

  cout << endl;

  cout << "======================= The End ========================" << endl << endl;

  return 0;
}
