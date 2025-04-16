#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setSceneRect(-ui->graphicsView->width() / 2, -ui->graphicsView->height() / 2, ui->graphicsView->width(), ui->graphicsView->height());

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);

    ellipse = new Ellipse();
    glaza = new Eyes;
    gubi = new Lips;

    scene->addItem(ellipse);
    scene->addItem(glaza);
    scene->addItem(gubi);

    timer = new QTimer();

    connect(timer, &QTimer::timeout, this, &MainWindow::UpdateScene);

    timer->start(10);
}


void MainWindow::UpdateScene()
{
    scene->update();
}

MainWindow::~MainWindow() {
    delete ellipse;
    delete glaza;
    delete gubi;
}

void MainWindow::on_pushButton_clicked() { glaza->onTime(); }
void MainWindow::on_pushButton_2_clicked() { gubi->onTime2(); }
