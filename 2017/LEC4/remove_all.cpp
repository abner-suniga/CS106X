#include <iostream>
#include <vector>

using namespace std;

void remove_all(vector<string> &v, string s) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == s) {
      v.erase(v.begin() + i);
      i--;
    }
  }
}

int main() {
  vector<string> v = {"a", "b", "c", "b", "b", "a", "b"};
  remove_all(v, "b");
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  return 0;
}
