#include "fivestar.h"
#include <QtMath>
#include <QPainter>

FiveStar::FiveStar(qreal outerWidth, qreal outerHeight, qreal innerWidth, qreal innerHeight, QGraphicsItem* parent)
    : PolygonFigure(QPolygonF(), parent),
    m_outerWidth(outerWidth), m_outerHeight(outerHeight),
    m_innerWidth(innerWidth), m_innerHeight(innerHeight)
{
    setStar(outerWidth, outerHeight, innerWidth, innerHeight);
}

void FiveStar::setStar(qreal outerWidth, qreal outerHeight,
                            qreal innerWidth, qreal innerHeight)
{
    m_outerWidth = outerWidth;
    m_outerHeight = outerHeight;
    m_innerWidth = innerWidth;
    m_innerHeight = innerHeight;

    QPolygonF poly;
    const int numPoints = 10;
    double angleStep = 2 * M_PI / numPoints;
    double startAngle = -M_PI / 2;

    for (int i = 0; i < numPoints; ++i) {
        double angle = startAngle + i * angleStep;
        if (i % 2 == 0) {
            qreal x = (outerWidth / 2.0) * qCos(angle);
            qreal y = (outerHeight / 2.0) * qSin(angle);
            poly << QPointF(x, y);
        } else {
            qreal x = (innerWidth / 2.0) * qCos(angle);
            qreal y = (innerHeight / 2.0) * qSin(angle);
            poly << QPointF(x, y);
        }
    }
    setPolygon(poly);
}

double FiveStar::area() const
{
    double A = 0;
    QPolygonF poly = getPolygon();
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        QPointF p1 = poly[i];
        QPointF p2 = poly[(i + 1) % n];
        A += (p1.x() * p2.y() - p2.x() * p1.y());
    }
    return qAbs(A) / 2.0;
}

double FiveStar::perimeter() const
{
    double p = 0;
    QPolygonF poly = getPolygon();
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        p += QLineF(poly[i], poly[(i + 1) % n]).length();
    }
    return p;
}

QPointF FiveStar::centerOfMass() const
{
    return QPointF(0, 0);
}

void FiveStar::setCenterOfMass(const QPointF &newCenter)
{
    setTransformOriginPoint(newCenter);
}

QRectF FiveStar::boundingRect() const
{
    return getPolygon().boundingRect();
}

void FiveStar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawPolygon(getPolygon());
}
