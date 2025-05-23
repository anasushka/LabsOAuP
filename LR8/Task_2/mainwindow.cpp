#include "mainwindow.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), listHeap(new ListHeap())
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    arrayHeapGroup = new QGroupBox("Куча на массиве", centralWidget);
    arrayLayout = new QVBoxLayout(arrayHeapGroup);
    arrayLayout->setSpacing(10);

    arrayValueSpin = new QSpinBox(arrayHeapGroup);
    arrayValueSpin->setRange(-1000, 1000);
    arrayValueSpin->setFixedWidth(100);

    arrayButtonLayout = new QHBoxLayout();
    arrayButtonLayout->setSpacing(5);
    arrayInsertButton = new QPushButton("Добавить", arrayHeapGroup);
    arrayExtractButton = new QPushButton("Извлечь максимум", arrayHeapGroup);
    arrayClearButton = new QPushButton("Очистить", arrayHeapGroup);

    arrayButtonLayout->addWidget(arrayInsertButton);
    arrayButtonLayout->addWidget(arrayExtractButton);
    arrayButtonLayout->addWidget(arrayClearButton);

    arrayHeapInfo = new QTextEdit(arrayHeapGroup);
    arrayHeapInfo->setReadOnly(true);

    arrayLayout->addWidget(arrayValueSpin, 0, Qt::AlignHCenter);
    arrayLayout->addLayout(arrayButtonLayout);
    arrayLayout->addWidget(arrayHeapInfo);

    listHeapGroup = new QGroupBox("Куча на списке", centralWidget);
    listLayout = new QVBoxLayout(listHeapGroup);
    listLayout->setSpacing(10);

    listValueSpin = new QSpinBox(listHeapGroup);
    listValueSpin->setRange(-1000, 1000);
    listValueSpin->setFixedWidth(100);

    listButtonLayout = new QHBoxLayout();
    listButtonLayout->setSpacing(5);
    listInsertButton = new QPushButton("Добавить", listHeapGroup);
    listExtractButton = new QPushButton("Извлечь максимум", listHeapGroup);
    listClearButton = new QPushButton("Очистить", listHeapGroup);

    listButtonLayout->addWidget(listInsertButton);
    listButtonLayout->addWidget(listExtractButton);
    listButtonLayout->addWidget(listClearButton);

    listHeapInfo = new QTextEdit(listHeapGroup);
    listHeapInfo->setReadOnly(true);

    listLayout->addWidget(listValueSpin, 0, Qt::AlignHCenter);
    listLayout->addLayout(listButtonLayout);
    listLayout->addWidget(listHeapInfo);

    mainLayout->addWidget(arrayHeapGroup);
    mainLayout->addWidget(listHeapGroup);

    connect(arrayInsertButton, &QPushButton::clicked, this, &MainWindow::onArrayInsert);
    connect(arrayExtractButton, &QPushButton::clicked, this, &MainWindow::onArrayExtract);
    connect(arrayClearButton, &QPushButton::clicked, this, &MainWindow::onArrayClear);

    connect(listInsertButton, &QPushButton::clicked, this, &MainWindow::onListInsert);
    connect(listExtractButton, &QPushButton::clicked, this, &MainWindow::onListExtract);
    connect(listClearButton, &QPushButton::clicked, this, &MainWindow::onListClear);

    updateHeapDisplays();

    setWindowTitle("Демонстрация кучи");
    resize(850, 620);
}

MainWindow::~MainWindow() {}

void MainWindow::onArrayInsert() {
    int value = arrayValueSpin->value();
    arrayHeap.insert(value);
    updateHeapDisplays();
}

void MainWindow::onArrayExtract() {
    try {
        int max = arrayHeap.extractMax();
        QMessageBox::information(this, "Извлечение максимума",
                                 QString("Извлечённое значение: %1").arg(max));
        updateHeapDisplays();
    } catch (const std::out_of_range&) {
        QMessageBox::warning(this, "Ошибка", "Куча на массиве пуста");
    }
}

void MainWindow::onArrayClear() {
    arrayHeap.clear();
    updateHeapDisplays();
}

void MainWindow::onListInsert() {
    int value = listValueSpin->value();
    listHeap->insert(value);
    updateHeapDisplays();
}

void MainWindow::onListExtract() {
    try {
        int max = listHeap->extractMax();
        QMessageBox::information(this, "Извлечение максимума",
                                 QString("Извлечённое значение: %1").arg(max));
        updateHeapDisplays();
    } catch (const std::out_of_range&) {
        QMessageBox::warning(this, "Ошибка", "Куча на списке пуста");
    }
}

void MainWindow::onListClear() {
    listHeap->clear();
    updateHeapDisplays();
}

void MainWindow::updateHeapDisplays() {
    arrayHeapInfo->clear();
    if (arrayHeap.isEmpty()) {
        arrayHeapInfo->append("Куча пуста");
    } else {
        arrayHeapInfo->append(QString("Размер: %1").arg(arrayHeap.size()));
        arrayHeapInfo->append(QString("Максимум: %1").arg(arrayHeap.getMax()));
        arrayHeapInfo->append("Элементы:");
        for (int val : arrayHeap.toVector()) {
            arrayHeapInfo->append(QString::number(val));
        }
    }

    listHeapInfo->clear();
    if (listHeap->isEmpty()) {
        listHeapInfo->append("Куча пуста");
    } else {
        listHeapInfo->append(QString("Размер: %1").arg(listHeap->size()));
        listHeapInfo->append(QString("Максимум: %1").arg(listHeap->getMax()));
        listHeapInfo->append("Элементы:");
        for (int val : listHeap->toVector()) {
            listHeapInfo->append(QString::number(val));
        }
    }
}
