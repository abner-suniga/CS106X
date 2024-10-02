#include <filesystem>
#include <iostream>

std::string tabs(int n) {
  std::string str = "";
  for (int i = 0; i < n; i++) {
    str += '\t';
  }
  return str;
}

void crawl(std::string path, int level = 0) {
  for (const auto &entry : std::filesystem::directory_iterator(path)) {

    std::string entryPath = entry.path();
    std::string entryName =
        std::filesystem::path(entryPath).filename().string();

    std::cout << tabs(level) << entryName << std::endl;

    if (entry.is_directory()) {
      crawl(entryPath, level + 1);
    }
  }
}

int main() {

  crawl(".");

  return 0;
}
