#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// 123 Alex 3 2 4 1
// 46 Jessica 8.5 1.5 5 5 10 6
// 7289 Erik 3 6 4 4.68 4

// Alex     (ID#  123) worked 10.0 hours (2.50/day)
// Jessica  (ID#   46) worked 36.0 hours (6.00/day)
// Erik     (ID# 7289) worked 21.7 hours (4.34/day)

void hoursWorked(string filename) {
  ifstream input;
  input.open(filename);
  string line;

  while (getline(input, line)) {
    string id, name;
    double sum_hours = 0;
    int num_hours = 0;

    istringstream lineinput(line);

    lineinput >> id >> name;
    string hour;
    while (lineinput >> hour) {
      sum_hours += stod(hour);
      num_hours++;
    }

    cout << setw(9) << left << name;
    cout << "(ID# " << setw(4) << right << id << ") ";
    cout << "worked " << fixed << setprecision(1) << sum_hours << " hours ";
    cout << "(" << fixed << setprecision(2) << sum_hours / num_hours << "/day)";
    cout << endl;
  }

  input.close();
}

int main() {
  hoursWorked("hours.txt");
  return 0;
}
