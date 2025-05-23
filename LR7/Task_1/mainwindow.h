#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "queue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void enqueueClicked();
    void dequeueClicked();
    void frontClicked();
    void backClicked();
    void sizeClicked();
    void isEmptyClicked();
    void sortClicked();

private:
    void updateDisplay();
    Ui::MainWindow *ui;

    Queue queue;
    QListWidget *queueDisplay;
    QLineEdit *valueInput;
};

#endif // MAINWINDOW_H
