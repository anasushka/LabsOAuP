#include "rhombus.h"

#include <QPolygonF>
#include <QtMath>


Rhombus::Rhombus(qreal diagonal1, qreal diagonal2, QGraphicsItem* parent)
    : PolygonFigure(QPolygonF(), parent), m_diagonal1(diagonal1), m_diagonal2(diagonal2)
{
    setDiagonals(diagonal1, diagonal2);
}

void Rhombus::setDiagonals(qreal diagonal1, qreal diagonal2)
{
    m_diagonal1 = diagonal1;
    m_diagonal2 = diagonal2;
    QPolygonF poly;
      poly << QPointF(0, diagonal2/2.0)
         << QPointF(m_diagonal1/2.0, 0)
         << QPointF(0, -m_diagonal2/2.0)
         << QPointF(-m_diagonal1/2.0, 0);
    setPolygon(poly);
}

qreal Rhombus::getDiagonal1() const { return m_diagonal1; }
qreal Rhombus::getDiagonal2() const { return m_diagonal2; }

double Rhombus::area() const { return (m_diagonal1 * m_diagonal2) / 2.0; }
double Rhombus::perimeter() const {
      double side = qSqrt((m_diagonal1/2.0) * (m_diagonal1/2.0) + (m_diagonal2/2.0) * (m_diagonal2/2.0));
    return 4 * side;
}

QPointF Rhombus::centerOfMass() const {
    return QPointF(0, 0);
}

void Rhombus::setCenterOfMass(const QPointF &newCenter) {
    setTransformOriginPoint(newCenter);
}

QRectF Rhombus::boundingRect() const { return getPolygon().boundingRect(); }
void Rhombus::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawPolygon(getPolygon());
}
