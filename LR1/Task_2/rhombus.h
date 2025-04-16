#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "polygonfigure.h"

class Rhombus:public PolygonFigure
{
public:
    Rhombus(qreal diagonal1, qreal diagonal2, QGraphicsItem* parent =nullptr);
    virtual ~Rhombus(){}

    void setDiagonals(qreal diagonal1,qreal diagonal2);
    qreal getDiagonal1() const;
    qreal getDiagonal2() const;

    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF& newCenter) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


private:
    qreal m_diagonal1, m_diagonal2;

};

#endif // RHOMBUS_H
