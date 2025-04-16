#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "folderfilescount.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->chooseFolderButton, &QPushButton::clicked, this, &MainWindow::onChooseFolderClicked);
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::onOpenFileClicked);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->directoryLabel->setAlignment(Qt::AlignCenter);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onChooseFolderClicked()
{

    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), QDir::homePath());
    if (dirPath.isEmpty()) {
        ui->directoryLabel->setText(tr("Directory not chosen"));
        ui->resultDir->setText(tr("-1"));
         ui->resultFiles->setText(tr("-1"));
        return;
    }


    ui->directoryLabel->setText(dirPath);


    int folders = 0, files = 0;

    FolderFilesCount::count(dirPath, folders, files);

    // Выводим результаты на экран.
    ui->resultDir->setText(tr(" %1 ").arg(folders));
    ui->resultFiles->setText(tr("%1 ").arg(files));
}

void MainWindow::onOpenFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Choose File"), QDir::homePath());
    if (filePath.isEmpty())
        return;


    bool success = QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    if (!success)
        QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
}
