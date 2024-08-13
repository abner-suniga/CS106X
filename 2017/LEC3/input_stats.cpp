#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Line 1 has 30 chars
// Line 2 has 41 chars
// Line 3 has 0 chars
// Line 4 has 31 chars
// Line 5 has 26 chars
// 5 lines; longest = 41, average = 25.6

void inputStats(string filename) {
  ifstream input;
  input.open(filename);

  int counter = 0;
  int longest = 0;
  double sum = 0;
  string line;
  while (getline(input, line)) {
    counter++;
    sum += line.length();

    if (line.length() > longest) {
      longest = line.length();
    }

    cout << "Line " << counter << " has " << line.length() << " chars" << endl;
  }
  cout << counter << " lines; " << "longest = " << longest
       << ", average = " << sum / counter << endl;

  input.close();
}

int main() {
  inputStats("carroll.txt");
  return 0;
}
