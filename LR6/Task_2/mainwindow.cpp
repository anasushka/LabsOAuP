#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "inputdialog.h"
#include <fstream>
#include <locale>
#include <vector>
#include  <QKeyEvent>
#include <QLabel>
#include <QTextEdit>
#include <QDoubleValidator>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>
#include <QDialogButtonBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {

    if (watched == m_TextEdit && event->type() == QEvent::KeyPress) {
        auto *ke = static_cast<QKeyEvent*>(event);
        if ((ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
            && !(ke->modifiers() & (Qt::ShiftModifier|Qt::ControlModifier))) {

            m_Dialog->accept();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_case1Button_clicked() {

    QDialog dlg(this);
    dlg.setWindowTitle("Ввод абзаца");
    dlg.setFixedSize(500, 300);

    QVBoxLayout *layout = new QVBoxLayout(&dlg);
    layout->addWidget(new QLabel("Введите текст : ", &dlg));

    QTextEdit *text = new QTextEdit(&dlg);
    text->setAcceptRichText(false);
    text->setWordWrapMode(QTextOption::WordWrap);
    text->setMinimumHeight(200);
    layout->addWidget(text);

    m_Dialog  = &dlg;
    m_TextEdit = text;
    text->installEventFilter(this);

    if (dlg.exec() != QDialog::Accepted) {
        text->removeEventFilter(this);
        m_Dialog = nullptr;
        m_TextEdit = nullptr;
        return;
    }

    QString qtxt = text->toPlainText();

    text->removeEventFilter(this);
    m_Dialog = nullptr;
    m_TextEdit = nullptr;

    //запись wchar
    std::wstring wtext = qtxt.toStdWString();
    std::wofstream fileOf("СушкевичЛаб20.txt");
    fileOf.imbue(std::locale());
    for(wchar_t wc : wtext) fileOf.put(wc);
    fileOf.close();
    //чтение wchar
    std::wstring out;
    std::wifstream fileIf("СушкевичЛаб20.txt");
    fileIf.imbue(std::locale());
    wchar_t wc;
    while(fileIf.get(wc)) out.push_back(wc);
    fileIf.close();

    QMessageBox::information(this, "Текст", QString::fromStdWString(out));

}


void MainWindow::on_case2Button_clicked(){
    bool ok;
    int n =  QInputDialog::getInt(this, "Массив", "Введиет размер массива : ", 1,1,500,1, &ok);

    if(!ok) return;


    QDialog dlg(this);
    dlg.setWindowTitle("Ввод массива");

    int cols = (n + 9) / 10;
    int rows = qMin(n, 10);
    dlg.resize(cols * 120, rows * 30);

    auto *grid = new QGridLayout(&dlg);

    std::vector<QLineEdit*> edits(n);

    for (int i = 0; i < n; ++i) {
        QLabel *lbl = new QLabel(QString::number(i)+":", &dlg);
        edits[i] = new QLineEdit(&dlg);
        edits[i]->setValidator(new QDoubleValidator(this));
        int r = i % 10;
        int c = i / 10;
        grid->addWidget(lbl, r, c*2);
        grid->addWidget(edits[i], r, c*2 + 1);
    }

    auto *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
    grid->addWidget(bb, rows, 0, 1, cols*2);
    connect(bb, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(bb, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() != QDialog::Accepted) return;

    std::vector<float> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = edits[i]->text().toFloat();

    // запись с ')'
    std::ofstream fout("СушкевичЛаб20_0.txt");
    for (float x : arr) fout << x << ')';
    fout.close();

    // чтение
    std::ifstream fin("СушкевичЛаб20_0.txt");
    std::vector<float> out;
    float v;
    while (fin >> v) {
        out.push_back(v);
        if (fin.peek() == ')') fin.get();
    }
    fin.close();

    QStringList parts;
    for (float x : out) parts << QString::number(x);
    QMessageBox::information(this, "Массив из файла", parts.join(" "));
}

void MainWindow::on_case3Button_clicked(){
    InputDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;
    Toy t = dlg.getToy();

    std::ofstream fout("СушкевичЛаб20_1.txt", std::ios::app);
    fout << t.id << ' ' << t.price << ' ' << t.grade << ' '
       << t.inStock << ' ' << t.name << ' ';
    for (int i=0;i<5;++i) fout<<t.ratings[i]<<' ';
    fout<<'\n'; fout.close();

    std::ifstream fin("СушкевичЛаб20_1.txt");
    QStringList rows;
    Toy u;
    while (fin >> u.id >> u.price >> u.grade >> u.inStock >> u.name) {
        for (int i=0;i<5;++i) fin>>u.ratings[i];
        QStringList p;
        p << QString::number(u.id)
          << QString::number(u.price)
          << (u.grade? QString(u.grade): QString("-"))
          << (u.inStock?"Да":"Нет")
          << QString::fromUtf8(u.name);
        for (int i=0;i<5;++i) p << QString::number(u.ratings[i]);
        rows << p.join(" | ");
    }
    fin.close();

    QMessageBox::information(this, "Структуры (текст)", rows.join("\n"));

}
void MainWindow::on_case4Button_clicked(){
    InputDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;
    Toy t = dlg.getToy();

    std::ofstream fout("СушкевичЛаб20_2.bin", std::ios::app|std::ios::binary);
    fout.write(reinterpret_cast<char*>(&t), sizeof(t));
    fout.close();

    std::ifstream fin("СушкевичЛаб20_2.bin", std::ios::binary);
    QStringList rows;
    Toy u;
    while (fin.read(reinterpret_cast<char*>(&u), sizeof(u))) {
        QStringList p;
        p << QString::number(u.id)
          << QString::number(u.price)
          << (u.grade? QString(u.grade): QString("-"))
          << (u.inStock?"Да":"Нет")
          << QString::fromUtf8(u.name);
        for(int i=0;i<5;++i) p << QString::number(u.ratings[i]);
        rows << p.join(" ; ");
    }
    fin.close();

    QMessageBox::information(this, "Структуры (бин)", rows.join("\n"));

}
void MainWindow::on_case5Button_clicked(){
    QDialog dlg(this);
    dlg.setWindowTitle("Ввод предложения");
    dlg.setFixedSize(500, 200);

    auto *layout = new QVBoxLayout(&dlg);

    layout->addWidget(new QLabel("Введите предложение и нажмите Enter:", &dlg));

    QTextEdit *edit = new QTextEdit(&dlg);
    edit->setAcceptRichText(false);
    edit->setWordWrapMode(QTextOption::WordWrap);
    edit->setMinimumHeight(100);
    layout->addWidget(edit);


    m_Dialog   = &dlg;
    m_TextEdit = edit;
    edit->installEventFilter(this);

    if (dlg.exec() != QDialog::Accepted) {
        edit->removeEventFilter(this);
        m_Dialog = nullptr;
        m_TextEdit = nullptr;
        return;
    }

    QString line = edit->toPlainText();

    edit->removeEventFilter(this);
    m_Dialog = nullptr;
    m_TextEdit = nullptr;

    std::ofstream fout("СушкевичЛаб20_3.txt", std::ios::app);
    fout << line.toStdString() << '\n';
    fout.close();

    std::ifstream fin("СушкевичЛаб20_3.txt");
    QStringList rows;
    std::string tmp;
    while (std::getline(fin, tmp))
        rows << QString::fromStdString(tmp);
    fin.close();

    QMessageBox::information(this, "Предложения", rows.join("\n"));
}

void MainWindow::on_exitButton_clicked(){
    close();
}
