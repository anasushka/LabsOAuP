#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QComboBox;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QLabel;
class QWidget;

#include "bstree.h"
#include "hashtable.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onTreeTypeChanged(int index);
    void bstInsert();
    void bstCheck();
    void bstUpdateIterators();
    void hashInsert();
    void hashErase();
    void hashContains();
    void hashClear();
    void hashRehash();

private:
    // Настройка вкладок
    void setupBSTTab(QWidget *parent);
    void setupHashTab(QWidget *parent);

    // Обновление BST
    void updateBstOutputs();
    QString buildTreeStringMap(BSTNode<int, QString>* node, int indent = 0);
    QString buildTreeStringSet(BSTNode<int, char>* node, int indent = 0);

    // Обновление Hash Table
    void updateHashDisplay();

    // BST виджеты
    QComboBox *comboTreeType;
    QLineEdit *lineEditKey;
    QLineEdit *lineEditValue;
    QPushButton *btnBstInsert;
    QPushButton *btnBstCheck;
    QPushButton *btnBstUpdateIterator;
    QTextEdit *textBstOutput;  // Вывод обхода итератором
    QTextEdit *textBstTree;    // Структура дерева
    QLabel *bstInfoLabel;      // Информация о BST

    // BST структуры данных
    BSTMap<int, QString> bstMap;
    BSTSet<int> bstSet;

    // Hash Table виджеты
    QLineEdit *lineEditHashKey;
    QLineEdit *lineEditHashValue;
    QPushButton *btnHashInsert;
    QPushButton *btnHashErase;
    QPushButton *btnHashContains;
    QPushButton *btnHashClear;
    QPushButton *btnHashRehash;
    QTextEdit *textHashDisplay;
    QLabel *hashInfoLabel;     // Статистика хеш-таблицы

    // Hash Table структура данных
    HashTable<int, QString> hashTable;
};

#endif // MAINWINDOW_H
