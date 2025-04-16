#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QIcon>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QFormLayout>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* hLayout = new QHBoxLayout(centralWidget);

    view = new MyGraphicsView(this);
    hLayout->addWidget(view, 1);


    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);


    QWidget* sliderPanel = new QWidget(this);
    QVBoxLayout* sliderLayout = new QVBoxLayout(sliderPanel);

    QSlider* sliderRotation = new QSlider(Qt::Vertical, this);
    sliderRotation->setMinimum(0);
    sliderRotation->setMaximum(100);
    connect(sliderRotation, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_valueChanged);

    QSlider* sliderScale = new QSlider(Qt::Vertical, this);
    sliderScale->setMinimum(0);
    sliderScale->setMaximum(100);
    sliderScale->setValue(50);
    connect(sliderScale, &QSlider::valueChanged, this, &MainWindow::on_horizontalSlider_2_valueChanged);

    sliderLayout->addWidget(sliderRotation);
    sliderLayout->addWidget(sliderScale);
    sliderPanel->setLayout(sliderLayout);

    QWidget* centerPanel = new QWidget(this);
    QFormLayout* centerLayout = new QFormLayout(centerPanel);
    QLineEdit* lineEditCenterX = new QLineEdit(centerPanel);
    QLineEdit* lineEditCenterY = new QLineEdit(centerPanel);
    centerLayout->addRow("X:", lineEditCenterX);
    centerLayout->addRow("Y:", lineEditCenterY);

    QPushButton* setCenterButton = new QPushButton("Новый центр масс.", centerPanel);
    centerLayout->addRow(setCenterButton);
    centerPanel->setLayout(centerLayout);

    connect(setCenterButton, &QPushButton::clicked, this, [=]() {

        qreal newX = lineEditCenterX->text().toDouble();
        qreal newY = lineEditCenterY->text().toDouble();
        QPointF newCenter(newX, newY);

        if (!view->scene()->selectedItems().isEmpty()) {
            QGraphicsItem* selectedItem = view->scene()->selectedItems().first();
            QPointF localCenter = selectedItem->mapFromScene(newCenter);
            selectedItem->setTransformOriginPoint(localCenter);
        }
    });

    rightLayout->addWidget(sliderPanel);
    rightLayout->addWidget(centerPanel);
    rightPanel->setLayout(rightLayout);

    hLayout->addWidget(rightPanel);

    setCentralWidget(centralWidget);

    setWindowTitle("типо Paint");
    resize(800, 600);

    QToolBar* toolbar = addToolBar("");

    //QAction* actionSelect = toolbar->addAction(QIcon(":/icons/select.png"), "Выбор");
    QAction* actionSquare = toolbar->addAction(QIcon(":/icon/icons/square.png"), "Квадрат");
    QAction* actionCircle = toolbar->addAction(QIcon(":/icon/icons/circle.png"), "Круг");
    QAction* actionRectangle = toolbar->addAction(QIcon(":/icon/icons/rectangle.png"), "Прямоугольник");
    QAction* actionEllipse = toolbar->addAction(QIcon(":/icon/icons/ellipse.png"), "Эллипс");
    QAction* actionRhombus = toolbar->addAction(QIcon(":/icon/icons/rhombus.png"), "Ромб");
    QAction* actionTriangle = toolbar->addAction(QIcon(":/icon/icons/triangle.png"), "Треугольник");
    QAction* actionHexagon = toolbar->addAction(QIcon(":/icon/icons/hexagon.png"), "Шестиугольник");
    QAction* actionFiveStar = toolbar->addAction(QIcon(":/icon/icons/fivestar.png"), "Звезда 5");
    QAction* actionSixStar = toolbar->addAction(QIcon(":/icon/icons/sixstar.png"), "Звезда 6");
    QAction* actionEightStar = toolbar->addAction(QIcon(":/icon/icons/eightstar.png"), "Звезда 8");

   // connect(actionSelect, &QAction::triggered, this, &MainWindow::on_actionSelect_triggered);
    connect(actionSquare, &QAction::triggered, this, &MainWindow::on_actionSquare_triggered);
    connect(actionCircle, &QAction::triggered, this, &MainWindow::on_actionCircle_triggered);
    connect(actionRectangle, &QAction::triggered, this, &MainWindow::on_actionRectangle_triggered);
    connect(actionEllipse, &QAction::triggered, this, &MainWindow::on_actionEllipse_triggered);
    connect(actionRhombus, &QAction::triggered, this, &MainWindow::on_actionRhombus_triggered);
    connect(actionTriangle, &QAction::triggered, this, &MainWindow::on_actionTriangle_triggered);
    connect(actionHexagon, &QAction::triggered, this, &MainWindow::on_actionHexagon_triggered);
    connect(actionFiveStar, &QAction::triggered, this, &MainWindow::on_actionFiveStar_triggered);
    connect(actionSixStar, &QAction::triggered, this, &MainWindow::on_actionSixStar_triggered);
    connect(actionEightStar, &QAction::triggered, this, &MainWindow::on_actionEightStar_triggered);

    connect(view->scene(), &QGraphicsScene::selectionChanged, this, &MainWindow::highlightCenterOfMass);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::UpdateScene);
    timer->start(10);
}


