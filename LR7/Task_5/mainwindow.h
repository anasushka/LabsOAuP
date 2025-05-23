#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QFormLayout>

#include "deque.h"  // Ваша реализация Deque<T>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void pushFront();
    void pushBack();
    void popFront();
    void popBack();
    void clearDeque();
    void showSize();
    void showEmpty();

private:
    Deque<int> deque;

    QSpinBox   *valueSpinBox;
    QPushButton *pushFrontButton;
    QPushButton *pushBackButton;
    QPushButton *popFrontButton;
    QPushButton *popBackButton;
    QPushButton *clearButton;
    QPushButton *sizeButton;
    QPushButton *emptyButton;
    QTextEdit  *outputTextEdit;

    void setupUI();
    void updateDisplay();
};

#endif // MAINWINDOW_H
