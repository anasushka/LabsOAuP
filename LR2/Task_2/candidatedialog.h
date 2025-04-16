#ifndef CANDIDATEDIALOG_H
#define CANDIDATEDIALOG_H

#include <QDialog>
#include "candidate.h"
namespace Ui {
class CandidateDialog;
}

class CandidateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandidateDialog(QWidget *parent = nullptr);
    explicit CandidateDialog(const Candidate &candidate, QWidget *parent = nullptr);

    ~CandidateDialog();


    Candidate getCandidate() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CandidateDialog *ui;
    Candidate m_candidate;
};

#endif // CANDIDATEDIALOG_H
