#ifndef ARRAYHEAP_H
#define ARRAYHEAP_H

#include <vector>
#include <stdexcept>

class ArrayHeap {
public:
    void insert(int value);
    int extractMax();
    int getMax() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
    std::vector<int> toVector() const;

private:
    std::vector<int> heap;
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
};

#endif // ARRAYHEAP_H
