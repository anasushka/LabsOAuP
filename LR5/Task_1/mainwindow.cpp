#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QKeyEvent>
#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentPosition(0)
    , errorCount(0)
    , wordCount(0)
    , currentLanguage("Русский")
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    setWindowTitle("Тренажер");

    auto *mainLayout = new QVBoxLayout(central);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    startButton    = new QPushButton("Начать");
    fileButton     = new QPushButton("Выбрать файл");
    languageButton = new QPushButton("Язык");
    finishButton   = new QPushButton("Завершить");
    resetButton    = new QPushButton("Сбросить");
    for (auto *btn : {startButton, fileButton, languageButton, finishButton, resetButton}) {
        btn->setFocusPolicy(Qt::NoFocus);
        btn->setAutoDefault(false);
        btn->setDefault(false);
        btnLayout->addWidget(btn);
    }
    mainLayout->addLayout(btnLayout);

    textDisplay = new QTextEdit;
    textDisplay->setReadOnly(true);
    textDisplay->setFocusPolicy(Qt::NoFocus);
    mainLayout->addWidget(textDisplay);


    timerLabel    = new QLabel("Время: 00:00");
    wpmLabel      = new QLabel("Скорость: 0 WPM");
    accuracyLabel = new QLabel("Точность: 100%");


    wpmInfoLabel = new QLabel("WPM - Words Per Minute (Количество слов в минуту)");
    wpmInfoLabel->setStyleSheet("color: gray; font-style: italic;");
    wpmInfoLabel->setAlignment(Qt::AlignCenter);

    QGridLayout *stats = new QGridLayout;
    // первая строка: время, скорость, точность
    stats->addWidget(timerLabel,    0, 0);
    stats->setAlignment(timerLabel,    Qt::AlignCenter);
    stats->addWidget(wpmLabel,      0, 1);
    stats->setAlignment(wpmLabel,      Qt::AlignCenter);
    stats->addWidget(accuracyLabel, 0, 2);
    stats->setAlignment(accuracyLabel, Qt::AlignCenter);
    // вторая строка: подпись WPM под скоростью
    stats->addWidget(wpmInfoLabel,  1, 1);
    stats->setAlignment(wpmInfoLabel, Qt::AlignCenter);
    stats->setVerticalSpacing(4);
    // добавляем layout статистики
    mainLayout->addLayout(stats);

    keyboardWidget = new QWidget;
    mainLayout->addWidget(keyboardWidget);
    createKeyboardLayout(currentLanguage);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startTest);
    connect(fileButton,  &QPushButton::clicked, this, &MainWindow::openTextFile);
    connect(languageButton, &QPushButton::clicked, [this](){
        QStringList langs = {"Русский", "Английский","Немецкий", "Французский", "Арабский", "Китайский", "Белорусский", "Иврит"};
        bool ok = false;
        QString lang = QInputDialog::getItem(this, "Выбор языка", "Язык:", langs, langs.indexOf(currentLanguage), false, &ok);
        if (ok && !lang.isEmpty()) {
            currentLanguage = lang;
            createKeyboardLayout(lang);
        }
    });
    connect(finishButton, &QPushButton::clicked, this, &MainWindow::stopTraining);
    connect(resetButton,  &QPushButton::clicked, this, &MainWindow::resetTest);

    qApp->installEventFilter(this); // Фильтр событий для обработки ввода с физической клавиатуры
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        auto *ke = static_cast<QKeyEvent*>(event);
        QString key = ke->text();
        if (!key.isEmpty() && !ke->isAutoRepeat()) {
            QString displayKey = (ke->key() == Qt::Key_Space) ? " " : key.toUpper();
            highlightVirtualKey(displayKey); // Подсвечиваем нажатую клавишу на виртуальной клавиатуре
            processKey(key); // Обработка ввода
        }
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::createKeyboardLayout(const QString &lang) {
    if (auto *old = keyboardWidget->layout()) {
        QLayoutItem *it;
        while ((it = old->takeAt(0))) {
            delete it->widget();
            delete it;
        }
        delete old;
    }
    keyMap.clear();
    auto *grid = new QGridLayout(keyboardWidget);

    QStringList rows;
    if (lang == "Русский") {
        rows = QStringList{
             "Ё1234567890-", "ЙЦУКЕНГШЩЗХЪ", "ФЫВАПРОЛДЖЭ.", "ЯЧСМИТЬБЮ!?,"};
    } else if (lang == "Английский") {
        rows = QStringList{
             "`1234567890", "QWERTYUIOP-", "ASDFGHJKL?!", "ZXCVBNM,./:"};
    } else if (lang == "Немецкий") {
        rows =  QStringList{
                           "1234567890!`", "ßqwertzuiop?", "üasdfghjklö:","äyxcvbnm,.-"};
    } else if (lang == "Французский") {
        rows = QStringList{
            "azertyui`","opqsdfghj", "klmùwxcvb", "néàè,!?.:"
        };
    } else if (lang == "Арабский") {
        rows = QStringList{
            "ضصثقفغعهخ" ,"حجدپچژکگگف",  "ڵمنوپتسع",  "طذضصث!?.-:"
        };
    }else if(lang == "Китайский"){
    rows = QStringList{
            "你我他她它", "是了在上吗","好不行大吗","中天国学你"};
    }
    else if (lang == "Белорусский") {
        rows = QStringList{
             "Ё1234567890-" , "ЙЦУКЕНГШЎЗХЪ" , "ФІВАПРОЛДЖЄ!" , "ЯЧСМІТЬБЮ.,?"};
    } else if (lang == "Иврит") {
        rows = QStringList{
             "1234567890","קראטוןםפ!-" , "שדגכעיכל;'", "זסבהנמצ,.?"};
    }


    for (int i = 0; i < rows.size(); ++i) {
        const QString &row = rows[i];
        for (int j = 0; j < row.size(); ++j) {
            QString ch = row.mid(j,1);
            QPushButton *btn = new QPushButton(ch);
            btn->setStyleSheet("font-size:18px;");
            btn->setFocusPolicy(Qt::NoFocus);
            connect(btn, &QPushButton::clicked, this, [this, ch]() { processKey(ch); });
            grid->addWidget(btn, i, j);
            keyMap[ch.toUpper()] = btn;
        }
    }
    QPushButton *spaceBtn = new QPushButton("————");
    spaceBtn->setStyleSheet("min-width:300px;font-size:18px;");
    spaceBtn->setFocusPolicy(Qt::NoFocus);
    connect(spaceBtn, &QPushButton::clicked, this, [this]() { processKey(" "); });
    grid->addWidget(spaceBtn, rows.size(), 0, 1, grid->columnCount());
    keyMap[" "] = spaceBtn;
}

