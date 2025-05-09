#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_case1Button_clicked();
    void on_case2Button_clicked();
    void on_case3Button_clicked();
    void on_case4Button_clicked();
    void on_case5Button_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    QDialog   *m_Dialog   = nullptr;
    QTextEdit *m_TextEdit  = nullptr;
};
#endif // MAINWINDOW_H
