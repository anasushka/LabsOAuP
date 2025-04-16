#ifndef EIGHTSTAR_H
#define EIGHTSTAR_H
#include "polygonfigure.h"

class EightStar:public PolygonFigure
{
public:
    explicit EightStar(qreal outerWidth, qreal outerHeight, qreal innerWidth, qreal innerHeight, QGraphicsItem* parent = nullptr);
    virtual ~EightStar() {}

    // Метод для установки параметров звезды (позволяет растягивать по горизонтали и вертикали независимо)
    void setStar(qreal outerWidth, qreal outerHeight, qreal innerWidth, qreal innerHeight);


    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    void setCenterOfMass(const QPointF& newCenter) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget = nullptr) override;

private:
    qreal m_outerWidth;
    qreal m_outerHeight;
    qreal m_innerWidth;
    qreal m_innerHeight;
};

#endif // EIGHTSTAR_H
