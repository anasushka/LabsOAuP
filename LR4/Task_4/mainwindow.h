#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "vector.h"
#include "pair.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Vector<int> a{1, 2, 3, 4, 5, 6, 7};
    Vector< pair< Vector<int>, Vector< pair<int, double> > > > matrixData;


protected slots:
    void update();

    void atSlot();

    void capacitySlot();

    void clearSlot();

    void dataSlot();

    void emptySlot();

    void eraseSlot();

    void maxSizeSlot();

    void popBackSlot();

    void pushBackSlot();

    void reserveSlot();

    void resizeSlot();

    void sizeSlot();



};

#endif // MAINWINDOW_H
