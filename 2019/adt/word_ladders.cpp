#include <algorithm>
#include <cctype>
#include <cwctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

bool contains(const unordered_set<string> &set, string str) {
  return !(set.find(str) == set.end());
}

vector<string>
generate_valid_one_letter_permutations(unordered_set<string> &dict,
                                       unordered_set<string> &used_words,
                                       string word) {
  vector<string> generated_words;

  for (int i = 0; i < word.length(); i++) {
    for (int j = 0; j < alphabet.length(); j++) {
      string generated_word = word;
      generated_word[i] = alphabet[j];
      if (contains(dict, generated_word) &&
          !contains(used_words, generated_word)) {
        generated_words.push_back(generated_word);
      }
    }
  }

  return generated_words;
}

optional<vector<string>> find_word_ladder(unordered_set<string> &dict,
                                          string source, string destination) {
  vector<string> ladder;
  ladder.push_back(source);

  queue<vector<string>> q;
  q.push(ladder);

  unordered_set<string> used_words;

  while (!q.empty()) {
    vector<string> front_ladder = q.front();
    q.pop();

    string top_word = front_ladder.back();

    if (top_word == destination) {
      return front_ladder;
    } else {
      vector<string> valid_words =
          generate_valid_one_letter_permutations(dict, used_words, top_word);

      for (string word : valid_words) {
        vector<string> ladder = front_ladder;
        ladder.push_back(word);
        used_words.insert(word);
        q.push(ladder);
      }
    }
  }

  return nullopt;
}

void to_lowercase(char &c) { c = tolower(c); }

int main() {

  unordered_set<string> dict;

  ifstream input;
  input.open("dictionary.txt");

  string word;
  while (getline(input, word)) {
    for_each(word.begin(), word.end(), to_lowercase);
    dict.insert(word);
  }

  optional<vector<string>> result = find_word_ladder(dict, "sleep", "awake");
  if (result) {
    for (string word : *result)
      cout << word << " ";
    cout << endl;
  }

  return 0;
}
