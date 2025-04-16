#ifndef FIGURE_H
#define FIGURE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>

class Figure: public QGraphicsItem
{
public:
    Figure(QGraphicsItem* parent = nullptr);
    virtual ~Figure() {}

    virtual double area() const=0; //площадь
    virtual double perimeter() const=0;//периметр
    virtual QPointF centerOfMass() const = 0;

    virtual void setCenterOfMass(const QPointF& newCenter) = 0;

};

#endif // FIGURE_H
