#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QDate sys = QDate::currentDate();
    Date current(sys.day(), sys.month(), sys.year());
    ui-> label_7 ->setText(current.getFormatted());



    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::on_openFileButton_clicked);
    connect(ui->nextDayButton, &QPushButton::clicked, this, &MainWindow::on_nextDayButton_clicked);
    connect(ui->prevDayButton, &QPushButton::clicked, this, &MainWindow::on_prevDayButton_clicked);
    connect(ui->isLeapButton, &QPushButton::clicked, this, &MainWindow::on_isLeapButton_clicked);
    connect(ui->weekNumberButton, &QPushButton::clicked, this, &MainWindow::on_weekNumberButton_clicked);
    connect(ui->birthdayButton, &QPushButton::clicked, this, &MainWindow::on_birthdayButton_clicked);
    connect(ui->durationButton, &QPushButton::clicked, this, &MainWindow::on_durationButton_clicked);
    connect(ui->addDateButton, &QPushButton::clicked, this, &MainWindow::on_addDateButton_clicked);
    connect(ui->editDateButton, &QPushButton::clicked, this, &MainWindow::on_editDateButton_clicked);


    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers << "Дата" << "Следующий день" << "Номер недели" << "Разница с след. датой";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
  // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

   currentFileName.clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл с датами"),"", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {

        currentFileName = fileName;
        try {
            readDatesFromFile(fileName);
            displayDates();
        }
        catch(...) {
            QMessageBox::critical(this, "Ошибка", "Не удалось прочитать даты из файла");
        }
    }
}

void MainWindow::readDatesFromFile(const QString &filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для чтения!");
    }
    QTextStream in(&file);
    dates.clear();
    // Предполагаем, что каждая дата записана через пробел или перенос строки в формате dd.mm.yyyy
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList dateStrings = line.split(" ", Qt::SkipEmptyParts);
        for (const QString &dateStr : dateStrings) {
            int d, m, y;
            QList<QString> parts = dateStr.split(".");
            if (parts.size() == 3) {
                d = parts.at(0).toInt();
                m = parts.at(1).toInt();
                y = parts.at(2).toInt();
                dates.push_back(Date(d, m, y));
            } else {
                QMessageBox::warning(this, "Предупреждение", "Неверный формат даты: " + dateStr);
            }
        }
    }
    file.close();

}

Date MainWindow::parseDateFromString(const QString &str) const
{
    QStringList parts = str.split(".");
    if (parts.size() == 3) {
        int d = parts.at(0).toInt();
        int m = parts.at(1).toInt();
        int y = parts.at(2).toInt();
        return Date(d, m, y);
    }
    return Date();
}

void MainWindow::displayDates()
{
    ui->tableWidget->setRowCount(0);
    for (size_t i = 0; i < dates.size(); i++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int row = ui->tableWidget->rowCount() - 1;

        Date current = dates[i];
        Date nextDay = current.NextDay();
        short wNum = current.WeekNumber();

        int diff = 0;
        if (i + 1 < dates.size()) {
            diff = current.Duration(dates[i + 1]);
        }

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(current.getFormatted()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nextDay.getFormatted()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(wNum)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(diff)));
    }
}


// Следующий день
void MainWindow::on_nextDayButton_clicked()
{
    QString inputStr = ui->inputDateEdit->text();
    Date d = parseDateFromString(inputStr);
    Date nd = d.NextDay();
    ui-> label->setText(nd.getFormatted());
}

// Предыдущий день
void MainWindow::on_prevDayButton_clicked()
{
    QString inputStr = ui->inputDateEdit->text();
    Date d = parseDateFromString(inputStr);
    Date pd = d.PreviousDay();
    ui->label_2->setText(pd.getFormatted());
}

// Високосный?
void MainWindow::on_isLeapButton_clicked()
{
    QString inputStr = ui->inputDateEdit->text();
    Date d = parseDateFromString(inputStr);
    if (d.IsLeap()) {
        ui->label_3->setText("Да");
    } else {
        ui->label_3->setText("Нет");
    }
}

// Номер недели
void MainWindow::on_weekNumberButton_clicked()
{
    QString inputStr = ui->inputDateEdit->text();
    Date d = parseDateFromString(inputStr);
    short wNum = d.WeekNumber();
    ui->label_4->setText(QString::number(wNum));
}

// День рождения
void MainWindow::on_birthdayButton_clicked()
{

    QDate sys = QDate::currentDate();
    Date current(sys.day(), sys.month(), sys.year());

    QString inputStr = ui->inputDateEdit->text();
    Date bday = parseDateFromString(inputStr);

    int days = current.DaysTillYourBithday(bday);
    ui->label_5->setText(QString::number(days));
}

// Количество дней (между сегодняшней датой и введенной)
void MainWindow::on_durationButton_clicked()
{
    QDate sys = QDate::currentDate();
    Date current(sys.day(), sys.month(), sys.year());

    QString inputStr = ui->inputDateEdit->text();
    Date d = parseDateFromString(inputStr);

    int diff = current.Duration(d);
    ui->label_6->setText(QString::number(diff));
}

// Добавить дату
void MainWindow::on_addDateButton_clicked()
{
    QString inputStr = ui->inputDateEdit->text();
    Date newDate = parseDateFromString(inputStr);

    dates.push_back(newDate);

    if (!currentFileName.isEmpty()) {
        QFile file(currentFileName);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << " " << newDate.getFormatted();
            file.close();
        }
        else {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для добавления.");
        }
    } else {
        QMessageBox::information(this, "Внимание", "Файл не открыт. Дата добавлена только в программу.");
    }
    displayDates();
}

void MainWindow::on_editDateButton_clicked()
{
    bool ok = false;
    int index = QInputDialog::getInt(this, tr("Изменить дату"),tr("Номер даты для изменения (1 - %1):").arg(dates.size()),1, 1, dates.size(), 1, &ok);
    if (!ok) return;
    index--;

    QString newDateStr = QInputDialog::getText(this, tr("Новая дата"),tr("Введите новую дату (dd.mm.yyyy):"));
    if(newDateStr.isEmpty()){
        QMessageBox::warning(this, tr("Ошибка"), tr("Дата не введена!"));
        return;
    }
    Date newDate = parseDateFromString(newDateStr);


    dates[index] = newDate;

    QFile file(currentFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось открыть файл для записи"));
        return;
    }
    QTextStream out(&file);
    for (size_t i = 0; i < dates.size(); i++) {
        out << dates[i].getFormatted();
        if (i + 1 < dates.size()) {
            out << " ";
        }
    }
    file.close();

    displayDates();
    QMessageBox::information(this, tr("Успех"), tr("Дата успешно изменена"));
}
