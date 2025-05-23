#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QLineEdit>
#include "binarytreesearch.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    BinarySearchTree bst;
    QTreeWidget *m_treeWidget;

    // Поля ввода
    QLineEdit *m_editNode;
    QLineEdit *m_editParent;
    QLineEdit *m_editSubtree;
    QLineEdit *m_editDirection;
    QLineEdit *m_editLCA1;
    QLineEdit *m_editLCA2;

    // Методы
    void updateTreeDisplay();
    void populateTreeWidget(QTreeWidgetItem* parentItem, BSTNode* node);
};

#endif // MAINWINDOW_H
