#include "hexagon.h"
#include <QPolygonF>
#include <QPainter>
#include <QtMath>

Hexagon::Hexagon(qreal width, qreal height, QGraphicsItem* parent)
    : PolygonFigure(QPolygonF(), parent),
    m_width(width),
    m_height(height)
{
    setDimensions(width, height);
}

void Hexagon::setDimensions(qreal width, qreal height)
{
    m_width = width;
    m_height = height;
    QPolygonF poly;

    poly << QPointF(-width/4.0, -height/2.0)
         << QPointF( width/4.0, -height/2.0)
         << QPointF( width/2.0, 0)
         << QPointF( width/4.0, height/2.0)
         << QPointF(-width/4.0, height/2.0)
         << QPointF(-width/2.0, 0);

    setPolygon(poly);
}

qreal Hexagon::getWidth() const { return m_width; }
qreal Hexagon::getHeight() const { return m_height; }

double Hexagon::area() const
{
   double A = 0;
    QPolygonF poly = getPolygon();
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        QPointF p1 = poly[i];
        QPointF p2 = poly[(i+1) % n];
        A += (p1.x() * p2.y() - p2.x() * p1.y());
    }
    return qAbs(A) / 2.0;
}

double Hexagon::perimeter() const
{
    double p = 0;
    QPolygonF poly = getPolygon();
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        p += QLineF(poly[i], poly[(i+1)%n]).length();
    }
    return p;
}

QPointF Hexagon::centerOfMass() const
{
    return QPointF(0, 0);
}

void Hexagon::setCenterOfMass(const QPointF &newCenter)
{
    setTransformOriginPoint(newCenter);
}

QRectF Hexagon::boundingRect() const
{
    return getPolygon().boundingRect();
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawPolygon(getPolygon());
}
