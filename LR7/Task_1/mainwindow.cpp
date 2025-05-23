#include "mainwindow.h"
#include "bubblequeuesorter.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), queue(10)
{
    ui->setupUi(this);
    // Главный виджет и layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Отображение очереди
    queueDisplay = new QListWidget();
    mainLayout->addWidget(queueDisplay);

    // Поле ввода и кнопка Enqueue
    QHBoxLayout *inputLayout = new QHBoxLayout();
    valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Введите ЦЕЛОЕ ЧИСЛО(от -2^31 до 2^31-1)");
    QPushButton *enqueueBtn = new QPushButton("Enqueue");
    inputLayout->addWidget(valueInput);
    inputLayout->addWidget(enqueueBtn);
    mainLayout->addLayout(inputLayout);

    // Основные кнопки операций
    QHBoxLayout *opsLayout = new QHBoxLayout();
    QPushButton *dequeueBtn = new QPushButton("Dequeue");
    QPushButton *frontBtn = new QPushButton("Front");
    QPushButton *backBtn = new QPushButton("Back");
    opsLayout->addWidget(dequeueBtn);
    opsLayout->addWidget(frontBtn);
    opsLayout->addWidget(backBtn);
    mainLayout->addLayout(opsLayout);

    // Кнопки информации
    QHBoxLayout *infoLayout = new QHBoxLayout();
    QPushButton *sizeBtn = new QPushButton("Size");
    QPushButton *isEmptyBtn = new QPushButton("Is Empty?");
    infoLayout->addWidget(sizeBtn);
    infoLayout->addWidget(isEmptyBtn);
    mainLayout->addLayout(infoLayout);

    // Кнопка сортировки
    QPushButton *sortBtn = new QPushButton("Bubble Sort");
    mainLayout->addWidget(sortBtn);

    // Подключение сигналов
    connect(enqueueBtn, &QPushButton::clicked, this, &MainWindow::enqueueClicked);
    connect(dequeueBtn, &QPushButton::clicked, this, &MainWindow::dequeueClicked);
    connect(frontBtn, &QPushButton::clicked, this, &MainWindow::frontClicked);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::backClicked);
    connect(sizeBtn, &QPushButton::clicked, this, &MainWindow::sizeClicked);
    connect(isEmptyBtn, &QPushButton::clicked, this, &MainWindow::isEmptyClicked);
    connect(sortBtn, &QPushButton::clicked, this, &MainWindow::sortClicked);

    setCentralWidget(centralWidget);
    setWindowTitle("Queue Visualizer");
    updateDisplay();
}

void MainWindow::updateDisplay()
{
    queueDisplay->clear();
    if (queue.isEmpty()) {
        queueDisplay->addItem("Queue is empty");
        return;
    }

    // Временный массив для хранения элементов
    QVector<int> tempElements;
    int size = queue.size();

    // Извлекаем и запоминаем элементы
    for (int i = 0; i < size; ++i) {
        int val = queue.dequeue();
        tempElements.append(val);
        queue.enqueue(val);  // Возвращаем элемент обратно в очередь
    }

    // Отображаем элементы
    for (int val : tempElements) {
        queueDisplay->addItem(QString::number(val));
    }
}

void MainWindow::enqueueClicked()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    if (ok) {
        queue.enqueue(value);
        updateDisplay();
        valueInput->clear();
    }
}

void MainWindow::dequeueClicked()
{
    try {
        int val = queue.dequeue();
        QMessageBox::information(this, "Dequeued", QString("Removed: %1").arg(val));
        updateDisplay();
    } catch (...) {
        QMessageBox::warning(this, "Error", "Queue is empty!");
    }
}

void MainWindow::frontClicked()
{
    try {
        QMessageBox::information(this, "Front", QString::number(queue.front()));
    } catch (...) {
        QMessageBox::warning(this, "Error", "Queue is empty!");
    }
}

void MainWindow::backClicked()
{
    try {
        QMessageBox::information(this, "Back", QString::number(queue.back()));
    } catch (...) {
        QMessageBox::warning(this, "Error", "Queue is empty!");
    }
}

void MainWindow::sizeClicked()
{
    QMessageBox::information(this, "Size", QString::number(queue.size()));
}

void MainWindow::isEmptyClicked()
{
    QMessageBox::information(this, "Is Empty", queue.isEmpty() ? "Yes" : "No");
}

void MainWindow::sortClicked()
{
    if (queue.isEmpty()) {
        QMessageBox::warning(this, "Error", "Queue is empty!");
        return;
    }

    BubbleQueueSorter::sort(queue);
    updateDisplay();
    QMessageBox::information(this, "Sorted", "Queue sorted!");
}

MainWindow::~MainWindow() {
    delete ui;
}
