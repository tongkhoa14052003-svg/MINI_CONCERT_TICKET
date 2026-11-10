
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

#include "Product.h"

struct OrderItem {
    Product product;
    int quantity;
};

struct Order {
    int orderId;
    std::string customerName;
    std::vector<OrderItem> items;
    double total;
    std::string status;
};

// Hiển thị thông tin một đơn hàng
void displayOrder(const Order& order);

#endif
