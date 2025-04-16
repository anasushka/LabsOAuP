#ifndef POLYGONFIGURE_H
#define POLYGONFIGURE_H
#include "figure.h"
#include <QPolygonF>

class PolygonFigure: public Figure
{
public:
    explicit PolygonFigure(const QPolygonF& polygon, QGraphicsItem* parent = nullptr);
    virtual ~PolygonFigure() {}

    void setPolygon(const QPolygonF& polygon);
    QPolygonF getPolygon() const;


protected:
    QPolygonF m_polygon;
};

#endif // POLYGONFIGURE_H
