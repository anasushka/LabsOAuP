#include "mygraphicsview.h"
#include "square.h"
#include <QGraphicsScene>

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent),
    m_drawing(false),
    m_tempItem(nullptr)
{

    setScene(new QGraphicsScene(this));
   // setRenderHint(QPainter::Antialiasing);
    setSceneRect(-400, -300, 800, 600);
    setAlignment(Qt::AlignCenter);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MyGraphicsView::~MyGraphicsView()
{
}

void MyGraphicsView::setCurrentShape(ShapeType shape)
{
    m_currentShape = shape;
}

ShapeType MyGraphicsView::currentShape() const
{
    return m_currentShape;
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPointF scenePos = mapToScene(event->pos());

        QGraphicsItem* item = scene()->itemAt(scenePos, QTransform());
        if(item) {

            QGraphicsView::mousePressEvent(event);
            return;
        }
        if(m_currentShape != ShapeType::None)
        {
            m_drawing = true;
            m_startPoint = event->pos();
            switch(m_currentShape) {
            case ShapeType::Square:
                m_tempItem = new Square(0);
                break;
            case ShapeType::Circle:
                m_tempItem = new Circle(0);
                break;
            case ShapeType::Rectangle:
                m_tempItem= new Rectangle(0,0);
                break;
            case ShapeType::Ellipse:
                m_tempItem= new Ellipse(0,0);
                break;
            case ShapeType::Rhombus:
                m_tempItem= new Rhombus(0,0);
                break;
            case ShapeType::Triangle:
                m_tempItem= new Triangle(0,0);
                break;
            case ShapeType::Hexagon:
                m_tempItem= new Hexagon(0,0);
                break;
            case ShapeType::FiveStar:
                m_tempItem= new FiveStar(0,0,0,0);
                break;
            case ShapeType::SixStar:
                m_tempItem= new SixStar(0,0,0,0);
                break;
            case ShapeType::EightStar:
                m_tempItem= new EightStar(0,0,0,0);
                break;
            default:
                break;
            }
            if(m_tempItem) {
                scene()->addItem(m_tempItem);
                m_tempItem->setPos(scenePos);
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_drawing && m_tempItem)
    {
        QPointF start = mapToScene(m_startPoint);
        QPointF current = mapToScene(event->pos());
        qreal dx = qAbs(current.x() - start.x());
        qreal dy = qAbs(current.y() - start.y());

        if(m_currentShape == ShapeType::Square)
        {
            Square* square = dynamic_cast<Square*>(m_tempItem);
            if(square) {
                square->setSideLength(dx);
            }
        }
        else if(m_currentShape == ShapeType::Circle)
        {
            Circle* circle = dynamic_cast<Circle*>(m_tempItem);
            if(circle) {
                circle->setRadius(dx/2.0); // радиус = половина стороны
            }
        }
        else if(m_currentShape == ShapeType::Rectangle)
        {
            Rectangle* rectangle = dynamic_cast<Rectangle*>(m_tempItem);
            if(rectangle) {
                rectangle->setRectangle(dx, dy);
            }
        }
        else if(m_currentShape == ShapeType::Ellipse)
        {
            Ellipse* ellipse = dynamic_cast<Ellipse*>(m_tempItem);
            if(ellipse) {
                ellipse->setEllipse(dx, dy);
            }
        }
        else if(m_currentShape == ShapeType::Rhombus)
        {
            Rhombus* rhombus = dynamic_cast<Rhombus*>(m_tempItem);
            if(rhombus) {
                rhombus->setDiagonals(dx, dy);
            }
        }
        else if(m_currentShape == ShapeType::Triangle)
        {
            Triangle* triangle = dynamic_cast<Triangle*>(m_tempItem);
            if(triangle) {
                triangle->setTriangle(dx,dy);
            }
        }
        else if(m_currentShape == ShapeType::Hexagon)
        {
            Hexagon* hexagon = dynamic_cast<Hexagon*>(m_tempItem);
            if(hexagon) {
                hexagon->setDimensions(dx,dy);
            }
        }
        else if(m_currentShape == ShapeType::FiveStar)
        {
            FiveStar* fivestar = dynamic_cast<FiveStar*>(m_tempItem);
            if(fivestar) {
                fivestar->setStar(dx,dy,dx/2.0,dy/2.0);
            }
        }
        else if(m_currentShape == ShapeType::SixStar)
        {
            SixStar* sixstar = dynamic_cast<SixStar*>(m_tempItem);
            if(sixstar) {
                sixstar->setStar(dx,dy,dx/2.0,dy/2.0);
            }
        }
        else if(m_currentShape == ShapeType::EightStar)
        {
            EightStar* eightstar = dynamic_cast<EightStar*>(m_tempItem);
            if(eightstar) {
                eightstar->setStar(dx,dy,dx/2.0,dy/2.0);
            }
        }


    }
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_drawing)
    {
        m_drawing = false;
        m_tempItem = nullptr; // Завершаем рисование, объект остаётся на сцене
    }
    QGraphicsView::mouseReleaseEvent(event);
}
