#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "mygraphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
     //Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSquare_triggered();
    void on_actionCircle_triggered();
    void on_actionRectangle_triggered();
    void on_actionEllipse_triggered();
    void on_actionRhombus_triggered();
    void on_actionTriangle_triggered();
    void on_actionHexagon_triggered();
    void on_actionFiveStar_triggered();
    void on_actionSixStar_triggered();
    void on_actionEightStar_triggered();


    void highlightCenterOfMass();

    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);

    void UpdateScene();


private:
    Ui::MainWindow *ui;
    MyGraphicsView* view;
    QTimer *timer;
    QGraphicsEllipseItem* centerMarker = nullptr;
};

#endif // MAINWINDOW_H
