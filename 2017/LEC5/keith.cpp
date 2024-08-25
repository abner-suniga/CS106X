#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(vector<int> &v) {
  for (int element : v) {
    cout << element << " ";
  }
  cout << endl;
}

int sum(vector<int> &v) {
  int sum = 0;
  for (int element : v) {
    sum += element;
  }
  return sum;
}

bool is_keith(int n) {
  string digits = to_string(n);
  // cout << digits << endl;
  vector<int> v(digits.length());

  // init vec
  for (int i = 0; i < v.size(); i++) {
    // cout << digits.at(i) << endl;
    v[i] = digits.at(i) - '0';
  }

  int acc = 0;
  while (acc < n) {
    // print(v);

    acc = sum(v);

    // cout << "acc = " << acc << endl;

    // this can be optimized
    v.erase(v.begin());
    v.insert(v.end(), acc);
  }

  // cout << acc << " " << n << endl;

  return acc == n;
}

int main() {

  cout << is_keith(197) << endl;
  cout << is_keith(14) << endl;
  cout << is_keith(7909) << endl;
  cout << is_keith(7385) << endl;

  cout << is_keith(200) << endl;
  cout << is_keith(92) << endl;
  cout << is_keith(7908) << endl;

  return 0;
}
