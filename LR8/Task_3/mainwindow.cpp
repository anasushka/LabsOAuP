#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QSplitter>
#include <QString>
#include <sstream>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    bstMap(), bstSet(),
    hashTable(8, 0.75f)
{
    // Простой размер окна
    resize(800, 600);
    setWindowTitle("Демонстрация BST и Hash Table");

    // Создаем вкладки
    QTabWidget *tabWidget = new QTabWidget(this);
    QWidget *tabBST = new QWidget();
    QWidget *tabHash = new QWidget();
    tabWidget->addTab(tabBST, "BST (Map/Set)");
    tabWidget->addTab(tabHash, "Hash Table");
    setCentralWidget(tabWidget);

    setupBSTTab(tabBST);
    setupHashTab(tabHash);
}

void MainWindow::setupBSTTab(QWidget *parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // Выбор типа BST
    QHBoxLayout *typeLayout = new QHBoxLayout();
    typeLayout->addWidget(new QLabel("Тип BST:"));
    comboTreeType = new QComboBox();
    comboTreeType->addItem("Map (ключ-значение)");
    comboTreeType->addItem("Set (только ключи)");
    typeLayout->addWidget(comboTreeType);
    typeLayout->addStretch();
    mainLayout->addLayout(typeLayout);

    // Ввод данных
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(new QLabel("Ключ:"));
    lineEditKey = new QLineEdit();
    lineEditKey->setPlaceholderText("Введите число");
    inputLayout->addWidget(lineEditKey);

    inputLayout->addWidget(new QLabel("Значение:"));
    lineEditValue = new QLineEdit();
    lineEditValue->setPlaceholderText("Введите строку");
    inputLayout->addWidget(lineEditValue);

    btnBstInsert = new QPushButton("Вставить");
    inputLayout->addWidget(btnBstInsert);

    btnBstCheck = new QPushButton("Проверить");
    inputLayout->addWidget(btnBstCheck);

    mainLayout->addLayout(inputLayout);

    // Кнопки управления
    QHBoxLayout *controlLayout = new QHBoxLayout();
    btnBstUpdateIterator = new QPushButton("Обновить итераторы");
    controlLayout->addWidget(btnBstUpdateIterator);
    controlLayout->addStretch();
    mainLayout->addLayout(controlLayout);

    // Разделитель для вывода
    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    // Левая часть - обход итератором
    QWidget *leftWidget = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(new QLabel("Обход итератором (по порядку):"));
    textBstOutput = new QTextEdit();
    textBstOutput->setMaximumHeight(200);
    leftLayout->addWidget(textBstOutput);

    // Правая часть - структура дерева
    QWidget *rightWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->addWidget(new QLabel("Структура дерева:"));
    textBstTree = new QTextEdit();
    textBstTree->setMaximumHeight(200);
    rightLayout->addWidget(textBstTree);

    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setSizes({400, 400});
    mainLayout->addWidget(splitter);

    // Информация о дереве
    bstInfoLabel = new QLabel("Дерево пусто");
    mainLayout->addWidget(bstInfoLabel);

    // Подключение сигналов
    connect(btnBstInsert, &QPushButton::clicked, this, &MainWindow::bstInsert);
    connect(btnBstCheck, &QPushButton::clicked, this, &MainWindow::bstCheck);
    connect(btnBstUpdateIterator, &QPushButton::clicked, this, &MainWindow::bstUpdateIterators);
    connect(comboTreeType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onTreeTypeChanged);

    onTreeTypeChanged(0);
}

