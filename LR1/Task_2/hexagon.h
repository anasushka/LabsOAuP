#ifndef HEXAGON_H
#define HEXAGON_H

#include "polygonfigure.h"

class Hexagon : public PolygonFigure
{
public:
    explicit Hexagon(qreal width, qreal height, QGraphicsItem* parent = nullptr);
    virtual ~Hexagon() {}

    void setDimensions(qreal width, qreal height);
    qreal getWidth() const;
    qreal getHeight() const;

    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF& newCenter) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    qreal m_width;
    qreal m_height;
};

#endif // HEXAGON_H
