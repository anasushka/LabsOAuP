#ifndef AVL_H
#define AVL_H

#include <QString>
#include <QTreeWidget>
#include <QTableWidget>
#include <QVector>

class AVL {
public:
    struct Node {
        int passportNumber;
        QString fullName;
        int height;
        Node* left;
        Node* right;

        Node(int passport, const QString& name)
            : passportNumber(passport), fullName(name),
            height(1), left(nullptr), right(nullptr) {}
    };

    AVL();
    ~AVL();

    void insert(int passport, const QString& name);
    void remove(int passport);
    QString find(int passport) const;
    void clear();
    void balance();

    QString preOrderTraversal() const;  // Прямой обход
    QString inOrderTraversal() const;   // Симметричный обход (по возрастанию)
    QString postOrderTraversal() const; // Обратный обход

    int maxDepth() const;
    void loadFromTable(QTableWidget* table);
    void displayInTreeWidget(QTreeWidget* treeWidget) const;

    Node* getRoot() const { return root; }

private:
    Node* root;
    int size;

    Node* insert(Node* node, int passport, const QString& name);
    Node* remove(Node* node, int passport);
    Node* findMin(Node* node) const;
    Node* removeMin(Node* node);
    Node* balance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    void clear(Node* node);
    int height(Node* node) const;
    int balanceFactor(Node* node) const;
    void updateHeight(Node* node);
    int maxDepth(Node* node) const;

    void collectSorted(Node* node, QVector<QPair<int, QString>>& elements);
    Node* buildBalanced(const QVector<QPair<int, QString>>& elements, int start, int end);

    void buildTreeWidget(Node* node, QTreeWidgetItem* parentItem) const;
    void preOrderTraversal(Node* node, QString& result) const;
    void inOrderTraversal(Node* node, QString& result) const;
    void postOrderTraversal(Node* node, QString& result) const;
};

#endif // AVL_H
