#include "hashtable.h"
#include <QList>
#include <climits>

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(int value) {
    StackNode* newNode = new StackNode(value);
    newNode->next = top;
    top = newNode;
}

int Stack::pop() {
    if (isEmpty()) return INT_MIN; // Изменено для работы с отрицательными числами
    StackNode* temp = top;
    int value = temp->data;
    top = top->next;
    delete temp;
    return value;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

bool Stack::contains(int value) const {
    StackNode* current = top;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}

QString Stack::toString() const {
    QStringList elements;
    StackNode* current = top;
    while (current) {
        elements << QString::number(current->data);
        current = current->next;
    }
    return "[" + elements.join(" → ") + "]";
}

// Реализация родительского класса HashTable
HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = new Stack();
    }
}

HashTable::~HashTable() {
    clear();
    for (int i = 0; i < TABLE_SIZE; ++i) {
        delete table[i];
    }
}

void HashTable::insert(int key) {
    int index = hashFunction(key);
    table[index]->push(key);
}

bool HashTable::remove(int key) {
    int index = hashFunction(key);
    Stack tempStack;
    bool found = false;

    while (!table[index]->isEmpty()) {
        int val = table[index]->pop();
        if (val == key) {
            found = true;
            break;
        }
        tempStack.push(val);
    }

    while (!tempStack.isEmpty()) {
        table[index]->push(tempStack.pop());
    }

    return found;
}

bool HashTable::contains(int key) const {
    int index = hashFunction(key);
    return table[index]->contains(key);
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        while (!table[i]->isEmpty()) {
            table[i]->pop();
        }
    }
}

QString HashTable::print() const {
    QStringList result;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (!table[i]->isEmpty()) {
            result << QString("%1: %2").arg(i).arg(table[i]->toString());
        }
    }
    return result.join("\n");
}

// Реализация производного класса ExtendedHashTable
ExtendedHashTable::ExtendedHashTable() : HashTable() {}

ExtendedHashTable::~ExtendedHashTable() {}

int ExtendedHashTable::removeNegativeKeys() {
    int removedCount = 0;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Stack tempStack;

        // Извлекаем все элементы из стека
        while (!table[i]->isEmpty()) {
            int val = table[i]->pop();
            if (val >= 0) {
                // Если ключ неотрицательный, сохраняем его
                tempStack.push(val);
            } else {
                // Если ключ отрицательный, удаляем его (не сохраняем)
                removedCount++;
            }
        }

        // Возвращаем неотрицательные элементы обратно в стек
        while (!tempStack.isEmpty()) {
            table[i]->push(tempStack.pop());
        }
    }

    return removedCount;
}

int ExtendedHashTable::countNegativeKeys() const {
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Stack::Iterator it = table[i]->getIterator();
        while (it.hasNext()) {
            int current = it.next();
            if (current < 0) {
                count++;
            }
        }
    }

    return count;
}
