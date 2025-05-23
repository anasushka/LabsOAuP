#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTreeWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "avl.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadFromTableClicked();
    void onInsertClicked();
    void onRemoveClicked();
    void onFindClicked();
    void onBalanceClicked();
    void onClearClicked();
    void onPreOrderClicked();
    void onInOrderClicked();
    void onPostOrderClicked();
    void onMaxDepthClicked();

private:
    void setupUI();
    void setupTable();
    void setupConnections();

    QTableWidget *tableWidget;
    QTreeWidget *treeWidget;
    QTextEdit *outputText;

    QPushButton *loadTableBtn;
    QPushButton *insertBtn;
    QPushButton *removeBtn;
    QPushButton *findBtn;
    QPushButton *balanceBtn;
    QPushButton *clearBtn;
    QPushButton *preOrderBtn;
    QPushButton *inOrderBtn;
    QPushButton *postOrderBtn;
    QPushButton *maxDepthBtn;

    QWidget *centralWidget;
    AVL avlTree;
};

#endif // MAINWINDOW_H
