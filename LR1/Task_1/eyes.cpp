#include "eyes.h"

Eyes::Eyes(QGraphicsObject *parent) : Ellipse() {
    tim = new QTimer();

    connect(tim, &QTimer::timeout, this, &Eyes::moveEyes);
    x = 0;
    stop = true;
    tim->start(1000 / 20);
}

Eyes::~Eyes() {
    tim->stop();
    delete tim;
}

void Eyes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    painter->setBrush(Qt::white);
    painter->drawEllipse(-20, -50, 60, 40);
    painter->drawEllipse(60, -50, 60, 40);
    painter->setBrush(Qt::black);
    painter->drawEllipse(x + -5, -45, 30, 30);
    painter->drawEllipse(x + 75, -45, 30, 30);
}


void Eyes::moveEyes() {
    if (x < pright && stop == false) {

        x += 1;
        update();
        if (x == pright) {
            right = true;
        }
    } else if (x >= pstop && right == true) {

        x -= 1;
        update();
        stop = true;
    } else {

        tim->stop();
    }
}

void Eyes::onTime() {
    stop = false;
    right = false;
    if (!tim->isActive()) {
     tim->start(1000 / 20);
     }
}
