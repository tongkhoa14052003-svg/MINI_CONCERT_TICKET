
#ifndef STACK_H
#define STACK_H

#include <stack>
#include "Product.h"

class Stack {
private:
    std::stack<Product> items;

public:
    void push(const Product& product);
    bool pop(Product& product);
    bool peek(Product& product) const;

    bool isEmpty() const;
    int size() const;
    void clear();
};

#endif
