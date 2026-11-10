
#include "Cart.h"

#include <iostream>

Cart::Cart() {
}

bool Cart::addProduct(
    const Product& product,
    int quantity
) {
    if (quantity <= 0 || product.stock <= 0) {
        return false;
    }

    for (OrderItem& item : items) {
        if (item.product.id == product.id) {
            if (item.quantity + quantity > product.stock) {
                return false;
            }

            item.quantity += quantity;
            return true;
        }
    }

    if (quantity > product.stock) {
        return false;
    }

    OrderItem newItem;
    newItem.product = product;
    newItem.quantity = quantity;

    items.push_back(newItem);

    return true;
}

bool Cart::removeProduct(int productId) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].product.id == productId) {
            undoStack.push(items[i].product);
            removedQuantities.push_back(items[i].quantity);

            items.erase(items.begin() + i);
            return true;
        }
    }

    return false;
}

bool Cart::undoLastRemoval() {
    if (undoStack.isEmpty() || removedQuantities.empty()) {
        return false;
    }

    Product product;

    if (!undoStack.pop(product)) {
        return false;
    }

    int quantity = removedQuantities.back();
    removedQuantities.pop_back();

    for (OrderItem& item : items) {
        if (item.product.id == product.id) {
            item.quantity += quantity;
            return true;
        }
    }

    OrderItem restoredItem;
    restoredItem.product = product;
    restoredItem.quantity = quantity;

    items.push_back(restoredItem);

    return true;
}

double Cart::getTotal() const {
    double total = 0;

    for (const OrderItem& item : items) {
        total += item.product.price * item.quantity;
    }

    return total;
}

int Cart::getItemCount() const {
    int total = 0;

    for (const OrderItem& item : items) {
        total += item.quantity;
    }

    return total;
}

void Cart::display() const {
    std::cout << "\n========== GIO HANG ==========\n";

    if (items.empty()) {
        std::cout << "Gio hang dang trong.\n";
        return;
    }

    for (const OrderItem& item : items) {
        std::cout << "ID: " << item.product.id
                  << " | Ten ve: " << item.product.name
                  << " | So luong: " << item.quantity
                  << " | Don gia: "
                  << formatVND(item.product.price)
                  << " | Thanh tien: "
                  << formatVND(item.product.price * item.quantity)
                  << '\n';
    }

    std::cout << "Tong so ve: " << getItemCount() << '\n';
    std::cout << "Tong tien: " << formatVND(getTotal()) << '\n';
    std::cout << "==============================\n";
}

Order Cart::checkout(
    int orderId,
    const std::string& customerName
) const {
    Order order;

    order.orderId = orderId;
    order.customerName = customerName;
    order.items = items;
    order.total = getTotal();
    order.status = "Cho xu ly";

    return order;
}

void Cart::clear() {
    items.clear();
    undoStack.clear();
    removedQuantities.clear();
}

bool Cart::isEmpty() const {
    return items.empty();
}
