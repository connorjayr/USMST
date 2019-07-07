#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include "city.h"
#include <QPaintEvent>
#include <QWidget>

class Overlay : public QWidget {
  std::vector<City> cities;

public:
  Overlay(QWidget* parent, const std::vector<City>& c)
      : QWidget(parent), cities(c) {}
protected:
  void paintEvent(QPaintEvent* event);
};

#endif
