#define RESET NULL

bool get_word(const char *input_line, int number, char *output_word);
char rhyming_letter(const char *ending);
int count_words(const char* line);
bool find_phonetic_ending(const char* word, char* phonetic_ending);
bool contains_vowel(const char* word);
bool find_rhyme_scheme(const char* filename, char* scheme);
const char* identify_sonnet(const char* filename);



