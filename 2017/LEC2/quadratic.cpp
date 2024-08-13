#include <cmath>
#include <iostream>

using namespace std;

void quadratic(double a, double b, double c, double &root1, double &root2) {
  double delta = sqrt((b * b) - (4 * a * c));
  root1 = (-b + delta) / (2 * a);
  root2 = (-b - delta) / (2 * a);
}

int main() {
  double root1, root2;
  quadratic(1.0, -3.0, -4.0, root1, root2);
  cout << root1 << endl;
  cout << root2 << endl;
  return 0;
}
