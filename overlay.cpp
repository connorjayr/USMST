#include "overlay.h"
#include <QFont>
#include <QPainter>

void Overlay::paintEvent(QPaintEvent* event) {
  QPainter gfx(this);
  gfx.setRenderHint(QPainter::Antialiasing);

  gfx.setPen(QPen(Qt::black, 1));
  gfx.setBrush(Qt::black);
  for (size_t i = 0; i < cities.size(); ++i) {
    QPoint location = cities[i].getLocation().toQPoint();
    gfx.drawEllipse(location, 4, 4);
    for (size_t j = i + 1; j < cities.size(); ++j) {
      gfx.drawLine(location, cities[j].getLocation().toQPoint());
    }
  }

  // PRIM'S ALGORTITHM
  std::vector<Vertex> graph;
  for (size_t i = 0; i < cities.size(); ++i) {
    graph.push_back(Vertex(cities[i].getLocation()));
  }
  std::set<Edge> edges;
  for (size_t i = 0; i < graph.size(); ++i) {
    for (size_t j = i + 1; j < graph.size(); ++j) {
      edges.insert(Edge(&graph[i], &graph[j]));
    }
  }
  std::vector<Edge> tree;
  while (findMSTEdge(edges, tree)) {
    const std::pair<Vertex*, Vertex*>& vertices = tree.back().getVertices();
    gfx.drawLine(vertices.first->getLocation().toQPoint(),
                 vertices.second->getLocation().toQPoint());
  }

  gfx.setPen(QPen(Qt::black, 1));
  QBrush boxBrush(QColor(255, 255, 255, 256 * 1 / 2));
  
  QFont font("Roboto", 12);
  gfx.setFont(font);
  QFontMetrics fontMetrics(font);
  
  for (size_t c = 0; c < cities.size(); ++c) {
    City& city = cities[c];
    QPoint labelLocation = city.getLocation().toQPoint() + QPoint(8, 8);

    QString name(city.getName().c_str());
    QRect boundingBox = fontMetrics.boundingRect(name);
    boundingBox.translate(labelLocation);
    boundingBox.adjust(-2, -2, 2, 2);
    gfx.fillRect(boundingBox, boxBrush);

    gfx.drawText(labelLocation, name);
  }
}