void MainWindow::highlightVirtualKey(const QString &key) {
    if (keyMap.contains(key)) {
        auto *btn = keyMap[key];

        QColor pressedColor = btn->palette().color(QPalette::Highlight);

        btn->setStyleSheet(QString("background-color:%1; font-size:18px;")
                               .arg(pressedColor.name()));
        QTimer::singleShot(200, [btn]() {
            btn->setStyleSheet("font-size:18px;");
        });
    }
}

void MainWindow::startTest() {
    currentPosition = 0;
    errorCount = 0;
    wordCount = 0;
    timeElapsed = QTime(0,0,0);
    timer->start(1000);
}

void MainWindow::openTextFile() {
    QString fn = QFileDialog::getOpenFileName(this, "Выбрать текст", {}, "*.txt");
    if (fn.isEmpty()) return;
    QFile f(fn);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    expectedText = QString::fromUtf8(f.readAll()).trimmed();
    textDisplay->setPlainText(expectedText);
    currentPosition = 0;
}

void MainWindow::updateTimer() {
    timeElapsed = timeElapsed.addSecs(1);
    timerLabel->setText("Время: " + timeElapsed.toString("mm:ss"));
    updateStatistics();
}

void MainWindow::processKey(const QString &key) {
    if (!timer->isActive() || currentPosition >= expectedText.length()) return;
    QString exp = expectedText.mid(currentPosition,1);
    bool correct = (QString::compare(key, exp, Qt::CaseInsensitive) == 0);
    highlightText(currentPosition, correct);
    if (correct) {
        currentPosition++;
        if (key == " ") wordCount++;
    } else {
        errorCount++;
    }
    updateStatistics();
}

void MainWindow::highlightText(int pos, bool correct) {
    QTextCursor c(textDisplay->document());
    c.setPosition(pos);
    c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
    QTextCharFormat fmt;
    fmt.setForeground(correct ? Qt::green : Qt::red);
    c.setCharFormat(fmt);
}

void MainWindow::updateStatistics() {
    double secs = timeElapsed.minute()*60 + timeElapsed.second();
    double mins = secs / 60.0;
    double wpm = (mins > 0) ? wordCount / mins : 0;
    double acc = (currentPosition > 0) ? (currentPosition - errorCount) * 100.0 / currentPosition : 100;
    wpmLabel->setText(QString("Скорость: %1 WPM").arg(wpm,0,'f',1));
    accuracyLabel->setText(QString("Точность: %1%").arg(acc,0,'f',1));
}

void MainWindow::stopTraining() {
    timer->stop();
    QMessageBox::information(this, "Результаты",
                             QString("Время: %1\nСкорость: %2 WPM\nТочность: %3%\nСлов: %4")
                                 .arg(timeElapsed.toString("mm:ss"))
                                 .arg(wpmLabel->text().split(' ').last())
                                 .arg(accuracyLabel->text().split('%').first())
                                 .arg(wordCount)
                             );
}

void MainWindow::resetTest() {
    timer->stop();
    currentPosition = errorCount = wordCount = 0;
    timeElapsed = QTime(0,0,0);
    textDisplay->clear();
    if (!expectedText.isEmpty()) textDisplay->setPlainText(expectedText);
    updateStatistics();
}
