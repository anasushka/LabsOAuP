#include "figure.h"

Figure::Figure(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}
