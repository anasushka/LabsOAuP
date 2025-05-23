#ifndef QUEUE_H
#define QUEUE_H

#include "iqueue.h"

class Queue : public IQueue {
private:
    int* data;
    int frontIndex;
    int backIndex;
    int capacity;
    int currentSize;

    void resize();

public:
    Queue(int initialCapacity);
    ~Queue();

    void enqueue(int value) override;
    int dequeue() override;
    int front() override;
    int back() override;
    bool isEmpty() const override;
    int size() const override;

    int next() const override;
    void swapAdjacent() override;
    void rotateForward() override;
};

#endif // QUEUE_H
