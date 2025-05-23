#ifndef IQUEUE_H
#define IQUEUE_H

class IQueue {
public:
    virtual ~IQueue() = default;
    virtual void enqueue(int value) = 0;
    virtual int dequeue() = 0;
    virtual int front() = 0;
    virtual int back() = 0;
    virtual bool isEmpty() const = 0;
    virtual int size() const = 0;

    virtual int next() const = 0;
    virtual void swapAdjacent() = 0;
    virtual void rotateForward() = 0;
};

#endif // IQUEUE_H
