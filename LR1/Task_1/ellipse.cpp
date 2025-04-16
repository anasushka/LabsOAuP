#include "ellipse.h"

Ellipse::Ellipse() {}
QRectF

Ellipse::boundingRect() const {
    return QRectF(0, 0, 10, 10);
}


void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::blue);
    painter->drawEllipse(-50, 120, 200, 300);

    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-50, -120, 200, 300);
}
