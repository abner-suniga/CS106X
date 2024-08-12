#include <iostream>

using namespace std;

int main() {
  int stanford_score, cal_score;

  cout << "Stanford: How many points did they score? ";
  cin >> stanford_score;

  cout << "Cal: How many points did they score? ";
  cin >> cal_score;

  if (stanford_score == cal_score) {
    cout << "Draw" << endl;
  } else if (stanford_score > cal_score) {
    cout << "Stanford won!" << endl;
  } else {
    cout << "Cal won!" << endl;
  }

  return 0;
}
