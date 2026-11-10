
#include "Product.h"

#include <string>

std::string formatVND(double amount) {
    long long value = static_cast<long long>(amount + 0.5);
    std::string s = std::to_string(value);

    for (int i = static_cast<int>(s.size()) - 3; i > 0; i -= 3) {
        s.insert(static_cast<size_t>(i), ".");
    }

    return s + " VNĐ";
}

void displayProduct(const Product& p) {
    std::cout << std::left
              << std::setw(9) << p.id
              << std::setw(38) << p.name
              << std::right
              << std::setw(18) << formatVND(p.price)
              << std::setw(10) << p.stock
              << std::setw(9) << std::fixed
              << std::setprecision(1) << p.rating
              << '\n';
}
