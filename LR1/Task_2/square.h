#ifndef SQUIRE_H
#define SQUIRE_H

#include "polygonfigure.h"

class Square : public PolygonFigure
{
public:
    explicit Square(qreal sideLength, QGraphicsItem* parent = nullptr);
    virtual ~Square() {}

    void setSideLength(qreal sideLength);
    qreal getSideLength() const;

    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF& newCenter) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    qreal m_sideLength;
};

#endif // SQUIRE_H