void MainWindow::highlightCenterOfMass()
{
    if (centerMarker) {
        view->scene()->removeItem(centerMarker);
        delete centerMarker;
        centerMarker = nullptr;
    }

    if (!view->scene()->selectedItems().isEmpty()) {
        QGraphicsItem* item = view->scene()->selectedItems().first();

        QPointF centerLocal = item->transformOriginPoint();
        QPointF centerScene = item->mapToScene(centerLocal);

        centerMarker = view->scene()->addEllipse(centerScene.x() - 3, centerScene.y() - 3, 6, 6, QPen(Qt::red), QBrush(Qt::red));
        centerMarker->setZValue(1000);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateScene()
{
    view->scene()->update();


    if (!view->scene()->selectedItems().isEmpty()) {
        QGraphicsItem* item = view->scene()->selectedItems().first();
        QPointF localCenter = item->transformOriginPoint();
        QPointF sceneCenter = item->mapToScene(localCenter);

        if (centerMarker) {
            centerMarker->setRect(sceneCenter.x() - 3, sceneCenter.y() - 3, 6, 6);
        } else {
            centerMarker = view->scene()->addEllipse(sceneCenter.x() - 3,sceneCenter.y() - 3,6, 6, QPen(Qt::red),QBrush(Qt::red));
            centerMarker->setZValue(1000);
        }
    } else {

        if (centerMarker) {
            view->scene()->removeItem(centerMarker);
            delete centerMarker;
            centerMarker = nullptr;
        }
    }
}



void MainWindow::on_actionSquare_triggered()
{
    view->setCurrentShape(ShapeType::Square);
}

void MainWindow::on_actionCircle_triggered()
{
    view->setCurrentShape(ShapeType::Circle);
}

void MainWindow::on_actionRectangle_triggered()
{
    view->setCurrentShape(ShapeType::Rectangle);
}

void MainWindow::on_actionEllipse_triggered()
{
    view->setCurrentShape(ShapeType::Ellipse);
}


void MainWindow::on_actionRhombus_triggered()
{
    view->setCurrentShape(ShapeType::Rhombus);
}

void MainWindow::on_actionTriangle_triggered()
{
    view->setCurrentShape(ShapeType::Triangle);
}

void MainWindow::on_actionHexagon_triggered()
{
    view->setCurrentShape(ShapeType::Hexagon);
}

void MainWindow::on_actionFiveStar_triggered()
{
    view->setCurrentShape(ShapeType::FiveStar);
}

void MainWindow::on_actionSixStar_triggered()
{
    view->setCurrentShape(ShapeType::SixStar);
}

void MainWindow::on_actionEightStar_triggered()
{
    view->setCurrentShape(ShapeType::EightStar);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if (!view->scene()->selectedItems().isEmpty())
        view->scene()->selectedItems().first()->setRotation(value * 3.6);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    if (!view->scene()->selectedItems().isEmpty())
        view->scene()->selectedItems().first()->setScale(value * 0.02);
}
