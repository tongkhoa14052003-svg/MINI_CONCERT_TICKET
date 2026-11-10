
#include "Stack.h"

void Stack::push(const Product& product) {
    items.push(product);
}

bool Stack::pop(Product& product) {
    if (items.empty()) {
        return false;
    }

    product = items.top();
    items.pop();

    return true;
}

bool Stack::peek(Product& product) const {
    if (items.empty()) {
        return false;
    }

    product = items.top();
    return true;
}

bool Stack::isEmpty() const {
    return items.empty();
}

int Stack::size() const {
    return static_cast<int>(items.size());
}

void Stack::clear() {
    while (!items.empty()) {
        items.pop();
    }
}
