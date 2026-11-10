
#include "Order.h"

#include <iostream>
#include <iomanip>

#include "Product.h"

void displayOrder(const Order& order) {
    std::cout << "\n========== THONG TIN DON HANG ==========\n";

    std::cout << "Ma don hang: " << order.orderId << '\n';
    std::cout << "Khach hang: " << order.customerName << '\n';
    std::cout << "Trang thai: " << order.status << '\n';

    std::cout << "\nCHI TIET VE:\n";

    if (order.items.empty()) {
        std::cout << "Don hang chua co san pham.\n";
    }

    for (const OrderItem& item : order.items) {
        std::cout << "- " << item.product.name
                  << " | So luong: " << item.quantity
                  << " | Don gia: "
                  << formatVND(item.product.price)
                  << " | Thanh tien: "
                  << formatVND(
                      item.product.price * item.quantity
                  )
                  << '\n';
    }

    std::cout << "----------------------------------------\n";
    std::cout << "TONG TIEN: " << formatVND(order.total) << '\n';
    std::cout << "========================================\n";
}
