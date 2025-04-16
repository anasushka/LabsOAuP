#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "square.h"
#include "circle.h"
#include "rectangle.h"
#include "ellipse.h"
#include "rhombus.h"
#include "triangle.h"
#include "hexagon.h"
#include "fivestar.h"
#include "sixstar.h"
#include "eightstar.h"


enum class ShapeType {
        None,
        Square,
        Circle,
        Rectangle,
        Ellipse,
        Rhombus,
        Triangle,
        Hexagon,
        FiveStar,
        SixStar,
        EightStar
};

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget* parent = nullptr);
    ~MyGraphicsView();


    void setCurrentShape(ShapeType shape);
    ShapeType currentShape() const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool m_drawing;
    QPoint m_startPoint;
    QGraphicsItem* m_tempItem;
    ShapeType m_currentShape;
};

#endif // MYGRAPHICSVIEW_H


