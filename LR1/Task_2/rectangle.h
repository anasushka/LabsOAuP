#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "polygonfigure.h"

class Rectangle:public PolygonFigure
{
public:
    Rectangle(qreal width, qreal height, QGraphicsItem* parent = nullptr);
    virtual ~Rectangle(){}

    void setRectangle(qreal width, qreal height);
    qreal getWidth() const;
    qreal getHeight() const;


    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF& newCenter) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    qreal m_width, m_height;
};

#endif // RECTANGLE_H
