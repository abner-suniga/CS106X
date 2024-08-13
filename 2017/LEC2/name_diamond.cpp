#include <iostream>

using namespace std;

void nameDiamond(string name) {
  int i = 0, j = 0;
  while (i < name.length() || j < name.length()) {

    for (int k = 0; k < i; k++) {
      cout << " ";
    }
    for (int k = i; k <= j; k++) {
      cout << name[k];
    }
    cout << endl;

    if (j < name.length()) {
      j++;
    }
    if (j == name.length() && i < name.length()) {
      i++;
    }
  }
}

int main() {

  nameDiamond("MARTY");
  return 0;
}
