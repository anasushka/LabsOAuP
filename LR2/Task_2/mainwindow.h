#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "candidate.h"
#include "candidatedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonOpen_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonSortAge_clicked();
    void on_pushButtonAddGroom_clicked();
    void on_pushButtonAddBride_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonFindPairs_clicked();
    void on_pushButtonExit_clicked();


private:
    Ui::MainWindow *ui;

    QVector<Candidate> m_grooms; // Мужчины (gender = "M")
    QVector<Candidate> m_brides; // Женщины (gender = "F")

    // Методы работы с данными:
    bool loadFromFile(const QString &fileName);
    bool saveToFile(const QString &fileName);
    void updateTableWidgets();
    void sortByAge();
    void findPairs();

    // Вспомогательный метод для добавления кандидата в соответствующий список (по полу).
    void addCandidate(const Candidate &candidate);

    int generateId();


};
#endif // MAINWINDOW_H
