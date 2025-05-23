#include "mainwindow.h"
#include <QInputDialog>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupTable();
    setupConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QGroupBox *buttonGroup = new QGroupBox("Операции", this);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonGroup);

    // Создаем кнопки
    loadTableBtn = new QPushButton("Загрузить из таблицы", this);
    insertBtn = new QPushButton("Добавить", this);
    removeBtn = new QPushButton("Удалить", this);
    findBtn = new QPushButton("Найти", this);
    balanceBtn = new QPushButton("Балансировать", this);
    clearBtn = new QPushButton("Очистить", this);
    preOrderBtn = new QPushButton("Прямой обход", this);
    inOrderBtn = new QPushButton("Симметричный обход", this);
    postOrderBtn = new QPushButton("Обратный обход", this);
    maxDepthBtn = new QPushButton("Макс. глубина", this);

    // Добавляем кнопки в layout
    buttonLayout->addWidget(loadTableBtn);
    buttonLayout->addWidget(insertBtn);
    buttonLayout->addWidget(removeBtn);
    buttonLayout->addWidget(findBtn);
    buttonLayout->addWidget(balanceBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addWidget(preOrderBtn);
    buttonLayout->addWidget(inOrderBtn);
    buttonLayout->addWidget(postOrderBtn);
    buttonLayout->addWidget(maxDepthBtn);
    buttonLayout->addStretch();

    // Таблица (StringGrid)
    tableWidget = new QTableWidget(this);
    tableWidget->setMinimumWidth(300);

    // Правая панель (дерево + вывод)
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    // Дерево для визуализации
    treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderLabel("AVL Дерево");
    treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    treeWidget->setMinimumHeight(400);

    rightLayout->addWidget(treeWidget);


    // Добавляем все в главный layout
    mainLayout->addWidget(buttonGroup, 1);
    mainLayout->addWidget(tableWidget, 2);
    mainLayout->addWidget(rightPanel, 3);

    setWindowTitle("AVL Tree Visualizer");
    resize(1200, 800);
}

void MainWindow::setupTable()
{
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Номер паспорта", "Ф.И.О."});
    tableWidget->setRowCount(5);

    // Заполняем тестовыми данными
    for (int i = 0; i < 5; ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(1000 + i)));
        tableWidget->setItem(i, 1, new QTableWidgetItem("Человек " + QString::number(i + 1)));
    }
}

void MainWindow::setupConnections()
{
    connect(loadTableBtn, &QPushButton::clicked, this, &MainWindow::onLoadFromTableClicked);
    connect(insertBtn, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    connect(removeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(findBtn, &QPushButton::clicked, this, &MainWindow::onFindClicked);
    connect(balanceBtn, &QPushButton::clicked, this, &MainWindow::onBalanceClicked);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(preOrderBtn, &QPushButton::clicked, this, &MainWindow::onPreOrderClicked);
    connect(inOrderBtn, &QPushButton::clicked, this, &MainWindow::onInOrderClicked);
    connect(postOrderBtn, &QPushButton::clicked, this, &MainWindow::onPostOrderClicked);
    connect(maxDepthBtn, &QPushButton::clicked, this, &MainWindow::onMaxDepthClicked);
}

void MainWindow::onLoadFromTableClicked()
{
    avlTree.loadFromTable(tableWidget);
    avlTree.displayInTreeWidget(treeWidget);
   QMessageBox::information(this, "Загрузка","Данные загружены из таблицы в AVL дерево");
}

void MainWindow::onInsertClicked()
{
    bool ok;
    int passport = QInputDialog::getInt(this, "Добавление", "Введите номер паспорта:", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QString name = QInputDialog::getText(this, "Добавление", "Введите Ф.И.О.:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    avlTree.insert(passport, name);
    avlTree.displayInTreeWidget(treeWidget);
    QMessageBox::information(this, "Добавление",(QString("Добавлен: %1 - %2").arg(passport).arg(name)));
}

void MainWindow::onRemoveClicked()
{
    bool ok;
    int passport = QInputDialog::getInt(this, "Удаление", "Введите номер паспорта для удаления:", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    if (avlTree.find(passport).isEmpty()) {
        outputText->append(QString("Паспорт %1 не найден").arg(passport));
        return;
    }

    avlTree.remove(passport);
    avlTree.displayInTreeWidget(treeWidget);
    QMessageBox::information(this, "Удаление",QString("Удален паспорт: %1").arg(passport));
}

void MainWindow::onFindClicked()
{
    bool ok;
    int passport = QInputDialog::getInt(this, "Поиск", "Введите номер паспорта:", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QString name = avlTree.find(passport);
    if (name.isEmpty()) {
        QMessageBox::information(this, "Поиск",QString("Паспорт %1 не найден").arg(passport));
    } else {
        QMessageBox::information(this, "Поиск",QString("Найден: %1 - %2").arg(passport).arg(name));
    }
}

void MainWindow::onBalanceClicked()
{
    int oldDepth = avlTree.maxDepth();
    avlTree.balance();
    avlTree.displayInTreeWidget(treeWidget);

    AVL::Node* root = avlTree.getRoot();
    QMessageBox::information(this, "Балансирование",
        QString("Балансировка выполнена:\nКорень: %1\nГлубина была: %2, стала: %3")
            .arg(root ? QString::number(root->passportNumber) : "нет")
            .arg(oldDepth)
            .arg(avlTree.maxDepth())
        );
}

void MainWindow::onClearClicked()
{
    avlTree.clear();
    treeWidget->clear();
    QMessageBox::information(this, "Очистка","Дерево очищено");
}

void MainWindow::onPreOrderClicked()
{
       QMessageBox::information(this, "Прямой обход (pre-order):",avlTree.preOrderTraversal());
}

void MainWindow::onInOrderClicked()
{
    QMessageBox::information(this, "Прямой обход (pre-order):",avlTree.inOrderTraversal());
}

void MainWindow::onPostOrderClicked()
{
   QMessageBox::information(this, "Обратный обход (post-order):",avlTree.postOrderTraversal());
}

void MainWindow::onMaxDepthClicked()
{
    QMessageBox::information(this, "Глубина",QString("Максимальная глубина дерева: %1").arg(avlTree.maxDepth()));
}
