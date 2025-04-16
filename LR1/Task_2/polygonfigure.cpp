#include "polygonfigure.h"

PolygonFigure::PolygonFigure(const QPolygonF &polygon, QGraphicsItem *parent)
    : Figure(parent), m_polygon(polygon)
{
}

void PolygonFigure::setPolygon(const QPolygonF &polygon)
{
    prepareGeometryChange();
    m_polygon = polygon;
}

QPolygonF PolygonFigure::getPolygon() const
{
    return m_polygon;
}
