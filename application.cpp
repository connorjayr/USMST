#include "city.h"
#include "graph.h"
#include "overlay.h"
#include <Qt>
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <fstream>
#include <iostream>

void loadCities(std::vector<City>& cities) {
  std::ifstream in("data/cities.txt");
  if (!in.good()) {
    std::cerr << "ERROR: could not open \"data/cities.txt\"" << std::endl;
    return;
  }

  std::string name;
  double lat, lon;
  while (in >> name >> lat >> lon) {
    cities.push_back(City(name, Coordinate(lat, lon)));
  }
  std::cout << "Loaded " << cities.size() << " cities" << std::endl;
}

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);

  QMainWindow window;
  window.setWindowTitle("AI and Society");

  QLabel map(&window);
  map.setPixmap(QPixmap("assets/united_states.png"));
  map.adjustSize();

  std::vector<City> cities;
  loadCities(cities);

  Overlay overlay(&window, cities);
  overlay.resize(map.size());
  
  window.setFixedSize(map.size());
  window.show();

  return application.exec();
}
