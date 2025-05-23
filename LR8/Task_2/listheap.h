#ifndef LISTHEAP_H
#define LISTHEAP_H

#include <memory>
#include <vector>
#include <queue>
#include <stdexcept>

class HeapNode {
public:
    int value;
    std::weak_ptr<HeapNode> parent;
    std::shared_ptr<HeapNode> left;
    std::shared_ptr<HeapNode> right;

    explicit HeapNode(int val) : value(val) {}
};

class ListHeap {
public:
    ListHeap() : root(nullptr), heapSize(0) {}

    void insert(int value);
    int extractMax();
    int getMax() const;
    bool isEmpty() const { return heapSize == 0; }
    size_t size() const { return heapSize; }
    void clear() { root.reset(); heapSize = 0; }
    std::vector<int> toVector() const;

private:
    std::shared_ptr<HeapNode> root;
    size_t heapSize;

    void heapifyUp(std::shared_ptr<HeapNode> node);
    void heapifyDown(std::shared_ptr<HeapNode> node);
    std::shared_ptr<HeapNode> getLastNode() const;
    void removeLastNode();
};

#endif // LISTHEAP_H