void MainWindow::setupHashTab(QWidget *parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // Ввод данных
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(new QLabel("Ключ:"));
    lineEditHashKey = new QLineEdit();
    lineEditHashKey->setPlaceholderText("Введите число");
    inputLayout->addWidget(lineEditHashKey);

    inputLayout->addWidget(new QLabel("Значение:"));
    lineEditHashValue = new QLineEdit();
    lineEditHashValue->setPlaceholderText("Введите строку");
    inputLayout->addWidget(lineEditHashValue);

    mainLayout->addLayout(inputLayout);

    // Кнопки операций
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    btnHashInsert = new QPushButton("Вставить");
    btnHashContains = new QPushButton("Найти");
    btnHashErase = new QPushButton("Удалить");
    btnHashClear = new QPushButton("Очистить");
    btnHashRehash = new QPushButton("Увеличить таблицу");

    buttonLayout->addWidget(btnHashInsert);
    buttonLayout->addWidget(btnHashContains);
    buttonLayout->addWidget(btnHashErase);
    buttonLayout->addWidget(btnHashClear);
    buttonLayout->addWidget(btnHashRehash);
    mainLayout->addLayout(buttonLayout);

    // Информация о таблице
    hashInfoLabel = new QLabel();
    mainLayout->addWidget(hashInfoLabel);

    // Вывод состояния таблицы
    mainLayout->addWidget(new QLabel("Содержимое хеш-таблицы:"));
    textHashDisplay = new QTextEdit();
    mainLayout->addWidget(textHashDisplay);

    // Подключение сигналов
    connect(btnHashInsert, &QPushButton::clicked, this, &MainWindow::hashInsert);
    connect(btnHashErase, &QPushButton::clicked, this, &MainWindow::hashErase);
    connect(btnHashContains, &QPushButton::clicked, this, &MainWindow::hashContains);
    connect(btnHashClear, &QPushButton::clicked, this, &MainWindow::hashClear);
    connect(btnHashRehash, &QPushButton::clicked, this, &MainWindow::hashRehash);

    updateHashDisplay();
}

void MainWindow::onTreeTypeChanged(int index) {
    bool isMap = (index == 0);
    lineEditValue->setEnabled(isMap);
    if (!isMap) {
        lineEditValue->clear();
        lineEditValue->setPlaceholderText("(не используется для Set)");
    } else {
        lineEditValue->setPlaceholderText("Введите строку");
    }
    updateBstOutputs();
}

void MainWindow::bstInsert() {
    bool ok;
    int key = lineEditKey->text().toInt(&ok);
    if (!ok || lineEditKey->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный числовой ключ.");
        return;
    }

    if (comboTreeType->currentIndex() == 0) { // Map
        QString value = lineEditValue->text();
        if (value.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите значение для Map.");
            return;
        }
        bstMap.insert(key, value);
    } else { // Set
        bstSet.insert(key);
    }

    lineEditKey->clear();
    lineEditValue->clear();
    updateBstOutputs();
}

void MainWindow::bstCheck() {
    bool ok;
    int key = lineEditKey->text().toInt(&ok);
    if (!ok || lineEditKey->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный числовой ключ для проверки.");
        return;
    }

    bool found;
    QString message;

    if (comboTreeType->currentIndex() == 0) { // Map
        found = bstMap.contains(key);
        if (found) {
            QString value = bstMap[key];
            message = QString("Ключ %1 найден, значение: %2").arg(key).arg(value);
        } else {
            message = QString("Ключ %1 не найден").arg(key);
        }
    } else { // Set
        found = bstSet.contains(key);
        message = found ? QString("Ключ %1 найден").arg(key) : QString("Ключ %1 не найден").arg(key);
    }

    QMessageBox::information(this, "Результат поиска", message);
}

void MainWindow::bstUpdateIterators() {
    updateBstOutputs();
    QMessageBox::information(this, "Обновление", "Итераторы обновлены");
}

void MainWindow::updateBstOutputs() {
    QString inorderStr;
    QString treeStr;
    QString infoStr;

    if (comboTreeType->currentIndex() == 0) { // Map
        // Обход итератором
        for (auto it = bstMap.begin(); it != bstMap.end(); ++it) {
            inorderStr += QString("[%1:%2] ").arg(it->first).arg(it->second);
        }
        if (inorderStr.isEmpty()) {
            inorderStr = "Дерево пусто";
        }

        // Структура дерева
        treeStr = buildTreeStringMap(bstMap.getRoot());
        if (treeStr.isEmpty()) {
            treeStr = "Дерево пусто";
        }

        infoStr = "BST Map активен";
    } else { // Set
        // Обход итератором
        for (auto it = bstSet.begin(); it != bstSet.end(); ++it) {
            inorderStr += QString("%1 ").arg(it->first);
        }
        if (inorderStr.isEmpty()) {
            inorderStr = "Дерево пусто";
        }

        // Структура дерева
        treeStr = buildTreeStringSet(bstSet.getRoot());
        if (treeStr.isEmpty()) {
            treeStr = "Дерево пусто";
        }

        infoStr = "BST Set активен";
    }

    textBstOutput->setText(inorderStr);
    textBstTree->setText(treeStr);
    bstInfoLabel->setText(infoStr);
}

