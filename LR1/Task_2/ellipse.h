#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "figure.h"

class Ellipse : public Figure
{
public:
    explicit Ellipse(qreal radius_a, qreal redius_b, QGraphicsItem* parent = nullptr);
    virtual ~Ellipse() {}

    void setEllipse(qreal radius_a, qreal radius_b);
    qreal getRadius_A() const;
    qreal getRadius_B() const;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF &newCenter) override;

protected:
    qreal m_radius_a, m_radius_b;

};

#endif // ELLIPSE_H
