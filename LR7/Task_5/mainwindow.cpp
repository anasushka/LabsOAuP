#include "mainwindow.h"
#include <QMessageBox>
#include <QString>

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    updateDisplay();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    auto *controlsBox = new QGroupBox("", this);
    auto *form = new QFormLayout(controlsBox);

    valueSpinBox = new QSpinBox(this);
    valueSpinBox->setRange(-1000, 1000);
    valueSpinBox->setToolTip("Введите число, ЦЕЛОЕ!!");

    auto makeBtn = [&](const QString &text, const QString &tip) {
        auto *btn = new QPushButton(text, this);
        btn->setFixedHeight(28);
        btn->setToolTip(tip);
        return btn;
    };

    pushFrontButton = makeBtn("push_front", "Добавить значение в начало");
    pushBackButton  = makeBtn("push_back",  "Добавить значение в конец");
    popFrontButton  = makeBtn("pop_front",  "Удалить значение из начала");
    popBackButton   = makeBtn("pop_back",   "Удалить значение из конца");
    clearButton     = makeBtn("clear",      "Очистить deque");
    sizeButton      = makeBtn("size",       "Показать размер");
    emptyButton     = makeBtn("empty",      "Проверить, пуст ли deque");

    form->addRow("Значение:", valueSpinBox);
    form->addRow(pushFrontButton, pushBackButton);
    form->addRow(popFrontButton, popBackButton);
    form->addRow(clearButton, sizeButton);
    form->addRow(emptyButton);

    outputTextEdit = new QTextEdit(this);
    outputTextEdit->setReadOnly(true);

    mainLayout->addWidget(controlsBox);
    mainLayout->addWidget(outputTextEdit, 1);
    setCentralWidget(central);

    connect(pushFrontButton, &QPushButton::clicked, this, &MainWindow::pushFront);
    connect(pushBackButton,  &QPushButton::clicked, this, &MainWindow::pushBack);
    connect(popFrontButton,  &QPushButton::clicked, this, &MainWindow::popFront);
    connect(popBackButton,   &QPushButton::clicked, this, &MainWindow::popBack);
    connect(clearButton,     &QPushButton::clicked, this, &MainWindow::clearDeque);
    connect(sizeButton,      &QPushButton::clicked, this, &MainWindow::showSize);
    connect(emptyButton,     &QPushButton::clicked, this, &MainWindow::showEmpty);

    setWindowTitle("Deque");
     resize(1000, 800);
}

void MainWindow::updateDisplay() {
    QString txt;
    for (size_t i = 0; i < deque.size(); ++i) {
        txt += QString::number(deque[i]) + " ";
    }
    outputTextEdit->setPlainText(txt);
}

void MainWindow::pushFront() {
    deque.push_front(valueSpinBox->value());
    updateDisplay();
}

void MainWindow::pushBack() {
    deque.push_back(valueSpinBox->value());
    updateDisplay();
}

void MainWindow::popFront() {
    if (!deque.empty()) deque.pop_front();
    updateDisplay();
}

void MainWindow::popBack() {
    if (!deque.empty()) deque.pop_back();
    updateDisplay();
}

void MainWindow::clearDeque() {
    // Предполагаем, что в реализации есть метод clear()
    deque.clear();
    updateDisplay();
}

void MainWindow::showSize() {
    QMessageBox::information(this, "Size",
                             QString("Size: %1").arg(deque.size()));
}

void MainWindow::showEmpty() {
    QMessageBox::information(this, "Empty",
                             deque.empty() ? "Yes" : "No");
}
