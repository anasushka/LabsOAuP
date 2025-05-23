#include "queue.h"
#include <stdexcept>

Queue::Queue(int initialCapacity) :
    frontIndex(0),
    backIndex(0),
    capacity(initialCapacity > 0 ? initialCapacity : 1),
    currentSize(0) {
    data = new int[capacity];
}

Queue::~Queue() {
    delete[] data;
}

int Queue::size() const {
    return currentSize;
}

bool Queue::isEmpty() const {
    return (currentSize == 0);
}

void Queue::enqueue(int value) {
    if (currentSize >= capacity) {
        resize();
    }
    data[backIndex] = value;
    backIndex = (backIndex + 1) % capacity;
    currentSize++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty!");
    }
    int value = data[frontIndex];
    frontIndex = (frontIndex + 1) % capacity;
    currentSize--;
    return value;
}

int Queue::front() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty!");
    }
    return data[frontIndex];
}

int Queue::back() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty!");
    }
    return data[(backIndex == 0) ? capacity - 1 : backIndex - 1];
}

void Queue::resize() {
    int newCapacity = capacity * 2;
    int* temp = new int[newCapacity];

    for (int i = 0, j = frontIndex; i < currentSize; ++i) {
        temp[i] = data[j];
        j = (j + 1) % capacity;
    }

    delete[] data;
    data = temp;
    capacity = newCapacity;
    frontIndex = 0;
    backIndex = currentSize;
}

void Queue::swapAdjacent() {
    if (currentSize < 2) return;

    int first = dequeue();
    int second = dequeue();

    enqueue(second);
    enqueue(first);

    for (int i = 2; i < currentSize; ++i) {
        enqueue(dequeue());
    }
}

void Queue::rotateForward() {
    if (isEmpty()) return;
    enqueue(dequeue());
}

int Queue::next() const {
    if (size() < 2) {
        throw std::runtime_error("Not enough elements");
    }
    return data[(frontIndex + 1) % capacity];
}
