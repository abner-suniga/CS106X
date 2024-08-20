#include <iostream>
#include <vector>

using namespace std;

int count_in_range(const vector<int> &v, int min, int max) {
  int count = 0;
  for (int i : v) {
    if (i >= min && i <= max) {
      count++;
    }
  }
  return count;
}

int main() {

  vector<int> v{28, 1, 17, 4, 41, 9, 59, 8, 31, 30, 25};
  cout << count_in_range(v, 10, 30) << endl;

  return 0;
}
