#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector>
#include <QMainWindow>
#include "date.h"

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

    void on_openFileButton_clicked();

    // Кнопки справа:
    void on_nextDayButton_clicked();
    void on_prevDayButton_clicked();
    void on_isLeapButton_clicked();
    void on_weekNumberButton_clicked();
    void on_birthdayButton_clicked();
    void on_durationButton_clicked();
    void on_addDateButton_clicked();
    void on_editDateButton_clicked();


private:
    Ui::MainWindow *ui;
    std::vector<Date> dates;

    QString currentFileName;

    void readDatesFromFile(const QString &fileName);
    void displayDates();

    Date parseDateFromString(const QString &str) const;
    QString dateToString(const Date &d) const;
};
#endif // MAINWINDOW_H
