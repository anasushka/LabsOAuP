#pragma once
#include <QGraphicsObject>
#include <QPainter>

class Ellipse : public QGraphicsObject {
public:
    Ellipse();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
