#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mystringlib.h"
#include <vector>
#include <cstring>  // для memcpy, если используете в memmove-demo
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnMemcpy,   &QPushButton::clicked, this, &MainWindow::onBtnMemcpyClicked);
    connect(ui->btnStrcpy,   &QPushButton::clicked, this, &MainWindow::onBtnStrcpyClicked);
    connect(ui->btnStrncpy,  &QPushButton::clicked, this, &MainWindow::onBtnStrncpyClicked);
    connect(ui->btnMemmove,  &QPushButton::clicked, this, &MainWindow::onBtnMemmoveClicked);
    connect(ui->btnPushBack, &QPushButton::clicked, this, &MainWindow::onBtnPushBackClicked);
    connect(ui->btnStrcmp,   &QPushButton::clicked, this, &MainWindow::onBtnStrcmpClicked);
    connect(ui->btnStrncmp,  &QPushButton::clicked, this, &MainWindow::onBtnStrncmpClicked);
    connect(ui->btnStrchr,   &QPushButton::clicked, this, &MainWindow::onBtnStrchrClicked);
    connect(ui->btnStrlen,   &QPushButton::clicked, this, &MainWindow::onBtnStrlenClicked);  // ← подключили

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnMemcpyClicked()
{
    auto s1 = ui->lineEdit1->text().toUtf8();
    auto s2 = ui->lineEdit2->text().toUtf8();
    int n = ui->lineEditN->text().toInt();

    std::vector<char> buf(s1.size() + n + 1, '\0');
    String::memcpy(buf.data(),          s1.constData(), s1.size());
    String::memcpy(buf.data() + s1.size(),
                   s2.constData(), n);
    buf[s1.size()+n] = '\0';

    QMessageBox::information(this, "memcpy",
                             QString("Берёт первые N байт (символов) из 2 и копируем их сразу после всей строки из 1 : \"%1\"")
                                 .arg(QString::fromUtf8(buf.data()))
                             );
}

void MainWindow::onBtnStrcpyClicked()
{
    String dest;
    String src(ui->lineEdit1->text().toUtf8().constData());
    String::strcpy(dest, src);

    QMessageBox::information(this, "strcpy",
                             QString("Копирует всю строку из 1 во внутреннюю переменную и получаем полную копию : \"%1\"")
                                 .arg(QString::fromUtf8(dest.c_str()))
                             );
}

void MainWindow::onBtnStrncpyClicked()
{
    String dest;
    String src(ui->lineEdit1->text().toUtf8().constData());
    int n = ui->lineEditN->text().toInt();
    String::strncpy(dest, src, n);

    QMessageBox::information(this, "strncpy",
                             QString("Копирует не более %1 символов из первого поля: \"%2\"")
                                 .arg(n)
                                 .arg(QString::fromUtf8(dest.c_str()))
                             );
}

void MainWindow::onBtnMemmoveClicked()
{
    auto txt = ui->lineEdit1->text().toUtf8();
    int n = ui->lineEditN->text().toInt();

    std::vector<char> buf(txt.size() + 1, '\0');
    memcpy(buf.data(), txt.constData(), txt.size()+1);

    String::memmove(buf.data()+2, buf.data(), n);

    QMessageBox::information(this, "memmove",
                             QString("Безопасно копирует %1 байт внутри буфера (с учётом перекрытия): \"%2\"")
                                 .arg(n)
                                 .arg(QString::fromUtf8(buf.data()))
                             );
}

void MainWindow::onBtnPushBackClicked()
{
    QString t = ui->lineEdit1->text();
    if (t.isEmpty()) {
        QMessageBox::warning(this, "push_back", "Введите сначала строку");
        return;
    }
    QChar ch = ui->lineEditChar->text().isEmpty()
                   ? QChar('?')
                   : ui->lineEditChar->text().at(0);

    String str(t.toUtf8().constData());
    str.push_back(ch.toLatin1());

    QMessageBox::information(this, "push_back",
                             QString("Добавляет символ '%1' в конец: \"%2\"")
                                 .arg(ch)
                                 .arg(QString::fromUtf8(str.c_str()))
                             );
}

void MainWindow::onBtnStrcmpClicked()
{
    String s1(ui->lineEdit1->text().toUtf8().constData());
    String s2(ui->lineEdit2->text().toUtf8().constData());
    int r = String::strcmp(s1, s2);

    QMessageBox::information(this, "strcmp",
                             QString("Сравнивает две строки полностью. strcmp(\"%1\",\"%2\") = %3, \n 0 - значит одинаковые, отрицатльное если 1 < 2, положительное если 1 > 2")
                                 .arg(ui->lineEdit1->text())
                                 .arg(ui->lineEdit2->text())
                                 .arg(r)
                             );
}

void MainWindow::onBtnStrncmpClicked()
{
    String s1(ui->lineEdit1->text().toUtf8().constData());
    String s2(ui->lineEdit2->text().toUtf8().constData());
    int n = ui->lineEditN->text().toInt();
    int r = String::strncmp(s1, s2, n);

    QMessageBox::information(this, "strncmp",
                             QString("Сравнимаем N символов. strncmp(%1,\"%2\",\"%3\") = %4")
                                 .arg(n)
                                 .arg(ui->lineEdit1->text())
                                 .arg(ui->lineEdit2->text())
                                 .arg(r)
                             );
}

void MainWindow::onBtnStrchrClicked()
{
    String str(ui->lineEdit1->text().toUtf8().constData());
    if (ui->lineEditChar->text().isEmpty()) {
        QMessageBox::warning(this, "strchr", "Введите символ в поле 'Char'");
        return;
    }
    char c = ui->lineEditChar->text().at(0).toLatin1();
    char *p = String::strchr(str, int(c));

    if (p) {
        int idx = int(p - str.c_str());
        QMessageBox::information(this, "strchr",
                                 QString("Поиск символа. strchr('%1') found at index %2")
                                     .arg(QChar(c)).arg(idx)
                                 );
    } else {
        QMessageBox::information(this, "strchr",
                                 QString("strchr('%1') not found").arg(QChar(c))
                                 );
    }
}



void MainWindow::onBtnStrlenClicked()
{
    // прочитаем из первого поля
    QString t = ui->lineEdit1->text();
    String s(t.toUtf8().constData());
    size_t len = String::strlen(s);

    QMessageBox::information(this, "strlen",
                             QString("Длина строки. strlen(\"%1\") = %2")
                                 .arg(t)
                                 .arg((qulonglong)len)
                             );
}
