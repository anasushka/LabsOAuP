#include "hashtable.h"
#include <algorithm>
#include <cmath>

HashTable::HashTable(int size, HashMethod method)
    : table(size, -1), method(method), collisions(0), maxProbes(0), elementsCount(0) {}

bool HashTable::insert(int key) {
    if (elementsCount >= table.size()) {
        return false; // Таблица заполнена
    }

    int attempt = 0;
    int originalHash = (method == Multiplicative) ? multiplicativeHash(key) : modularHash(key);

    do {
        int index = linearProbe(key, attempt);
        if (table[index] == -1) {
            table[index] = key;
            elementsCount++;
            maxProbes = std::max(maxProbes, attempt);
            return true;
        }
        if (table[index] == key) {
            return false; // Ключ уже существует
        }
        if (attempt == 0) {
            collisions++;
            collisionDetails[key] = originalHash;
        }
        attempt++;
    } while (attempt < table.size());

    return false;
}

bool HashTable::search(int key, int& comparisons) const {
    comparisons = 0;
    int attempt = 0;

    do {
        comparisons++;
        int index = linearProbe(key, attempt);
        if (table[index] == key) return true;
        if (table[index] == -1) return false;
        attempt++;
    } while (attempt < table.size());

    return false;
}

double HashTable::measureSearchTime(int key, int iterations) const {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++) {
        int comparisons;
        search(key, comparisons);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    return static_cast<double>(duration.count()) / iterations; // среднее время в наносекундах
}

int HashTable::getCollisionsCount() const {
    return collisions;
}

int HashTable::getMaxProbes() const {
    return maxProbes;
}

QHash<int, int> HashTable::getCollisionDetails() const {
    return collisionDetails;
}

int HashTable::getSize() const {
    return table.size();
}

double HashTable::getLoadFactor() const {
    return static_cast<double>(elementsCount) / table.size();
}

void HashTable::clear() {
    table.fill(-1);
    collisions = 0;
    maxProbes = 0;
    elementsCount = 0;
    collisionDetails.clear();
}

int HashTable::multiplicativeHash(int key) const {
    // H(key) = [hashTableSize * (key * A mod 1)]
    double keyA = static_cast<double>(key) * A;
    double fractionalPart = keyA - std::floor(keyA); // (key * A mod 1)
    return static_cast<int>(std::floor(table.size() * fractionalPart));
}

int HashTable::modularHash(int key) const {
    return key % table.size();
}

int HashTable::linearProbe(int key, int attempt) const {
    int hash = (method == Multiplicative) ? multiplicativeHash(key) : modularHash(key);
    return (hash + attempt) % table.size();
}
