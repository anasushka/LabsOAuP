#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <algorithm>
#include <QRandomGenerator>
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /* connect(ui->pushButtonOpen, &QPushButton::clicked, this, &MainWindow::on_pushButtonOpen_clicked);
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &MainWindow::on_pushButtonSave_clicked);
    connect(ui->pushButtonSortAge, &QPushButton::clicked, this, &MainWindow::on_pushButtonSortAge_clicked);
    connect(ui->pushButtonFindPairs, &QPushButton::clicked, this, &MainWindow::on_pushButtonFindPairs_clicked);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &MainWindow::on_pushButtonEdit_clicked);
    connect(ui->pushButtonExit, &QPushButton::clicked, this, &MainWindow::on_pushButtonExit_clicked);
    connect(ui->pushButtonAddCandidate, &QPushButton::clicked, this, &MainWindow::on_pushButtonAddCandidate_clicked);
*/


    ui->tableWidgetGrooms->setColumnCount(5);
    ui->tableWidgetGrooms->setHorizontalHeaderLabels(QStringList() << "ID" << "Имя" << "Возраст" << "Рост" << "Вес");
    ui->tableWidgetGrooms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetBrides->setColumnCount(5);
    ui->tableWidgetBrides->setHorizontalHeaderLabels(QStringList() << "ID" << "Имя" << "Возраст" << "Рост" << "Вес");
    ui->tableWidgetBrides->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


MainWindow::~MainWindow()
{
    delete ui;
}

// id;name;age;height;weight;habits;hobby;minAge;maxAge;minHeight;maxHeight;minWeight;maxWeight;gender
bool MainWindow::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл."));
        return false;
    }

    m_grooms.clear();
    m_brides.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;
        QStringList parts = line.split(";");
        if (parts.size() < 14)
            continue;

        int id = parts[0].toInt();
        QString name = parts[1];
        int age = parts[2].toInt();
        int height = parts[3].toInt();
        int weight = parts[4].toInt();
        QString habits = parts[5];
        QString hobby = parts[6];
        int minAge = parts[7].toInt();
        int maxAge = parts[8].toInt();
        int minHeight = parts[9].toInt();
        int maxHeight = parts[10].toInt();
        int minWeight = parts[11].toInt();
        int maxWeight = parts[12].toInt();
        QString gender = parts[13];

        Candidate c(id, name, age, height, weight, habits, hobby,
                    minAge, maxAge, minHeight, maxHeight, minWeight, maxWeight, gender);
         c.setIsActive(true);

        if(gender == "M")
            m_grooms.append(c);
        else if(gender == "F")
            m_brides.append(c);
    }
    file.close();
    updateTableWidgets();
    return true;
}


bool MainWindow::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл."));
        return false;
    }

    QTextStream out(&file);

    for (const Candidate &c : m_grooms) {
        out << c.getId() << ";"
            << c.getName() << ";"
            << c.getAge() << ";"
            << c.getHeight() << ";"
            << c.getWeight() << ";"
            << c.getHabits() << ";"
            << c.getHobby() << ";"
            << c.getMinAge() << ";"
            << c.getMaxAge() << ";"
            << c.getMinHeight() << ";"
            << c.getMaxHeight() << ";"
            << c.getMinWeight() << ";"
            << c.getMaxWeight() << ";"
            << c.getGender() << "\n";
    }

    for (const Candidate &c : m_brides) {
        out << c.getId() << ";"
            << c.getName() << ";"
            << c.getAge() << ";"
            << c.getHeight() << ";"
            << c.getWeight() << ";"
            << c.getHabits() << ";"
            << c.getHobby() << ";"
            << c.getMinAge() << ";"
            << c.getMaxAge() << ";"
            << c.getMinHeight() << ";"
            << c.getMaxHeight() << ";"
            << c.getMinWeight() << ";"
            << c.getMaxWeight() << ";"
            << c.getGender() << "\n";
    }
    file.close();
    return true;
}

