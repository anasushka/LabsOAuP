#include "inputdialog.h"
#include "ui_inputdialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

InputDialog::~InputDialog()
{
    delete ui;
}

Toy InputDialog::getToy() const{
    Toy t;
    t.id= ui->idEdit ->text().toInt();
    t.price= ui -> priceEdit ->text().toDouble();
    t.grade= ui -> gradeEdit -> text().isEmpty()? '/0' : ui-> gradeEdit->text().at(0).toLatin1();
    t.inStock = ui->inStockEdit->isChecked();

    std::memset(t.name, 0, sizeof(t.name));
    QByteArray ba = ui->nameEdit->text().toUtf8();
    int len = std::min<int>(ba.size(), sizeof(t.name) - 1);
    std::memcpy(t.name, ba.constData(), len);


    QLineEdit* ratingEdits[]={ui->ratingEdits0,ui->ratingEdits1,ui->ratingEdits2,ui->ratingEdits3,ui->ratingEdits4};
    for(int i=0; i<5; ++i)
        t.ratings[i] = ratingEdits[i]->text().toDouble();
    return t;
}

void InputDialog::on_buttonBox_accepted()
{
   accept();
}

void InputDialog::on_buttonBox_rejected(){
    reject();
}


