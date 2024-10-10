#include <iostream>

void _permute(std::string choices, std::string chosen) {
  if (choices.length() == 0) {
    std::cout << chosen << std::endl;
  }

  for (int i = 0; i < choices.length(); i++) {
    std::string letter = choices.substr(i, 1);
    std::string rest =
        choices.substr(0, i) + choices.substr(i + 1, choices.length());
    _permute(rest, chosen + letter);
  }
}

void permute(std::string str) { _permute(str, ""); }

int main() {

  // std::string mystr = "ABCDE";

  // std::cout << mystr.substr(1, 1) << std::endl; // B
  // std::cout << mystr.substr(0, 1) + mystr.substr(2, mystr.length())
  //           << std::endl; // ACDE

  permute("ABC");
}