void MainWindow::updateTableWidgets()
{

    ui->tableWidgetGrooms->clearContents();
    ui->tableWidgetGrooms->setRowCount(m_grooms.size());
    for (int i = 0; i < m_grooms.size(); ++i) {
        const Candidate &c = m_grooms.at(i);
        ui->tableWidgetGrooms->setItem(i, 0, new QTableWidgetItem(QString::number(c.getId())));
        ui->tableWidgetGrooms->setItem(i, 1, new QTableWidgetItem(c.getName()));
        ui->tableWidgetGrooms->setItem(i, 2, new QTableWidgetItem(QString::number(c.getAge())));
        ui->tableWidgetGrooms->setItem(i, 3, new QTableWidgetItem(QString::number(c.getHeight())));
        ui->tableWidgetGrooms->setItem(i, 4, new QTableWidgetItem(QString::number(c.getWeight())));
    }


    ui->tableWidgetBrides->clearContents();
    ui->tableWidgetBrides->setRowCount(m_brides.size());
    for (int i = 0; i < m_brides.size(); ++i) {
        const Candidate &c = m_brides.at(i);
        ui->tableWidgetBrides->setItem(i, 0, new QTableWidgetItem(QString::number(c.getId())));
        ui->tableWidgetBrides->setItem(i, 1, new QTableWidgetItem(c.getName()));
        ui->tableWidgetBrides->setItem(i, 2, new QTableWidgetItem(QString::number(c.getAge())));
        ui->tableWidgetBrides->setItem(i, 3, new QTableWidgetItem(QString::number(c.getHeight())));
        ui->tableWidgetBrides->setItem(i, 4, new QTableWidgetItem(QString::number(c.getWeight())));
    }
}


void MainWindow::sortByAge()
{
    std::sort(m_grooms.begin(), m_grooms.end(), [](const Candidate &a, const Candidate &b) {
        return a.getAge() < b.getAge();
    });
    std::sort(m_brides.begin(), m_brides.end(), [](const Candidate &a, const Candidate &b) {
        return a.getAge() < b.getAge();
    });
    updateTableWidgets();
}

void MainWindow::findPairs()
{
    QString result;

    for (int i = 0; i < m_grooms.size(); ++i) {

        if (!m_grooms[i].getIsActive())
            continue;


        for (int j = 0; j < m_brides.size(); ++j) {
            if (!m_brides[j].getIsActive())
                continue;

            if (m_grooms[i].isSuitable(m_brides[j])) {

                m_grooms[i].setIsActive(false);
                m_brides[j].setIsActive(false);

                result += tr("Love Match: %1 (%2 лет) и %3 (%4 лет)\n")
                              .arg(m_grooms[i].getName()).arg(m_grooms[i].getAge())
                              .arg(m_brides[j].getName()).arg(m_brides[j].getAge());

                break;
            }
        }
    }

    if(result.isEmpty())
        result = tr("Совместимых пар не найдено.");

    QMessageBox::information(this, tr("Результат поиска"), result);
}

int MainWindow::generateId()
{
    const int maxId = 100;
    QSet<int> usedIds;

    for (const Candidate &c : m_grooms)
        usedIds.insert(c.getId());
    for (const Candidate &c : m_brides)
        usedIds.insert(c.getId());

    int newId = QRandomGenerator::global()->bounded(1, maxId);
    while(usedIds.contains(newId)) {
        newId = QRandomGenerator::global()->bounded(1, maxId);
    }
    return newId;
}


void MainWindow::addCandidate(const Candidate &candidate)
{
    if (candidate.getGender() == "M")
        m_grooms.append(candidate);
    else if (candidate.getGender() == "F")
        m_brides.append(candidate);
}


void MainWindow::on_pushButtonOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "",
                                                    tr("Text Files (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        if(loadFromFile(fileName))
            QMessageBox::information(this, tr("Успех"), tr("Данные загружены."));
    }
}


void MainWindow::on_pushButtonSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "",
                                                    tr("Text Files (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        if(saveToFile(fileName))
            QMessageBox::information(this, tr("Успех"), tr("Данные сохранены."));
    }
}


void MainWindow::on_pushButtonSortAge_clicked()
{
    sortByAge();
}

void MainWindow::on_pushButtonAddGroom_clicked()
{

    CandidateDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        Candidate newCandidate = dlg.getCandidate();

        newCandidate.setGender("M");


        if(newCandidate.getId() == 0) {
            newCandidate.setId(generateId());
        }

        m_grooms.append(newCandidate);
        updateTableWidgets();
    }
}

void MainWindow::on_pushButtonAddBride_clicked()
{

    CandidateDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        Candidate newCandidate = dlg.getCandidate();
        newCandidate.setGender("F");


        if(newCandidate.getId() == 0) {
            newCandidate.setId(generateId());
        }


        m_brides.append(newCandidate);
        updateTableWidgets();
    }
}


void MainWindow::on_pushButtonEdit_clicked()
{

    int currentRow = ui->tableWidgetGrooms->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Выберите кандидата для редактирования."));
        return;
    }

    Candidate candidateToEdit = m_grooms.at(currentRow);
    CandidateDialog dlg(candidateToEdit, this);
    if (dlg.exec() == QDialog::Accepted) {
        Candidate updatedCandidate = dlg.getCandidate();
        m_grooms[currentRow] = updatedCandidate;
        updateTableWidgets();
    }
}


void MainWindow::on_pushButtonFindPairs_clicked()
{
    findPairs();
}

void MainWindow::on_pushButtonExit_clicked()
{
    close();
}


