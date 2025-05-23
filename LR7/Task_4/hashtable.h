#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <QVector>
#include <QHash>
#include <chrono>

class HashTable {
public:
    enum HashMethod { Multiplicative, Modular };

    HashTable(int size, HashMethod method);
    bool insert(int key);
    bool search(int key, int& comparisons) const;
    double measureSearchTime(int key, int iterations = 1000) const;
    int getCollisionsCount() const;
    int getMaxProbes() const;
    QHash<int, int> getCollisionDetails() const;
    void clear();
    int getSize() const;
    double getLoadFactor() const;

private:
    int multiplicativeHash(int key) const;
    int modularHash(int key) const;
    int linearProbe(int key, int attempt) const;

    QVector<int> table;
    QHash<int, int> collisionDetails; // key -> h'(key)
    HashMethod method;
    int collisions;
    int maxProbes;
    int elementsCount;

    // Константа для мультипликативного хеширования
    static constexpr double A = 0.6180339887499; // (sqrt(5) - 1) / 2
};

#endif // HASHTABLE_H
