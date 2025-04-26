#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "bitset.h"      // ваш заголовок с классой BitSet
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelValue->setText("29");

    connect(ui->btnSize,       &QPushButton::clicked, this, &MainWindow::onBtnSizeClicked);
    connect(ui->btnSet,        &QPushButton::clicked, this, &MainWindow::onBtnSetClicked);
    connect(ui->btnReset,      &QPushButton::clicked, this, &MainWindow::onBtnResetClicked);
    connect(ui->btnFlip,       &QPushButton::clicked, this, &MainWindow::onBtnFlipClicked);
    connect(ui->btnTest,       &QPushButton::clicked, this, &MainWindow::onBtnTestClicked);
    connect(ui->btnAll,        &QPushButton::clicked, this, &MainWindow::onBtnAllClicked);
    connect(ui->btnAny,        &QPushButton::clicked, this, &MainWindow::onBtnAnyClicked);
    connect(ui->btnNone,       &QPushButton::clicked, this, &MainWindow::onBtnNoneClicked);
    connect(ui->btnCount,      &QPushButton::clicked, this, &MainWindow::onBtnCountClicked);
    connect(ui->btnToString,   &QPushButton::clicked, this, &MainWindow::onBtnToStringClicked);
    connect(ui->btnToULong,    &QPushButton::clicked, this, &MainWindow::onBtnToULongClicked);
    connect(ui->btnToULLong,   &QPushButton::clicked, this, &MainWindow::onBtnToULLongClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::readSize(int &outSize) {
    bool ok = false;
    int sz = ui->lineEditSize->text().toInt(&ok);
    if (!ok || sz <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный размер (>0)");
        return false;
    }
    outSize = sz;
    return true;
}

bool MainWindow::readPos(int &outPos) {
    bool ok = false;
    int p = ui->lineEditPos->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите корректную позицию (целое)");
        return false;
    }
    outPos = p;
    return true;
}

void MainWindow::onBtnSizeClicked() {
    int sz;
    if (!readSize(sz)) return;
    // просто демонстрируем конструктор
    BitSet bs(sz);
    QMessageBox::information(this, "size",
                             QString("Создан BitSet размером %1 бит").arg(sz)
                             );
}

void MainWindow::onBtnSetClicked() {
    int sz;
    if (!readSize(sz)) return;
    int pos;
    if (!readPos(pos)) return;
    BitSet bs(sz);
    bs.set(pos);
    QMessageBox::information(this, "set",
                             QString("После set(%1): %2").arg(pos).arg(bs.to_string())
                             );
}

void MainWindow::onBtnResetClicked() {
    int sz;
    if (!readSize(sz)) return;
    int pos;
    if (!readPos(pos)) return;
    BitSet bs(sz);
    bs.set();       // сначала заполним все единицами, чтобы показать reset
    bs.reset(pos);
    QMessageBox::information(this, "reset",
                             QString("После reset(%1): %2").arg(pos).arg(bs.to_string())
                             );
}

void MainWindow::onBtnFlipClicked() {
    int sz;
    if (!readSize(sz)) return;
    BitSet bs(sz);
    bs.set();       // для наглядности
    bs.flip();      // инвертируем все
    QMessageBox::information(this, "flip",
                             QString("После flip(): %1").arg(bs.to_string())
                             );
}

void MainWindow::onBtnTestClicked() {
    int sz;
    if (!readSize(sz)) return;
    int pos;
    if (!readPos(pos)) return;
    BitSet bs(sz);
    bs.set(pos);
    bool v = bs.test(pos);
    QMessageBox::information(this, "test",
                             QString("test(%1) → %2")
                                 .arg(pos)
                                 .arg(v ? "true" : "false")
                             );
}

void MainWindow::onBtnAllClicked() {
    int sz;
    if (!readSize(sz)) return;
    BitSet bs(sz);
    bs.set();   // заполняем
    bool v = bs.all();
    QMessageBox::information(this, "all",
                             QString("all() → %1").arg(v ? "true" : "false")
                             );
}

void MainWindow::onBtnAnyClicked() {
    int sz;
    if (!readSize(sz)) return;
    BitSet bs(sz);
    // по умолчанию всё нули → any() false
    bool v = bs.any();
    QMessageBox::information(this, "any",
                             QString("any() → %1").arg(v ? "true" : "false")
                             );
}

void MainWindow::onBtnNoneClicked() {
    int sz;
    if (!readSize(sz)) return;
    BitSet bs(sz);
    bool v = bs.none();
    QMessageBox::information(this, "none",
                             QString("none() → %1").arg(v ? "true" : "false")
                             );
}

void MainWindow::onBtnCountClicked() {
    int sz;
    if (!readSize(sz)) return;
    BitSet bs(sz);
    bs.set();   // для демонстрации пусть все единицы
    int c = bs.count();
    QMessageBox::information(this, "count",
                             QString("count() → %1").arg(c)
                             );
}

void MainWindow::onBtnToStringClicked() {
    int sz;
    if (!readSize(sz)) return;

    bool ok = false;
    unsigned long long val = ui->labelValue->text().toULongLong(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректное число в метке");
        return;
    }

    BitSet bs(sz);
    // выставляем биты по числу val
    for (int i = 0; i < sz; ++i) {
        if (val & (1ULL << i))
            bs.set(i);
    }

    QMessageBox::information(this, "to_string",
                             QString("Число %1 → битовая строка:\n%2")
                                 .arg(val)
                                 .arg(bs.to_string())
                             );
}

void MainWindow::onBtnToULongClicked() {
    int sz;
    if (!readSize(sz)) return;

    bool ok = false;
    unsigned long long val = ui->labelValue->text().toULongLong(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректное число в метке");
        return;
    }

    BitSet bs(sz);
    for (int i = 0; i < sz; ++i) {
        if (val & (1ULL << i))
            bs.set(i);
    }

    unsigned long result = bs.to_ulong();
    QMessageBox::information(this, "to_ulong",
                             QString("BitSet из %1 → to_ulong() = %2")
                                 .arg(val)
                                 .arg((qulonglong)result)
                             );
}

void MainWindow::onBtnToULLongClicked() {
    int sz;
    if (!readSize(sz)) return;

    bool ok = false;
    unsigned long long val = ui->labelValue->text().toULongLong(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректное число в метке");
        return;
    }

    BitSet bs(sz);
    for (int i = 0; i < sz; ++i) {
        if (val & (1ULL << i))
            bs.set(i);
    }

    unsigned long long result = bs.to_ullong();
    QMessageBox::information(this, "to_ullong",
                             QString("BitSet из %1 → to_ullong() = %2")
                                 .arg(val)
                                 .arg(result)
                             );
}

