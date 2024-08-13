#include <iostream>
#include <math.h>

using namespace std;

void xkcdDatingRange(int age, int &min, int &max) {
  min = (age / 2) + 7;
  max = (age - 7) * 2;
}

int main() {
  int age, min, max;

  cout << "Enter age: ";
  cin >> age;
  xkcdDatingRange(age, min, max);
  cout << "Min: " << min << endl;
  cout << "Max: " << max << endl;

  return 0;
}
