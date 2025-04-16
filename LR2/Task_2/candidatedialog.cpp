#include "candidatedialog.h"
#include "ui_candidatedialog.h"
#include "ui_mainwindow.h"

CandidateDialog::CandidateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandidateDialog),   m_candidate(0, "", 0, 0, 0, "", "", 0, 0, 0, 0, 0, 0, "M")
{
    ui->setupUi(this);
}

CandidateDialog::CandidateDialog(const Candidate &candidate, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandidateDialog),
    m_candidate(candidate)
{
    ui->setupUi(this);

    ui->lineEdit->setText(candidate.getName());
    ui->lineEdit_2->setText(QString::number(candidate.getAge()));
    ui->lineEdit_3->setText(QString::number(candidate.getHeight()));
    ui->lineEdit_4->setText(QString::number(candidate.getWeight()));
    ui->lineEdit_5->setText(candidate.getHabits());
    ui->lineEdit_6->setText(candidate.getHobby());
    ui->lineEdit_7->setText(QString::number(candidate.getMinAge()));
    ui->lineEdit_8->setText(QString::number(candidate.getMaxAge()));
    ui->lineEdit_9->setText(QString::number(candidate.getMinHeight()));
    ui->lineEdit_10->setText(QString::number(candidate.getMaxHeight()));
    ui->lineEdit_11->setText(QString::number(candidate.getMinWeight()));
    ui->lineEdit_12->setText(QString::number(candidate.getMaxWeight()));

}

CandidateDialog::~CandidateDialog()
{
    delete ui;
}

Candidate CandidateDialog::getCandidate() const
{
    return m_candidate;
}

void CandidateDialog::on_buttonBox_accepted()
{
    m_candidate.setName( ui->lineEdit->text() );
    m_candidate.setAge( ui->lineEdit_2->text().toInt());
    m_candidate.setHeight( ui->lineEdit_3->text().toInt() );
    m_candidate.setWeight( ui->lineEdit_4->text().toInt() );
    m_candidate.setHabits( ui->lineEdit_5->text() );
    m_candidate.setHobby( ui->lineEdit_6->text() );
    m_candidate.setMinAge( ui->lineEdit_7->text().toInt() );
    m_candidate.setMaxAge( ui->lineEdit_8->text().toInt() );
    m_candidate.setMinHeight( ui->lineEdit_9->text().toInt());
    m_candidate.setMaxHeight( ui->lineEdit_10->text().toInt() );
    m_candidate.setMinWeight( ui->lineEdit_11->text().toInt() );
    m_candidate.setMaxWeight( ui->lineEdit_12->text().toInt() );

    accept();
}
