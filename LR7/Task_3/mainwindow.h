#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QFormLayout>

#include "hashtable.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void generateRandom();
    void insertKey();
    void removeKey();
    void containsKey();
    void clearTable();
    void removeNegativeKeys();

private:
    ExtendedHashTable hashTable;

    // Виджеты управления
    QSpinBox   *keySpinBox;
    QPushButton *generateButton;
    QPushButton *insertButton;
    QPushButton *removeButton;
    QPushButton *containsButton;
    QPushButton *clearButton;
    QPushButton *removeNegativeButton;
    QTextEdit  *outputTextEdit;

    void setupUI();
    void updateDisplay();
};

#endif // MAINWINDOW_H
