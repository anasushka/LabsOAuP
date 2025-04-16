#include "ellipse.h"
#include <QTimer>
#include <QPushButton>


class Eyes : public Ellipse {
public:
    Eyes(QGraphicsObject *parent = nullptr);
    ~Eyes();
    void moveEyes();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

public slots:

    void onTime();

private:
    bool buttonClicked = true;
    int pright = 15;
    int pstop = 0;
    bool stop = false;
    bool right = false;

    int x;
    QTimer *tim;
};
