#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void tokenize(std::string str, const std::string& delimiter,
              std::vector<std::string>& tokens) {
  int i = str.find(delimiter);
  while (i != std::string::npos) {
    tokens.push_back(str.substr(0, i));

    str = str.substr(i + delimiter.length());
    i = str.find(delimiter);
  }
  tokens.push_back(str);
}

void uncite(std::string& str) {
  int i = str.find("[");
  if (i != std::string::npos) str = str.substr(0, i);
}

void trim(std::string& str) {
  size_t begin = str.find_first_not_of(' ');
  size_t end = str.find_last_not_of(' ');
  str = str.substr(begin, end - begin + 1);
}

int main() {
  std::ifstream in("data.txt");
  std::ofstream out("out.txt");

  std::string line;
  while (getline(in, line)) {
    std::vector<std::string> columns;
    tokenize(line, "\t", columns);

    if (columns[2].find("Alaska") != std::string::npos ||
        columns[2].find("Hawaii") != std::string::npos) continue;

    std::string name = columns[1];
    uncite(name);
    trim(name);
    for (size_t i = 0; i < name.length(); ++i) {
      if (name[i] == ' ') name[i] = '_';
    }

    std::vector<std::string> coordinates;
    tokenize(columns.back(), " ", coordinates);

    double latitude = std::stod(coordinates.front());
    if (coordinates.front().back() == 'S') latitude *= -1;

    double longitude = std::stod(coordinates.back());
    if (coordinates.back().back() == 'W') longitude *= -1;

    out << name << " " << latitude << " " << longitude << std::endl;
  }
}
