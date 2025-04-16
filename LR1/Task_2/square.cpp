#include "square.h"
#include <QPolygonF>
#include <QtMath>

Square::Square(qreal sideLength, QGraphicsItem *parent)
    : PolygonFigure(QPolygonF(), parent), m_sideLength(sideLength)
{
    setSideLength(sideLength);
}

void Square::setSideLength(qreal sideLength)
{
    qreal half = sideLength / 2.0;
    QPolygonF square;
    square << QPointF(-half, -half)
           << QPointF( half, -half)
           << QPointF( half,  half)
           << QPointF(-half,  half);
    setPolygon(square);
}

qreal Square::getSideLength() const
{
    return m_sideLength;
}

double Square::area() const
{
    qreal side = getSideLength();
    return side * side;
}

double Square::perimeter() const
{
    return 4 * getSideLength();
}

QPointF Square::centerOfMass() const
{
    return QPointF(0, 0);
}


void Square::setCenterOfMass(const QPointF &newCenter)
{
     setTransformOriginPoint(newCenter);
}

QRectF Square::boundingRect() const
{
    return getPolygon().boundingRect();
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //painter->setBrush(Qt::cyan); // Пример заливки
    painter->setPen(Qt::black);
    painter->drawPolygon(getPolygon());
}

