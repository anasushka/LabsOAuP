#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

// Класс круга
class Circle : public Figure
{
public:
    explicit Circle(qreal radius, QGraphicsItem* parent = nullptr);
    virtual ~Circle() {}

    void setRadius(qreal radius);
    qreal getRadius() const;

    // Реализация методов QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Реализация интерфейса Figure
    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF &newCenter) override;

protected:
    qreal m_radius;
};

#endif // CIRCLE_H
