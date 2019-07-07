#include "city.h"

City::City(const std::string& n, const Coordinate& loc)
    : name(n), location(loc) {
  for (size_t i = 0; i < name.length(); ++i) {
    if (name[i] == '_') name[i] = ' ';
  }
}
