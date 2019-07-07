#ifndef __CITY_H__
#define __CITY_H__

#include "graph.h"
#include <string>

class City {
  std::string name;
  Coordinate location;

public:
  City(const std::string& n, const Coordinate& loc);

  const std::string& getName() const { return name; }
  const Coordinate& getLocation() const { return location; }
};

#endif
