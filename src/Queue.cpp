
#include "Queue.h"

void Queue::enqueue(const Order& order) {
    orders.push(order);
}

bool Queue::dequeue(Order& order) {
    if (orders.empty()) {
        return false;
    }

    order = orders.front();
    orders.pop();

    return true;
}

bool Queue::front(Order& order) const {
    if (orders.empty()) {
        return false;
    }

    order = orders.front();
    return true;
}

bool Queue::isEmpty() const {
    return orders.empty();
}

int Queue::size() const {
    return static_cast<int>(orders.size());
}

void Queue::clear() {
    while (!orders.empty()) {
        orders.pop();
    }
}
