#ifndef BINARYTREESEARCH_H
#define BINARYTREESEARCH_H

#include <functional>
#include <climits>
#include <algorithm>

// Узел бинарного дерева
class BSTNode {
public:
    int value;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int v);
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    // добавление нового узла
    void add(int value);

    // удаление узла по значению
    bool remove(int value);

    // поиск узла по значению
    BSTNode* find(int value) const;

    // обход всех узлов (in-order)
    void traverse(std::function<void(int)> func);

    // вставка поддерева
    void insertSubTree(int parentValue, BinarySearchTree &subtree, bool leftSide);

    // удаление поддерева
    bool removeSubTree(int targetValue);

    // вставка элемента в определенную позицию
    bool insertAtPosition(int parentValue, int newValue, bool leftSide);

    // поиск наименьшего общего предка
    BSTNode* lowestCommonAncestor(int value1, int value2);

    // Для отображения дерева в интерфейсе
    BSTNode* getRoot();

private:
    BSTNode* root;

    // рекурсивное добавление
    void add(BSTNode*& node, int value);

    // рекурсивное удаление
    BSTNode* remove(BSTNode* node, int value, bool &removed);

    // рекурсивный поиск
    BSTNode* find(BSTNode* node, int value) const;

    // рекурсивный обход
    void inOrder(BSTNode* node, std::function<void(int)> func);

    // очистка дерева
    void clear(BSTNode* node);

    // рекурсивное удаление поддерева
    bool removeSubTree(BSTNode* node, int targetValue);

    // рекурсивный поиск LCA
    BSTNode* lowestCommonAncestor(BSTNode* node, int value1, int value2);

    // проверка валидности поддерева для BST
    bool isValidSubtree(BSTNode* node, int minVal, int maxVal);
};

#endif // BINARYTREESEARCH_H
