#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Definition {
public:
  string name;
  vector<string> productions;

  Definition() : name(""), productions() {}

  Definition(string name, vector<string> productions)
      : name(name), productions(productions) {}

  void info() {
    cout << "name: " << name << endl;
    cout << "productions: " << endl;
    for (string p : productions) {
      cout << p << endl;
    }
    cout << endl;
  }

  string resolve(map<string, Definition> &definitions) {

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(
        0, productions.size() - 1);

    int p = dist(rng);
    string production = productions[p];

    string result = "";
    string current_non_terminal = "";
    bool in_non_terminal = false;

    for (char c : production) {
      if (c == '<') {
        current_non_terminal += c;
        in_non_terminal = true;
      } else if (c == '>') {
        current_non_terminal += c;
        in_non_terminal = false;
        string resolved =
            definitions[current_non_terminal].resolve(definitions);
        result += resolved;
        current_non_terminal = "";
      } else if (in_non_terminal) {
        current_non_terminal += c;
      } else {
        result += c;
      }
    }

    return result;
  }
};

// bond.g
// dance.g
// excuse.g
// news.g
// poem.g
// politics.g
// rejection.g
// startup.g
// subway.g

int main() {

  map<string, Definition> definitions;

  ifstream input;
  input.open("grammars/bond.g");

  string definition, productions_length, production;
  while (getline(input, definition)) {
    if (definition[0] == '<' && definition[definition.length() - 1] == '>') {
      getline(input, productions_length);

      vector<string> productions;
      for (int i = 0; i < stoi(productions_length); i++) {
        getline(input, production);
        productions.push_back(production);
      }

      Definition def(definition, productions);
      definitions[definition] = def;
      def.info();
    }
  }

  string result = definitions["<start>"].resolve(definitions);

  cout << "sequence generated: " << endl << result << endl;

  return 0;
}
