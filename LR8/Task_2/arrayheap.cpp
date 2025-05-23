#include "arrayheap.h"

void ArrayHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

int ArrayHeap::extractMax() {
    if (heap.empty()) {
        throw std::out_of_range("Heap is empty");
    }

    int max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }

    return max;
}

int ArrayHeap::getMax() const {
    if (heap.empty()) {
        throw std::out_of_range("Heap is empty");
    }
    return heap[0];
}

bool ArrayHeap::isEmpty() const {
    return heap.empty();
}

size_t ArrayHeap::size() const {
    return heap.size();
}

void ArrayHeap::clear() {
    heap.clear();
}

std::vector<int> ArrayHeap::toVector() const {
    return heap;
}

void ArrayHeap::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap[index] <= heap[parent]) {
            break;
        }
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

void ArrayHeap::heapifyDown(size_t index) {
    size_t left, right, largest;
    size_t size = heap.size();

    while (true) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}
