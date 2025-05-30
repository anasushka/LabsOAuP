#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "arrayheap.h"
#include "listheap.h"

class QTextEdit;
class QSpinBox;
class QPushButton;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onArrayInsert();
    void onArrayExtract();
    void onArrayClear();
    void onListInsert();
    void onListExtract();
    void onListClear();
    void updateHeapDisplays();

private:
    ArrayHeap arrayHeap;
    QSharedPointer<ListHeap> listHeap;

    QWidget *centralWidget;
    QHBoxLayout *mainLayout;

    QGroupBox *arrayHeapGroup;
    QVBoxLayout *arrayLayout;
    QSpinBox *arrayValueSpin;
    QHBoxLayout *arrayButtonLayout;
    QPushButton *arrayInsertButton;
    QPushButton *arrayExtractButton;
    QPushButton *arrayClearButton;
    QTextEdit *arrayHeapInfo;

    QGroupBox *listHeapGroup;
    QVBoxLayout *listLayout;
    QSpinBox *listValueSpin;
    QHBoxLayout *listButtonLayout;
    QPushButton *listInsertButton;
    QPushButton *listExtractButton;
    QPushButton *listClearButton;
    QTextEdit *listHeapInfo;
};

#endif // MAINWINDOW_H
