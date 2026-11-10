
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <iomanip>

struct Product {
    int id{};
    std::string name;
    double price{};
    int stock{};
    double rating{};
};

std::string formatVND(double amount);
void displayProduct(const Product& product);

#endif
