#include "rectangle.h"

Rectangle::Rectangle(qreal width, qreal height, QGraphicsItem* parent)
    : PolygonFigure(QPolygonF(), parent), m_width(width), m_height(height)
{
    setRectangle(width, height);
}

void Rectangle::setRectangle(qreal width,  qreal height)
{
    m_width=width;
    m_height=height;
    qreal halfW=width/2.0;
    qreal halfH=height/2.0;

    QPolygonF poly;
    poly << QPointF(-halfW, -halfH)
         << QPointF(halfW, -halfH)
         << QPointF(halfW, halfH)
         << QPointF(-halfW, halfH);
    setPolygon(poly);

}

qreal Rectangle::getWidth() const
{
    return m_width;

}


qreal Rectangle::getHeight() const
{
    return m_height;

}

double Rectangle::area() const
{
    return m_height*m_width;
}


double Rectangle::perimeter() const
{
    return (m_height+m_width)*2.0;
}


QPointF Rectangle::centerOfMass() const
{
    return QPointF(0, 0);
}

void Rectangle::setCenterOfMass(const QPointF &newCenter)
{
    setTransformOriginPoint(newCenter);
}

QRectF Rectangle::boundingRect() const
{
    return getPolygon().boundingRect();
}

void Rectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->drawPolygon(getPolygon());
}




