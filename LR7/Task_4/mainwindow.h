#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QTableWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QGroupBox>
#include <QSplitter>
#include "hashtable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void insertKey();
    void searchKey();
    void fillWithCollisions();
    void clearTables();
    void runTimeAnalysis();

private:
    void setupUI();
    void setupCharts();
    void updateStatistics();
    void generateSearchTimeChart();
    void generateCollisionChart();
    void log(const QString &message);

    // UI элементы
    QWidget *centralWidget;

    // Элементы управления
    QLineEdit *keyInput;
    QPushButton *insertButton;
    QPushButton *searchButton;
    QPushButton *fillButton;
    QPushButton *clearButton;
    QPushButton *analyzeButton;
    QSpinBox *fillCountSpinBox;
    QComboBox *hashMethodCombo;
    QTextEdit *logOutput;

    // Статистика
    QTableWidget *statsTable;

    // Графики
    QChartView *searchTimeChartView;
    QChartView *collisionChartView;
    QChart *searchTimeChart;
    QChart *collisionChart;

    // Хеш-таблицы
    QVector<HashTable*> tables;
    QVector<int> tableSizes;
};

#endif // MAINWINDOW_H
