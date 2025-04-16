#include "eyes.h"
#include "lips.h"
#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UpdateScene();


protected:
    Ui::MainWindow *ui;
    Ellipse *ellipse;
    Eyes *glaza;
    Lips *gubi;
    QTimer *timer;

    QGraphicsScene *scene;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
