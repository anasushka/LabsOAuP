#include "ellipse.h"
#include <QTimer>
#include <QPushButton>

class Lips : public Ellipse {
public:
    Lips(QGraphicsObject *parent = nullptr);
    ~Lips();
    void moveMouse();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

public slots:

    void onTime2();

private:
    bool buttonClicked = true;
    int pup = 5;
    int pstop2 = 0;
    bool stop2 = false;
    bool up = false;

    int y;
    QTimer *tim2;
};