QString MainWindow::buildTreeStringMap(BSTNode<int, QString>* node, int indent) {
    if (!node) return "";

    QString result;
    // Сначала правое поддерево (сверху)
    result += buildTreeStringMap(node->right.get(), indent + 4);
    // Текущий узел
    result += QString(" ").repeated(indent) + QString("%1:%2\n").arg(node->data.first).arg(node->data.second);
    // Затем левое поддерево (снизу)
    result += buildTreeStringMap(node->left.get(), indent + 4);

    return result;
}

QString MainWindow::buildTreeStringSet(BSTNode<int, char>* node, int indent) {
    if (!node) return "";

    QString result;
    // Сначала правое поддерево (сверху)
    result += buildTreeStringSet(node->right.get(), indent + 4);
    // Текущий узел
    result += QString(" ").repeated(indent) + QString("%1\n").arg(node->data.first);
    // Затем левое поддерево (снизу)
    result += buildTreeStringSet(node->left.get(), indent + 4);

    return result;
}

void MainWindow::hashInsert() {
    bool ok;
    int key = lineEditHashKey->text().toInt(&ok);
    if (!ok || lineEditHashKey->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный числовой ключ.");
        return;
    }

    QString value = lineEditHashValue->text();
    if (value.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите значение.");
        return;
    }

    hashTable.insert({key, value});
    lineEditHashKey->clear();
    lineEditHashValue->clear();
    updateHashDisplay();
}

void MainWindow::hashErase() {
    bool ok;
    int key = lineEditHashKey->text().toInt(&ok);
    if (!ok || lineEditHashKey->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный ключ для удаления.");
        return;
    }

    bool removed = hashTable.erase(key);
    QString msg = removed ? "Элемент удален" : "Элемент не найден";
    QMessageBox::information(this, "Удаление", msg);
    updateHashDisplay();
}

void MainWindow::hashContains() {
    bool ok;
    int key = lineEditHashKey->text().toInt(&ok);
    if (!ok || lineEditHashKey->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный числовой ключ.");
        return;
    }

    bool exists = hashTable.contains(key);
    QString message;

    if (exists) {
        QString value = hashTable[key];
        message = QString("Ключ %1 найден, значение: %2").arg(key).arg(value);
    } else {
        message = QString("Ключ %1 не найден").arg(key);
    }

    QMessageBox::information(this, "Поиск", message);
}

void MainWindow::hashClear() {
    hashTable.clear();
    updateHashDisplay();
    QMessageBox::information(this, "Очистка", "Хеш-таблица очищена");
}

void MainWindow::hashRehash() {
    size_t oldBuckets = hashTable.bucket_count();
    hashTable.rehash(oldBuckets * 2);
    updateHashDisplay();
    QMessageBox::information(this, "Перестроение",
                             QString("Размер увеличен с %1 до %2 buckets")
                                 .arg(oldBuckets).arg(hashTable.bucket_count()));
}

void MainWindow::updateHashDisplay() {
    // Обновляем информацию
    QString info = QString("Элементов: %1, Buckets: %2, Load Factor: %3")
                       .arg(hashTable.size())
                       .arg(hashTable.bucket_count())
                       .arg(hashTable.load_factor(), 0, 'f', 2);
    hashInfoLabel->setText(info);

    // Обновляем содержимое
    std::string debugStr = hashTable.debugString();
    textHashDisplay->setText(QString::fromStdString(debugStr));
}
