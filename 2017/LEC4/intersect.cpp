#include <iostream>
#include <vector>

using namespace std;

vector<int> intersect(const vector<int> &v1, const vector<int> &v2) {
  int i = 0, j = 0;
  vector<int> v_result{};

  while (i < v1.size() && j < v2.size()) {
    if (v1[i] == v2[j]) {
      v_result.push_back(v1[i]);
      i++;
      j++;
    } else if (v1[i] > v2[j]) {
      j++;
    } else if (v1[i] < v2[j]) {
      i++;
    }
  }

  return v_result;
}

int main() {

  vector<int> v1 = {1, 4, 8, 9, 11, 15, 17, 28, 41, 59};
  vector<int> v2 = {4, 7, 11, 17, 19, 20, 23, 28, 37, 59, 81};

  vector<int> v3 = intersect(v1, v2);

  for (int s : v3) {
    cout << s << ' ';
  }
  cout << endl;

  return 0;
}
