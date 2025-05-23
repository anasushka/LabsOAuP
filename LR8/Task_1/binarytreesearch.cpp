#include "binarytreesearch.h"

// Реализация конструктора узла
BSTNode::BSTNode(int v) : value(v), left(nullptr), right(nullptr) {}

// Реализация конструктора дерева
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Реализация деструктора дерева
BinarySearchTree::~BinarySearchTree() {
    clear(root);
}

// Публичный метод добавления значения в дерево
void BinarySearchTree::add(int value) {
    add(root, value);
}

// Рекурсивное добавление нового узла в дерево
void BinarySearchTree::add(BSTNode*& node, int value) {
    if (node == nullptr) {
        node = new BSTNode(value);
        return;
    }
    if (value < node->value)
        add(node->left, value);
    else if (value > node->value)
        add(node->right, value);
}

bool BinarySearchTree::remove(int value) {
    bool removed = false;
    root = remove(root, value, removed);
    return removed;
}

// ИСПРАВЛЕННОЕ рекурсивное удаление узла по значению
BSTNode* BinarySearchTree::remove(BSTNode* node, int value, bool &removed) {
    if (node == nullptr)
        return node;

    if (value < node->value) {
        node->left = remove(node->left, value, removed);
    } else if (value > node->value) {
        node->right = remove(node->right, value, removed);
    } else {
        // Узел найден
        removed = true;

        // Случай 1: узел без детей или с одним ребенком
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        } else {
            // Случай 2: узел с двумя детьми
            // Находим наименьший элемент в правом поддереве (наследника)
            BSTNode* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            // Копируем значение наследника в текущий узел
            node->value = successor->value;

            // Удаляем наследника (он гарантированно имеет не более одного ребенка)
            bool tempRemoved = false;
            node->right = remove(node->right, successor->value, tempRemoved);
        }
    }
    return node;
}

// Публичный метод поиска узла по значению
BSTNode* BinarySearchTree::find(int value) const {
    return find(root, value);
}

// Рекурсивный поиск узла по значению
BSTNode* BinarySearchTree::find(BSTNode* node, int value) const {
    if (node == nullptr)
        return nullptr;
    if (value < node->value)
        return find(node->left, value);
    else if (value > node->value)
        return find(node->right, value);
    else
        return node;
}

void BinarySearchTree::traverse(std::function<void(int)> func) {
    inOrder(root, func);
}

// Рекурсивный in-order обход дерева
void BinarySearchTree::inOrder(BSTNode* node, std::function<void(int)> func) {
    if (node == nullptr)
        return;
    inOrder(node->left, func);
    func(node->value);
    inOrder(node->right, func);
}

void BinarySearchTree::clear(BSTNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// УЛУЧШЕННАЯ вставка поддерева с проверкой BST-свойств
void BinarySearchTree::insertSubTree(int parentValue, BinarySearchTree &subtree, bool leftSide) {
    BSTNode* parent = find(parentValue);
    if (parent && subtree.root != nullptr) {
        if (leftSide && parent->left == nullptr) {
            // Проверяем, что все значения в поддереве меньше родителя
            if (isValidSubtree(subtree.root, INT_MIN, parent->value)) {
                parent->left = subtree.root;
                subtree.root = nullptr;
            }
        } else if (!leftSide && parent->right == nullptr) {
            // Проверяем, что все значения в поддереве больше родителя
            if (isValidSubtree(subtree.root, parent->value, INT_MAX)) {
                parent->right = subtree.root;
                subtree.root = nullptr;
            }
        }
    }
}

// Вспомогательный метод для проверки валидности поддерева
bool BinarySearchTree::isValidSubtree(BSTNode* node, int minVal, int maxVal) {
    if (node == nullptr)
        return true;

    if (node->value <= minVal || node->value >= maxVal)
        return false;

    return isValidSubtree(node->left, minVal, node->value) &&
           isValidSubtree(node->right, node->value, maxVal);
}

bool BinarySearchTree::removeSubTree(int targetValue) {
    if (root == nullptr)
        return false;
    if (root->value == targetValue) {
        clear(root);
        root = nullptr;
        return true;
    }
    return removeSubTree(root, targetValue);
}

bool BinarySearchTree::removeSubTree(BSTNode* node, int targetValue) {
    if (node == nullptr)
        return false;
    if (node->left && node->left->value == targetValue) {
        clear(node->left);
        node->left = nullptr;
        return true;
    }
    if (node->right && node->right->value == targetValue) {
        clear(node->right);
        node->right = nullptr;
        return true;
    }
    return removeSubTree(node->left, targetValue) || removeSubTree(node->right, targetValue);
}

// УЛУЧШЕННАЯ вставка с проверкой BST-свойств
bool BinarySearchTree::insertAtPosition(int parentValue, int newValue, bool leftSide) {
    BSTNode* parent = find(parentValue);
    if (parent) {
        if (leftSide && parent->left == nullptr) {
            // Проверяем BST-свойство: новое значение должно быть меньше родителя
            if (newValue < parent->value) {
                parent->left = new BSTNode(newValue);
                return true;
            }
        } else if (!leftSide && parent->right == nullptr) {
            // Проверяем BST-свойство: новое значение должно быть больше родителя
            if (newValue > parent->value) {
                parent->right = new BSTNode(newValue);
                return true;
            }
        }
    }
    return false;
}

// ОПТИМИЗИРОВАННЫЙ поиск наименьшего общего предка
BSTNode* BinarySearchTree::lowestCommonAncestor(int value1, int value2) {
    return lowestCommonAncestor(root, value1, value2);
}

// Рекурсивный поиск наименьшего общего предка для двух узлов
BSTNode* BinarySearchTree::lowestCommonAncestor(BSTNode* node, int value1, int value2) {
    if (node == nullptr)
        return nullptr;

    // Убеждаемся, что value1 <= value2 для упрощения логики
    if (value1 > value2) {
        std::swap(value1, value2);
    }

    // Если оба значения меньше текущего, искомый узел находится в левом поддереве
    if (node->value > value2)
        return lowestCommonAncestor(node->left, value1, value2);
    // Если оба значения больше, то искомый узел находится в правом поддереве
    if (node->value < value1)
        return lowestCommonAncestor(node->right, value1, value2);

    // Если мы здесь, то node->value находится между value1 и value2,
    // следовательно, это LCA (при условии, что оба узла существуют)
    // Проверяем существование обоих узлов
    if (find(node, value1) && find(node, value2))
        return node;
    else
        return nullptr;
}

BSTNode* BinarySearchTree::getRoot() {
    return root;
}
