#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygonfigure.h"

class Triangle : public PolygonFigure
{
public:
    explicit Triangle(qreal dx, qreal dy, QGraphicsItem* parent = nullptr);
    virtual ~Triangle() {}

    void setTriangle(qreal dx, qreal dy);

    qreal getDx() const;
    qreal getDy() const;


    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF &newCenter) override;


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget = nullptr) override;

private:
    qreal m_dx;
    qreal m_dy;
};

#endif // TRIANGLE_H
