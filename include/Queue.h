
#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Order.h"

class Queue {
private:
    std::queue<Order> orders;

public:
    void enqueue(const Order& order);
    bool dequeue(Order& order);
    bool front(Order& order) const;

    bool isEmpty() const;
    int size() const;
    void clear();
};

#endif
