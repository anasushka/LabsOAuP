#include "triangle.h"
#include <QtMath>
#include <QPainter>

Triangle::Triangle(qreal dx, qreal dy, QGraphicsItem* parent)
    : PolygonFigure(QPolygonF(), parent), m_dx(dx), m_dy(dy)
{
    setTriangle(dx, dy);
}

void Triangle::setTriangle(qreal dx, qreal dy)
{
    m_dx = dx;
    m_dy = dy;

    // Нижняя вершина: (0, -dy)
    // Левая: (-dx, 0)
    // Правая: (dx, 0)
    // Центроид: (0, -dy/3)
    QPointF A(0, -dy + dy/3.0);
    QPointF B(-dx, 0 + dy/3.0);
    QPointF C(dx, 0 + dy/3.0);

    QPolygonF poly;
    poly << A << B << C;
    setPolygon(poly);
}

qreal Triangle::getDx() const { return m_dx; }
qreal Triangle::getDy() const { return m_dy; }

double Triangle::area() const
{

    return (2 * m_dx * m_dy) / 2.0;
}

double Triangle::perimeter() const
{  
    qreal side = qSqrt(m_dx * m_dx + m_dy * m_dy);
    return 2 * side + 2 * m_dx;
}

QPointF Triangle::centerOfMass() const
{
    return QPointF(0, 0);
}

void Triangle::setCenterOfMass(const QPointF &newCenter)
{
    setTransformOriginPoint(newCenter);
}

QRectF Triangle::boundingRect() const
{
    return getPolygon().boundingRect();
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawPolygon(getPolygon());
}
