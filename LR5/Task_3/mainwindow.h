#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onBtnSizeClicked();
    void onBtnSetClicked();
    void onBtnResetClicked();
    void onBtnFlipClicked();
    void onBtnTestClicked();
    void onBtnAllClicked();
    void onBtnAnyClicked();
    void onBtnNoneClicked();
    void onBtnCountClicked();
    void onBtnToStringClicked();
    void onBtnToULongClicked();
    void onBtnToULLongClicked();

private:
    Ui::MainWindow *ui;

    // Вспомогательная функция, чтобы прочитать size из UI и проверить её
    bool readSize(int &outSize);
    // Вспомогательная функция, чтобы прочитать позицию
    bool readPos(int &outPos);
    QLabel *labelValue;

};
#endif // MAINWINDOW_H
