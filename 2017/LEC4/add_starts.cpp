#include <iostream>
#include <vector>

using namespace std;

void add_starts(vector<string> &v) {
  for (int i = 0; i <= v.size(); i += 2) {
    v.insert(v.begin() + i, "*");
  }
}

int main() {

  vector<string> v1{"the"};
  vector<string> v3{"the", "quick", "brown"};
  vector<string> v4{"the", "quick", "brown", "fox"};

  add_starts(v1);

  for (string s : v1) {
    cout << s << ' ';
  }
  cout << endl;

  add_starts(v3);

  for (string s : v3) {
    cout << s << ' ';
  }
  cout << endl;

  add_starts(v4);

  for (string s : v4) {
    cout << s << ' ';
  }
  cout << endl;

  return 0;
}
