#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

// own functions

int count_words(const char* line) {

  int count = 0;
  char word[100];


  for (int i = 1; get_word(line, i, word) != 0; i++) {
    count++;
  }

  return count;
}

bool find_phonetic_ending(const char* word, char* phonetic_ending) {

  char line[100];
  char word2[100];

  bool found = false;

  strcpy(phonetic_ending, "");

  ifstream in;
  in.open("dictionary.txt");

  while (!(in.fail())) {
    // go through every line                                                                                      
    in.getline(line, 100);

    get_word(line, 1, word2);

    if (strcmp(word, word2) == 0) {
      found = true;
      break;
    }
  }
  in.close();

  if (!found)
    return false;

  int num_words = count_words(line);
  int loc_last_vowel = 0;
  char w[100];

  for (int i = num_words; i > 1; i--) {
    get_word(line, i, w);
    if (contains_vowel(w)) {
      loc_last_vowel = i;
      break;
    }
  }

  for (int i = loc_last_vowel; i <= num_words; i++) {
    get_word(line, i, w);
    strcat(phonetic_ending, w);
  }

  return true;

}

bool contains_vowel(const char* word) {

  int len = strlen(word);

  for (int i = 0; i < len; i++) {
    char check = tolower(word[i]);

    switch(check) {

    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return true;
    }
  }
  return false;
}

bool find_rhyme_scheme(const char* filename, char* scheme) {

  ifstream in;
  char line[512];
  char word[100];
  char ending[100];
  char end[1];

  rhyming_letter(RESET);

  strcpy(scheme, "");

  in.open(filename);
  if (in.fail())
    return false;

  while (!in.fail()) {
    in.getline(line, 512);

    if (strlen(line) == 0)
      break;

    int num_words = count_words(line);
    get_word(line, num_words, word);

    find_phonetic_ending(word, ending);
    
    end[0] = rhyming_letter(ending);
    end[1] = '\0';

    strcat(scheme, end);
  }

  in.close();

  return true;

}

const char* identify_sonnet(const char* filename) {

  char shakespeare[20];
  char petrarchan[20];
  char spenserian[20];
  char scheme[100];

  find_rhyme_scheme("shakespeare.txt", shakespeare);
  find_rhyme_scheme("petrarch.txt", petrarchan);
  find_rhyme_scheme("spenser.txt", spenserian);

  ifstream in;
  in.open(filename);

  if (in.fail()) {
    return "Unknown";
  }
  in.close();

  find_rhyme_scheme(filename, scheme);


  if (strcmp(shakespeare, scheme) == 0) {
    return "Shakespearean";
  }
  else if (strcmp(petrarchan, scheme) == 0) {
    return "Petrarchan";
  }
  else if (strcmp(spenserian, scheme) == 0) {
    return "Spenserian";
  }
  else
    return "Unknown";

}
