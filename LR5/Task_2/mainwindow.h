#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void onBtnMemcpyClicked();
    void onBtnStrcpyClicked();
    void onBtnStrncpyClicked();
    void onBtnMemmoveClicked();
    void onBtnPushBackClicked();
    void onBtnStrcmpClicked();
    void onBtnStrncmpClicked();
    void onBtnStrchrClicked();
    void onBtnStrlenClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
