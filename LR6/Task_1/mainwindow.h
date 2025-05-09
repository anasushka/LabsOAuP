#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "inputdialog.h"
#include "./ui_inputdialog.h"
#include <QMainWindow>

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

private slots:
    void on_keyboardButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();



private:
    Ui::MainWindow *ui;
    Toy toy;
};
#endif // MAINWINDOW_H
