// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QMap>

class QPushButton;
class QTextEdit;
class QLabel;
class QTimer;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void startTest();
    void openTextFile();
    void updateTimer();
    void stopTraining();
    void resetTest();

private:
    void processKey(const QString &key);
    void createKeyboardLayout(const QString &lang);
    void highlightText(int pos, bool correct);
    void updateStatistics();
    void highlightVirtualKey(const QString &key);

    QTextEdit *textDisplay;
    QWidget *keyboardWidget;
    QPushButton *startButton;
    QPushButton *fileButton;
    QPushButton *languageButton;
    QPushButton *finishButton;
    QPushButton *resetButton;
    QLabel *timerLabel;
    QLabel *wpmLabel;
    QLabel *accuracyLabel;
    QLabel *wpmInfoLabel;
    QTimer *timer;

    QString expectedText;
    QTime timeElapsed;
    int currentPosition;
    int errorCount;
    int wordCount;
    QString currentLanguage;
    QMap<QString, QPushButton*> keyMap; // Сопоставление символов с кнопками виртуальной клавиатуры
};

#endif // MAINWINDOW_H
