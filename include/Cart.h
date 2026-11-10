
#ifndef CART_H
#define CART_H

#include <vector>
#include <string>
#include "Order.h"
#include "Stack.h"

class Cart {
private:
    std::vector<OrderItem> items;
    Stack undoStack;
    std::vector<int> removedQuantities;

public:
    Cart();

    bool addProduct(const Product& product, int quantity = 1);
    bool removeProduct(int productId);
    bool undoLastRemoval();

    double getTotal() const;
    int getItemCount() const;

    void display() const;

    Order checkout(
        int orderId,
        const std::string& customerName
    ) const;

    void clear();
    bool isEmpty() const;
};

#endif
