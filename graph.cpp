#include "graph.h"
#include <cmath>

#define R 6371.0

#define LATITUDE_SCALE -37.76435045
#define LONGITUDE_SCALE 31.56682027

double Coordinate::distance(const Coordinate& to) const {
  double lat1 = toRadians(latitude);
  double lon1 = toRadians(longitude);
  double lat2 = toRadians(to.latitude);
  double lon2 = toRadians(to.longitude);

  double u = sin((lat2 - lat1) / 2);
  double v = sin((lon2 - lon1) / 2);

  return 2 * R * asin(sqrt(u * u + cos(lat1) * cos(lat2) * v * v));
}

QPoint Coordinate::toQPoint() const {
  return QPoint(LONGITUDE_SCALE * longitude + 3960.368662,
                LATITUDE_SCALE * latitude + 1881.649546);
}

double toRadians(double angle) {
  return angle * M_PI / 180;
}

Edge::Edge(Vertex* a, Vertex* b)
    : vertices(std::pair<Vertex*, Vertex*>(a, b)) {
  distance = a->getLocation().distance(b->getLocation());
}

bool Edge::expandsTree() const {
  return vertices.first->getConnections().empty()
         ^ vertices.second->getConnections().empty();
}

bool Edge::touchesTree() const {
  return !vertices.first->getConnections().empty()
         || !vertices.second->getConnections().empty();
}

bool findMSTEdge(std::set<Edge>& edges, std::vector<Edge>& tree) {
  std::set<Edge>::iterator itr = edges.begin();
  while (!edges.empty() && !tree.empty() && !itr->expandsTree()) {
    if (itr->touchesTree()) itr = edges.erase(itr);
    else ++itr;
  }
  if (edges.empty()) return false;
  
  tree.push_back(*itr);

  const std::pair<Vertex*, Vertex*>& vertices = itr->getVertices();
  vertices.first->connect(*vertices.second);
  vertices.second->connect(*vertices.first);

  return true;
}
