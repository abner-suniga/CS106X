#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

void reverseLines(std::ifstream &input) {
  std::string line;

  if (std::getline(input, line)) {
    reverseLines(input);
    std::cout << line << std::endl;
  }
}

int main() {

  std::ifstream input;
  input.open("poem.txt");

  reverseLines(input);

  return 0;
}
