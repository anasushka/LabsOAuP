#include "avl.h"
#include <algorithm>

AVL::AVL() : root(nullptr), size(0) {}

AVL::~AVL() {
    clear(root);
}

void AVL::insert(int passport, const QString& name) {
    root = insert(root, passport, name);
}

AVL::Node* AVL::insert(Node* node, int passport, const QString& name) {
    if (!node) {
        size++;
        return new Node(passport, name);
    }

    if (passport < node->passportNumber) {
        node->left = insert(node->left, passport, name);
    } else if (passport > node->passportNumber) {
        node->right = insert(node->right, passport, name);
    } else {
        node->fullName = name;
    }

    updateHeight(node);
    return balance(node);

}

void AVL::remove(int passport) {
    root = remove(root, passport);
}

AVL::Node* AVL::remove(Node* node, int passport) {
    if (!node) return nullptr;

    if (passport < node->passportNumber) {
        node->left = remove(node->left, passport);
    } else if (passport > node->passportNumber) {
        node->right = remove(node->right, passport);
    } else {
        Node* left = node->left;
        Node* right = node->right;

        delete node;
        size--;

        if (!right) return left;

        Node* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;

        return min;
    }

    updateHeight(node);
    return balance(node);

}

AVL::Node* AVL::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

AVL::Node* AVL::removeMin(Node* node) {
    if (!node->left) return node->right;
    node->left = removeMin(node->left);
    return node;
}

void AVL::balance() {
    QVector<QPair<int, QString>> elems;
    collectSorted(root, elems);
    clear(root);
    root = nullptr;
    size = 0;
    root = buildBalanced(elems, 0, elems.size() - 1);
}


AVL::Node* AVL::balance(Node* node) {
    int bf = balanceFactor(node);
    if (bf == 2) {
        // правая ветка «тяжелее»
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (bf == -2) {
        // левая ветка «тяжелее»
        if (balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}


void AVL::collectSorted(Node* node, QVector<QPair<int, QString>>& elements) {
    if (!node) return;
    collectSorted(node->left, elements);
    elements.append(qMakePair(node->passportNumber, node->fullName));
    collectSorted(node->right, elements);
}

AVL::Node* AVL::buildBalanced(const QVector<QPair<int, QString>>& elements, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    Node* newNode = new Node(elements[mid].first, elements[mid].second);
    size++;

    newNode->left = buildBalanced(elements, start, mid - 1);
    newNode->right = buildBalanced(elements, mid + 1, end);

    updateHeight(newNode);
    return newNode;
}

void AVL::clear() {
    clear(root);
    root = nullptr;
    size = 0;
}

void AVL::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int AVL::height(Node* node) const {
    return node ? node->height : 0;
}

void AVL::updateHeight(Node* node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

int AVL::balanceFactor(Node* node) const {
    return height(node->right) - height(node->left);
}

AVL::Node* AVL::rotateRight(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    left->right = node;

    updateHeight(node);
    updateHeight(left);

    return left;
}

AVL::Node* AVL::rotateLeft(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    right->left = node;

    updateHeight(node);
    updateHeight(right);

    return right;
}

QString AVL::find(int passport) const {
    Node* current = root;
    while (current) {
        if (passport < current->passportNumber) {
            current = current->left;
        } else if (passport > current->passportNumber) {
            current = current->right;
        } else {
            return current->fullName;
        }
    }
    return QString();
}

int AVL::maxDepth() const {
    return maxDepth(root);
}

int AVL::maxDepth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(maxDepth(node->left), maxDepth(node->right));
}

void AVL::loadFromTable(QTableWidget* table) {
    clear();
    for (int i = 0; i < table->rowCount(); ++i) {
        int passport = table->item(i, 0)->text().toInt();
        QString name = table->item(i, 1)->text();
        insert(passport, name);
    }
}

void AVL::displayInTreeWidget(QTreeWidget* treeWidget) const {
    treeWidget->clear();
    if (root) {
        QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
        buildTreeWidget(root, item);
        treeWidget->expandAll();
    }
}

void AVL::buildTreeWidget(Node* node, QTreeWidgetItem* parentItem) const {
    if (!node) return;

    QString nodeText = QString("Паспорт: %1, Ф.И.О.: %2").arg(node->passportNumber).arg(node->fullName);
    parentItem->setText(0, nodeText);

    if (node->left) {
        QTreeWidgetItem* leftItem = new QTreeWidgetItem();
        parentItem->addChild(leftItem);
        buildTreeWidget(node->left, leftItem);
    }

    if (node->right) {
        QTreeWidgetItem* rightItem = new QTreeWidgetItem();
        parentItem->addChild(rightItem);
        buildTreeWidget(node->right, rightItem);
    }
}

QString AVL::preOrderTraversal() const {
    QString result;
    preOrderTraversal(root, result);
    return result;
}

void AVL::preOrderTraversal(Node* node, QString& result) const {
    if (node) {
        result += QString("Паспорт: %1, Ф.И.О.: %2\n").arg(node->passportNumber).arg(node->fullName);
        preOrderTraversal(node->left, result);
        preOrderTraversal(node->right, result);
    }
}

QString AVL::inOrderTraversal() const {
    QString result;
    inOrderTraversal(root, result);
    return result;
}

void AVL::inOrderTraversal(Node* node, QString& result) const {
    if (node) {
        inOrderTraversal(node->left, result);
        result += QString("Паспорт: %1, Ф.И.О.: %2\n").arg(node->passportNumber).arg(node->fullName);
        inOrderTraversal(node->right, result);
    }
}

QString AVL::postOrderTraversal() const {
    QString result;
    postOrderTraversal(root, result);
    return result;
}

void AVL::postOrderTraversal(Node* node, QString& result) const {
    if (node) {
        postOrderTraversal(node->left, result);
        postOrderTraversal(node->right, result);
        result += QString("Паспорт: %1, Ф.И.О.: %2\n").arg(node->passportNumber).arg(node->fullName);
    }
}
