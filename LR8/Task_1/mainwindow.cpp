#include "mainwindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QStringList>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget;
    setCentralWidget(central);
    setWindowTitle("Бинарное дерево поиска");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *controlLayout = new QVBoxLayout;

    // Дерево
    m_treeWidget = new QTreeWidget;
    m_treeWidget->setHeaderLabel("Дерево");

    // Основные операции
    QLabel *labelNode = new QLabel("Значение:");
    m_editNode = new QLineEdit;

    QPushButton *btnAdd = new QPushButton("Добавить");
    QPushButton *btnRemove = new QPushButton("Удалить");
    QPushButton *btnFind = new QPushButton("Найти");
    QPushButton *btnTraverse = new QPushButton("Обход");

    // Операции с поддеревьями
    QLabel *labelParent = new QLabel("Родитель:");
    m_editParent = new QLineEdit;

    QLabel *labelSubtree = new QLabel("Поддерево (через запятую):");
    m_editSubtree = new QLineEdit;

    QLabel *labelDirection = new QLabel("Направление (л/п):");
    m_editDirection = new QLineEdit;

    QPushButton *btnInsertSubTree = new QPushButton("Вставить поддерево");
    QPushButton *btnRemoveSubTree = new QPushButton("Удалить поддерево");
    QPushButton *btnInsertAtPosition = new QPushButton("Вставить в позицию");

    // НОП
    QLabel *labelLCA1 = new QLabel("Узел 1:");
    m_editLCA1 = new QLineEdit;
    QLabel *labelLCA2 = new QLabel("Узел 2:");
    m_editLCA2 = new QLineEdit;
    QPushButton *btnLCA = new QPushButton("Найти НОП");

    // Очистка
    QPushButton *btnClear = new QPushButton("Очистить");

    // Добавляем элементы
    controlLayout->addWidget(labelNode);
    controlLayout->addWidget(m_editNode);
    controlLayout->addWidget(btnAdd);
    controlLayout->addWidget(btnRemove);
    controlLayout->addWidget(btnFind);
    controlLayout->addWidget(btnTraverse);

    controlLayout->addSpacing(10);

    controlLayout->addWidget(labelParent);
    controlLayout->addWidget(m_editParent);
    controlLayout->addWidget(labelSubtree);
    controlLayout->addWidget(m_editSubtree);
    controlLayout->addWidget(labelDirection);
    controlLayout->addWidget(m_editDirection);
    controlLayout->addWidget(btnInsertSubTree);
    controlLayout->addWidget(btnRemoveSubTree);
    controlLayout->addWidget(btnInsertAtPosition);

    controlLayout->addSpacing(10);

    controlLayout->addWidget(labelLCA1);
    controlLayout->addWidget(m_editLCA1);
    controlLayout->addWidget(labelLCA2);
    controlLayout->addWidget(m_editLCA2);
    controlLayout->addWidget(btnLCA);

    controlLayout->addSpacing(10);
    controlLayout->addWidget(btnClear);
    controlLayout->addStretch();

    mainLayout->addLayout(controlLayout, 1);
    mainLayout->addWidget(m_treeWidget, 2);
    central->setLayout(mainLayout);

    // Подключения
    connect(btnAdd, &QPushButton::clicked, this, [=]() {
        bool ok;
        int val = m_editNode->text().toInt(&ok);
        if (ok) {
            bst.add(val);
            updateTreeDisplay();
            m_editNode->clear();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверное значение.");
        }
    });

    connect(btnRemove, &QPushButton::clicked, this, [=]() {
        bool ok;
        int val = m_editNode->text().toInt(&ok);
        if (ok) {
            if (bst.remove(val)) {
                updateTreeDisplay();
                m_editNode->clear();
            } else {
                QMessageBox::information(this, "Информация", "Узел не найден.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверное значение.");
        }
    });

    connect(btnFind, &QPushButton::clicked, this, [=]() {
        bool ok;
        int val = m_editNode->text().toInt(&ok);
        if (ok) {
            BSTNode *node = bst.find(val);
            if (node)
                QMessageBox::information(this, "Результат", QString("Узел %1 найден.").arg(val));
            else
                QMessageBox::information(this, "Результат", "Узел не найден.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверное значение.");
        }
    });

    connect(btnTraverse, &QPushButton::clicked, this, [=]() {
        QString result;
        bst.traverse([&](int v) {
            result += QString::number(v) + " ";
        });
        if (!result.isEmpty())
            QMessageBox::information(this, "Обход дерева", result);
        else
            QMessageBox::information(this, "Обход дерева", "Дерево пустое");
    });

    connect(btnInsertSubTree, &QPushButton::clicked, this, [=]() {
        bool okParent;
        int parentVal = m_editParent->text().toInt(&okParent);
        QString subtreeText = m_editSubtree->text();
        QString dirText = m_editDirection->text().trimmed().toLower();
        bool leftSide = (dirText == "л");

        if (okParent && !subtreeText.isEmpty() && (dirText == "л" || dirText == "п")) {
            BinarySearchTree subTree;
            QStringList numbers = subtreeText.split(",", Qt::SkipEmptyParts);
            for (auto &numStr : numbers) {
                bool ok;
                int num = numStr.trimmed().toInt(&ok);
                if (ok)
                    subTree.add(num);
            }
            bst.insertSubTree(parentVal, subTree, leftSide);
            updateTreeDisplay();
            m_editParent->clear();
            m_editSubtree->clear();
            m_editDirection->clear();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный ввод.");
        }
    });

    connect(btnRemoveSubTree, &QPushButton::clicked, this, [=]() {
        bool ok;
        int targetVal = m_editParent->text().toInt(&ok);
        if (ok) {
            if (bst.removeSubTree(targetVal)) {
                updateTreeDisplay();
                m_editParent->clear();
            } else {
                QMessageBox::information(this, "Информация", "Поддерево не найдено.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверное значение.");
        }
    });

    connect(btnInsertAtPosition, &QPushButton::clicked, this, [=]() {
        bool ok1, ok2;
        int parentVal = m_editParent->text().toInt(&ok1);
        int newVal = m_editNode->text().toInt(&ok2);
        QString dirText = m_editDirection->text().trimmed().toLower();
        bool leftSide = (dirText == "л");

        if (ok1 && ok2 && (dirText == "л" || dirText == "п")) {
            if (bst.insertAtPosition(parentVal, newVal, leftSide)) {
                updateTreeDisplay();
                m_editNode->clear();
                m_editParent->clear();
                m_editDirection->clear();
            } else {
                QMessageBox::information(this, "Информация", "Вставка не выполнена.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверные данные.");
        }
    });

    connect(btnLCA, &QPushButton::clicked, this, [=]() {
        bool ok1, ok2;
        int val1 = m_editLCA1->text().toInt(&ok1);
        int val2 = m_editLCA2->text().toInt(&ok2);
        if (ok1 && ok2) {
            BSTNode *lca = bst.lowestCommonAncestor(val1, val2);
            if (lca)
                QMessageBox::information(this, "НОП",
                                         QString("НОП для %1 и %2: %3").arg(val1).arg(val2).arg(lca->value));
            else
                QMessageBox::information(this, "НОП", "НОП не найден.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверные значения.");
        }
    });

    connect(btnClear, &QPushButton::clicked, this, [=]() {
        bst = BinarySearchTree();
        updateTreeDisplay();
        // Очищаем все поля
        m_editNode->clear();
        m_editParent->clear();
        m_editSubtree->clear();
        m_editDirection->clear();
        m_editLCA1->clear();
        m_editLCA2->clear();
    });

    updateTreeDisplay();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateTreeDisplay()
{
    m_treeWidget->clear();
    BSTNode* root = bst.getRoot();
    if (root) {
        QTreeWidgetItem *rootItem = new QTreeWidgetItem(QStringList(QString::number(root->value)));
        populateTreeWidget(rootItem, root);
        m_treeWidget->addTopLevelItem(rootItem);
        m_treeWidget->expandAll();
    }
}

void MainWindow::populateTreeWidget(QTreeWidgetItem* parentItem, BSTNode* node)
{
    if (node->left) {
        QTreeWidgetItem* leftItem = new QTreeWidgetItem(QStringList(QString::number(node->left->value)));
        parentItem->addChild(leftItem);
        populateTreeWidget(leftItem, node->left);
    }
    if (node->right) {
        QTreeWidgetItem* rightItem = new QTreeWidgetItem(QStringList(QString::number(node->right->value)));
        parentItem->addChild(rightItem);
        populateTreeWidget(rightItem, node->right);
    }
}
