#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_keyboardButton_clicked(){
    auto *dlg = new InputDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::on_pushButton_clicked(){
    Toy t = {1,69.99, 'A', true, "Игрушка котик", {4.5, 5.0, 5.0,4.8,4.99}};

    QString result;
    result+= QString::number(t.id) + " | ";
    result+= QString::number(t.price) + " | ";
    QString gradePart = (t.grade == '\0')
                            ? QString("-")
                            : QString(QChar(t.grade));
    result += gradePart + " | ";
    result+= (t.inStock ? "Да  | "  : "Нет | ");
    result+= QString::fromUtf8(t.name) + " | ";
    for (int i=0; i <5; ++i){
        result += QString::number(t.ratings[i])+ " | ";
    }

    QMessageBox::information(this, tr("Созданная структура"), result);

}


void MainWindow::on_pushButton_2_clicked(){
    Toy t;
    t.id=2;
    t.price=9.99;
    t.grade='B';
    t.inStock= true;
    std::strcpy(t.name, "Лапка");
    double temp[]={4.5, 5.0, 5.0,4.8,4.99};
    for( int i=0; i< 5; i++){
        t.ratings[i]=temp[i];
    }

    QString result;
    result+= QString::number(t.id) + " | ";
    result+= QString::number(t.price) + " | ";
    QString gradePart = (t.grade == '\0')
                            ? QString("-")
                            : QString(QChar(t.grade));
    result += gradePart + " | ";

result+= (t.inStock ? "Да  | "  : "Нет | ");
    result+= QString::fromUtf8(t.name) + " | ";
    for (int i=0; i <5; ++i){
        result += QString::number(t.ratings[i])+ " | ";
    }

    QMessageBox::information(this, tr("Созданная структура"), result);

}

void MainWindow::on_pushButton_3_clicked(){
    Toy t;
    Toy* p=&t;

    p->id=3;
    p->price=12.99;
    p->grade='C';
    p->inStock= true;
    std::strcpy(t.name, "Указка с пальцем");
    double temp[]={4.5, 5.0, 5.0,4.8,4.99};
    for( int i=0; i< 5; i++){
        p->ratings[i]=temp[i];
    }

    QString result;
    result+= QString::number(p->id) + " | ";
    result+= QString::number(p->price) + " | ";
    QString gradePart = (p->grade == '\0')
                            ? QString("-")
                            : QString(QChar(p->grade));
    result += gradePart + " | ";

    result+= (p->inStock ? "Да  | "  : "Нет | ");
    result+= QString::fromUtf8(p->name) + " | ";
    for (int i=0; i <5; ++i){
        result += QString::number(p->ratings[i])+ " | ";
    }

    QMessageBox::information(this, tr("Созданная структура"), result);

}

void MainWindow::on_pushButton_4_clicked(){

    Toy t;
    Toy& tt=t;

    tt.id=4;
    tt.price=8.49;
    tt.grade='D';
    tt.inStock= true;
    std::strcpy(tt.name, "Машинка");
    double temp[]={4.5, 5.0, 5.0,4.8,4.99};
    for( int i=0; i< 5; i++){
        tt.ratings[i]=temp[i];
    }

    QString result;
    result+= QString::number(tt.id) + " | ";
    result+= QString::number(tt.price) + " | ";
    QString gradePart = (tt.grade == '\0')
                            ? QString("-")
                            : QString(QChar(tt.grade));
    result += gradePart + " | ";

    result+= (tt.inStock ? "Да  | "  : "Нет | ");
    result+= QString::fromUtf8(tt.name) + " | ";
    for (int i=0; i <5; ++i){
        result += QString::number(tt.ratings[i])+ " | ";
    }

    QMessageBox::information(this, tr("Созданная структура"), result);


}



