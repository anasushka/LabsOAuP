#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse(qreal radius_a, qreal radius_b, QGraphicsItem *parent)
    : Figure(parent), m_radius_a(radius_a), m_radius_b(radius_b)
{
}

void Ellipse::setEllipse(qreal radius_a, qreal radius_b)
{
    prepareGeometryChange();
    m_radius_a = radius_a;
    m_radius_b = radius_b;
    update();
}

qreal Ellipse::getRadius_A() const
{
    return m_radius_a;
}

qreal Ellipse::getRadius_B() const
{
    return m_radius_b;
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(-m_radius_a, -m_radius_b, 2 * m_radius_a, 2 * m_radius_b);
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
}

double Ellipse::area() const
{
    return M_PI * m_radius_a * m_radius_b;
}

double Ellipse::perimeter() const
{
    return 2 * M_PI * sqrt((m_radius_a*m_radius_a+m_radius_b*m_radius_b)/2);
}

QPointF Ellipse::centerOfMass() const
{
    return QPointF(0, 0);
}

void Ellipse::setCenterOfMass(const QPointF &newCenter)
{
    setTransformOriginPoint(newCenter);
}
