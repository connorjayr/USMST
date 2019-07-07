#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <QPoint>
#include <set>
#include <utility>
#include <vector>

class Coordinate {
  double latitude;
  double longitude;

public:
  Coordinate(double lat, double lon) : latitude(lat), longitude(lon) {}

  double getLatitude() const { return latitude; }
  double getLongitude() const { return longitude; }

  double distance(const Coordinate& to) const;

  QPoint toQPoint() const;
};

double toRadians(double angle);

class Vertex {
  Coordinate location;
  std::vector<Vertex> connections;

public:
  Vertex(const Coordinate& loc) : location(loc) {}

  const Coordinate& getLocation() const { return location; }

  const std::vector<Vertex>& getConnections() const { return connections; }
  void connect(const Vertex& v) { connections.push_back(v); }
};

class Edge {
  std::pair<Vertex*, Vertex*> vertices;
  double distance;

public:
  Edge(Vertex* a, Vertex* b);

  const std::pair<Vertex*, Vertex*>& getVertices() const { return vertices; }
  double getDistance() const { return distance; }

  bool operator<(const Edge& e) const { return distance < e.distance; }

  bool expandsTree() const;
  bool touchesTree() const;
};

bool findMSTEdge(std::set<Edge>& edges, std::vector<Edge>& tree); 

#endif
