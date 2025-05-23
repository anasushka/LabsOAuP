// mainwindow.cpp
#include "mainwindow.h"
#include <QMessageBox>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    updateDisplay();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    // Центральный виджет и общий layout
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    // Группа контролов
    auto *controlsBox = new QGroupBox("Введите ключ от -10 до 10", this);
    auto *form = new QFormLayout(controlsBox);

    keySpinBox = new QSpinBox(this);
    keySpinBox->setRange(-10, 10);
    keySpinBox->setToolTip("Выберите ключ от -10 до 10");

    auto makeBtn = [&](const QString &text, const QString &tip) {
        auto *btn = new QPushButton(text, this);
        btn->setFixedHeight(28);
        btn->setToolTip(tip);
        return btn;
    };

    generateButton       = makeBtn("Генерировать 20", "Добавить 20 случайных ключей");
    insertButton         = makeBtn("Добавить",        "Вставить указанный ключ");
    removeButton         = makeBtn("Удалить",         "Удалить указанный ключ");
    containsButton       = makeBtn("Проверить",       "Проверить наличие ключа");
    clearButton          = makeBtn("Очистить",        "Удалить все ключи");
    removeNegativeButton = makeBtn("Удалить отрицотрицательные",  "Удалить все отрицательные ключи");

    form->addRow("Ключ:", keySpinBox);
    form->addRow(generateButton, insertButton);
    form->addRow(removeButton, containsButton);
    form->addRow(clearButton, removeNegativeButton);

    // Поле вывода
    outputTextEdit = new QTextEdit(this);
    outputTextEdit->setReadOnly(true);


    // Собираем интерфейс
    mainLayout->addWidget(controlsBox);
    mainLayout->addWidget(outputTextEdit, 1);
    setCentralWidget(central);

    // Подключаем слоты
    connect(generateButton,       &QPushButton::clicked, this, &MainWindow::generateRandom);
    connect(insertButton,         &QPushButton::clicked, this, &MainWindow::insertKey);
    connect(removeButton,         &QPushButton::clicked, this, &MainWindow::removeKey);
    connect(containsButton,       &QPushButton::clicked, this, &MainWindow::containsKey);
    connect(clearButton,          &QPushButton::clicked, this, &MainWindow::clearTable);
    connect(removeNegativeButton, &QPushButton::clicked, this, &MainWindow::removeNegativeKeys);

    setWindowTitle("Хеш-таблица");
    resize(800, 600);
}

void MainWindow::updateDisplay() {
    QString txt = hashTable.print();
    int negCount = hashTable.countNegativeKeys();

    outputTextEdit->setPlainText(txt);
}

void MainWindow::generateRandom() {
    hashTable.clear();
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dist(-10, 10);
    for (int i = 0; i < 20; ++i) hashTable.insert(dist(gen));
    updateDisplay();
    QMessageBox::information(this, "Генерация", "Добавлено 20 случайных ключей");
}

void MainWindow::insertKey() {
    hashTable.insert(keySpinBox->value());
    updateDisplay();
    QMessageBox::information(this, "Добавление", "Ключ добавлен");
}

void MainWindow::removeKey() {
    bool ok = hashTable.remove(keySpinBox->value());
    updateDisplay();
    QMessageBox::information(this, ok ? "Удаление" : "Ошибка",
                             ok ? "Ключ удалён" : "Ключ не найден");
}

void MainWindow::containsKey() {
    bool found = hashTable.contains(keySpinBox->value());
    QMessageBox::information(this, "Проверка",
                             found ? "Ключ присутствует" : "Ключ отсутствует");
}

void MainWindow::clearTable() {
    hashTable.clear();
    updateDisplay();
    QMessageBox::information(this, "Очистка", "Таблица очищена");
}

void MainWindow::removeNegativeKeys() {
    int removed = hashTable.removeNegativeKeys();
    updateDisplay();
    QMessageBox::information(this, "Удаление отрицательных",
                             QString("Удалено %1 ключей").arg(removed));
}
