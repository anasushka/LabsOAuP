#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QMessageBox>
#include <QDebug>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(800, 600);


    connect(ui->atPB,        SIGNAL(clicked(bool)), this, SLOT(atSlot()));
    connect(ui->capacityPB,  SIGNAL(clicked(bool)), this, SLOT(capacitySlot()));
    connect(ui->clearPB,     SIGNAL(clicked(bool)), this, SLOT(clearSlot()));
    connect(ui->dataPB,      SIGNAL(clicked(bool)), this, SLOT(dataSlot()));
    connect(ui->emptyPB,     SIGNAL(clicked(bool)), this, SLOT(emptySlot()));
    connect(ui->erasePB,     SIGNAL(clicked(bool)), this, SLOT(eraseSlot()));
    connect(ui->maxSizePB,   SIGNAL(clicked(bool)), this, SLOT(maxSizeSlot()));
    connect(ui->popBackPB,   SIGNAL(clicked(bool)), this, SLOT(popBackSlot()));
    connect(ui->pushBackPB,  SIGNAL(clicked(bool)), this, SLOT(pushBackSlot()));
    connect(ui->reservePB,   SIGNAL(clicked(bool)), this, SLOT(reserveSlot()));
    connect(ui->resizePB,    SIGNAL(clicked(bool)), this, SLOT(resizeSlot()));
    connect(ui->sizePB,      SIGNAL(clicked(bool)), this, SLOT(sizeSlot()));



    setWindowTitle(tr("Демонстрация методов"));

    ui->label->setAlignment(Qt::AlignCenter);
    ui->labelVector->setAlignment(Qt::AlignCenter);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    QStringList list;
    for (auto i : a) {
        list << QString::number(i);
    }
    QString s = list.join(", ");
    ui->labelVector->setText("vector<int> = " + s);
}



void MainWindow::atSlot()
{
   QString str = ui->lineEdit->text();

    int s = str.toInt();

    if (s == 0 && ui->lineEdit->text() != "0") {
        QMessageBox::warning(this, "At", "Error");
        return;
    }

    if (s >= 0 && s < a.size()) {
        QMessageBox::information(this, "At", QString::number(a[s]));
    } else {
        QMessageBox::warning(this, "At", "Error");
    }
}

void MainWindow::capacitySlot()
{
    QMessageBox::information(this, "Capacity", QString::number(a.capacity()));
}

void MainWindow::clearSlot()
{
    a.clear();
    update();
}

void MainWindow::dataSlot()
{
    QString ptrStr = QString("0x%1").arg(
        reinterpret_cast<quintptr>(a.data()),
        QT_POINTER_SIZE * 2, 16, QChar('0'));
    QMessageBox::information(this, "Data", ptrStr);
}

void MainWindow::emptySlot()
{
    // Судя по названию "EmplaceBack" в старом коде был какой-то баг. Исправим на "Empty".
    QMessageBox::information(this, "Empty", a.empty() ? "Empty" : "Not Empty");
}

void MainWindow::eraseSlot()
{
    QString s = ui->lineEdit->text();
    int i1 = s.toInt();

    if (i1 == 0 && s[0] != '0') {
        QMessageBox::warning(this, "Erase", "Error");
        return;
    }

    if (i1 >= 0 && i1 < a.size()) {
        qDebug() << i1;
        a.erase(a.begin() + i1);
        QMessageBox::information(this, "Erase", "Ok");
    } else {
        QMessageBox::warning(this, "Erase", "Error");
    }
    update();
}

void MainWindow::maxSizeSlot()
{
    QMessageBox::information(this, "Max Size", QString::number(a.max_size()));
}

void MainWindow::popBackSlot()
{
    if (!a.empty()) {
        a.pop_back();
    }
    update();
}

void MainWindow::pushBackSlot()
{
    QString s = ui->lineEdit->text();
    int i1 = s.toInt();

    if (i1 == 0 && s[0] != '0') {
        QMessageBox::warning(this, "PushBack", "Error");
        return;
    }

    a.push_back(i1);
    QMessageBox::information(this, "PushBack", "Ok");
    update();
}

void MainWindow::reserveSlot()
{
    QString s = ui->lineEdit->text();
    int i1 = s.toInt();

    if (i1 == 0 && s[0] != '0') {
        QMessageBox::warning(this, "Reserve", "Error");
        return;
    }

    a.reserve(i1);
    QMessageBox::information(this, "Reserve", "Ok");
}

void MainWindow::resizeSlot()
{
    QString s = ui->lineEdit->text();
    int i1 = s.toInt();

    if (i1 == 0 && s[0] != '0') {
        QMessageBox::warning(this, "Resize", "Error");
        return;
    }

    if (i1 >= 0) {
        a.resize(i1);
        QMessageBox::information(this, "Resize", "Ok");
    } else {
        QMessageBox::warning(this, "Resize", "Некорректный размер");
    }
    update();
}

void MainWindow::sizeSlot()
{
    QMessageBox::information(this, "Size", QString::number(a.size()));
}



