#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <QString>

class Stack {
private:
    struct StackNode {
        int data;
        StackNode* next;
        StackNode(int value) : data(value), next(nullptr) {}
    };
    StackNode* top;

public:
    Stack();
    ~Stack();
    void push(int value);
    int pop();
    bool isEmpty() const;
    bool contains(int value) const;
    QString toString() const;

    // Для доступа к элементам из HashTable
    class Iterator {
        StackNode* current;
    public:
        Iterator(StackNode* node) : current(node) {}
        bool hasNext() const { return current != nullptr; }
        int next() {
            int val = current->data;
            current = current->next;
            return val;
        }
    };
    Iterator getIterator() const { return Iterator(top); }
};

// Родительский класс
class HashTable {
protected:
    static const int TABLE_SIZE = 21; // Увеличен для диапазона -10..10
    Stack* table[TABLE_SIZE];
    int hashFunction(int key) const {
        // Преобразуем отрицательные ключи в положительные индексы
        return (key + 10) % TABLE_SIZE;
    }

public:
    HashTable();
    virtual ~HashTable();
    void insert(int key);
    bool remove(int key);
    bool contains(int key) const;
    void clear();
    QString print() const;
};

// Производный класс с методом для вашего варианта
class ExtendedHashTable : public HashTable {
public:
    ExtendedHashTable();
    virtual ~ExtendedHashTable();

    // Метод решения вашего варианта
    int removeNegativeKeys();

    // Вспомогательный метод для подсчета отрицательных ключей
    int countNegativeKeys() const;
};

#endif // HASHTABLE_H
