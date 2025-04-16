#include "circle.h"
#include <QtMath>

Circle::Circle(qreal radius, QGraphicsItem *parent)
    : Figure(parent), m_radius(radius)
{
}

void Circle::setRadius(qreal radius)
{
    prepareGeometryChange();
    m_radius = radius;
    update();
}

qreal Circle::getRadius() const
{
    return m_radius;
}

QRectF Circle::boundingRect() const
{
    return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
}

double Circle::area() const
{
    return M_PI * m_radius * m_radius;
}

double Circle::perimeter() const
{
    return 2 * M_PI * m_radius;
}

QPointF Circle::centerOfMass() const
{
    // Центр круга всегда в (0,0) в локальных координатах
    return QPointF(0, 0);
}

void Circle::setCenterOfMass(const QPointF &newCenter)
{
   setTransformOriginPoint(newCenter);
}
